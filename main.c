#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include <time.h>
#include <string.h>
#include "./core/json.h"
#include "./core/funktion.h"
#include "./core/gestion_des_quiz.h"




int main(int argc, char *argv[])
{
	char path_DATA_json[128];
    char path_Profil_json[128];
    printf("Recherche du fichier Data_en.json");
    recherch(path_DATA_json, sizeof(path_DATA_json), 'D');
    printf("Recherche du fichier Profil.json");
    recherch(path_Profil_json, sizeof(path_Profil_json), 'P');
    clear();

    char on[20] = "\033[1;32mON\033[0m";
    char off[21] = "\033[1;31mOFF\033[0m";

    int bouton_english = 0;
    int bouton_english_verb = 1;
    
	int bouton_math = 0;
	int bouton_math_basic = 1;

    int mode_infini = 0;
    int mode_normal = 1;

    if (argc == 1) {
        printf("Basic Mode: %s\n", on);
        printf("Personal Mode: %s\n", off);
    } else {
        printf("Basic Mode: %s\n", off);
        printf("Personal Mode: %s\n", on);
        for(int i = 1; i < argc; i++)
        {
			int j = i + 1;
            if (!strcmp(argv[i], "English")) {
                bouton_english = 1;
                printf("ENGLISH: %s\n", on);
                if (j < argc && !strcmp(argv[j], "verb")) {
                	bouton_english_verb = 1;
                	printf("\tVerb: %s\n", on);
                	i++;
                }
            } else if (!strcmp(argv[i], "math")) {
                bouton_math = 1;
                printf("MATH: %s\n", on);
                if (j < argc && !strcmp(argv[j], "basic")) {
                    bouton_math_basic = 1;
                	printf("\tBasic (+ / * -): %s\n", on);
                }
            } else if (!strcmp(argv[i], "infini")) {
                mode_infini = 1;
                mode_normal = 0;
                printf("Mode Infini: %s\n", on);
                printf("Mode Normal: %s\n", off);
            } else if (!strcmp(argv[i], "normal")) {
                mode_normal = 1;
                mode_infini = 0;
                printf("Mode Normal: %s\n", on);
                printf("Mode Infini: %s\n", off);
            } else {
                printf("Warning: The argument \"%s\" is not recognized.\n", argv[i]);
            }
        }
    }

    srand(time(NULL));
    int temp_int;
    cJSON *json = NULL;
    cJSON *Profil_json = NULL;
    
    temp_int = ouverture_du_json(path_DATA_json, &json);
    if (temp_int != 0) exit(1);

    temp_int = ouverture_du_json(path_Profil_json, &Profil_json);
    if (temp_int != 0) {
        cJSON_Delete(json);
        exit(1);
    }
	char username[21];
    printf("Quel est ton nom d'utilisateur [20max]?\n>> ");
    scanf(" %20s", username);

    // --- CHARGEMENT DU COMPTE UTILISATEUR ---	

    // Vider le tampon mémoire après scanf pour éviter des conflits avec les prochains menus
    int clean_char;
    while ((clean_char = getchar()) != '\n' && clean_char != EOF);

    // Utilisation de GetObjectItem pour chercher par clé de chaîne
    cJSON *user = cJSON_GetObjectItemCaseSensitive(Profil_json, username);
    
    int xp = 0;
    int level = 1;
    int score_max = 0;
    int score = 0;

    if (cJSON_IsObject(user)){
        cJSON *cjson_xp = cJSON_GetObjectItemCaseSensitive(user, "xp");
        cJSON *cjson_level = cJSON_GetObjectItemCaseSensitive(user, "level");
        cJSON *cjson_score_max = cJSON_GetObjectItemCaseSensitive(user, "score_max");

        if(cjson_xp) xp = cjson_xp->valuedouble;
        if(cjson_level) level = cjson_level->valuedouble;
        if(cjson_score_max) score_max = cjson_score_max->valuedouble;

        
        printf("Profil chargé ! Niveau: %d | XP actuel: %d | Record: %d\n\n", level, xp, score_max);
    } else {
        // L'utilisateur n'existe pas, on l'ajoute à la structure JSON globale
        printf("Création d'un nouveau profil pour \"%s\"...\n\n", username);
        user = cJSON_CreateObject();
        cJSON_AddNumberToObject(user, "level", 1);
        cJSON_AddNumberToObject(user, "xp", 0);
        cJSON_AddNumberToObject(user, "score_max", 0);
        cJSON_AddItemToObject(Profil_json, username, user);
    }

    //Choix de la matiere
	int choix[3][2] = {{mode_infini, mode_normal}, {bouton_english, bouton_english_verb}, {bouton_math, bouton_math_basic}};	
	table_des_matiere(choix);
	mode_infini = choix[0][0];
	mode_normal = choix[0][1];
	bouton_english = choix[1][0];
	bouton_english_verb = choix[1][1];
	bouton_math = choix[2][0];
	bouton_math_basic = choix[2][1];

	/*=============*/
	/* PARTIE QUIZ */
	/*=============*/
    clear();
    int nombre_de_question = 0;
    if(!mode_infini && mode_normal){
		quiz_normal(choix, &score, &nombre_de_question, json, Profil_json);
    } else if(mode_infini && !mode_normal){
		quiz_infini(choix, &score, &nombre_de_question, json, Profil_json);
    }

	/*========================================*/
	/* PRESENTATION DE LA FIN AVEC SAUVEGARDE */
	/*========================================*/
	char mode;
	if (mode_infini) {mode = 'i';}
	 else {mode = 'n';};
	gamification(&score, &score_max, &level, &xp, nombre_de_question, mode);
    
    // --- MISE À JOUR DANS LA STRUCTURE JSON ET SAUVEGARDE ---
    cJSON_SetNumberValue(cJSON_GetObjectItemCaseSensitive(user, "xp"), xp);
    cJSON_SetNumberValue(cJSON_GetObjectItemCaseSensitive(user, "level"), level);
    cJSON_SetNumberValue(cJSON_GetObjectItemCaseSensitive(user, "score_max"), score_max);

    sauvegarder_du_json(path_Profil_json, Profil_json);
    printf("Données de jeu synchronisées avec succès.\n");

    // Nettoyage complet de la mémoire
    cJSON_Delete(json);
    cJSON_Delete(Profil_json);
    return 0;
}
