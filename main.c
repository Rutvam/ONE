#include <stdio.h>
#include <stdlib.h>
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

	int choix[3][2] = {{0, 1}, {0, 1}, {0, 1}};	
	argv_and_argc_search(argc, argv, choix);
    


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
	table_des_matiere(choix);
	
	/*=============*/
	/* PARTIE QUIZ */
	/*=============*/
    clear();
    int nombre_de_question = 0;
    if(!choix[0][0] && choix[0][1]){
		quiz_normal(choix, &score, &nombre_de_question, json, Profil_json);
    } else if(choix[0][0] && !choix[0][1]){
		quiz_infini(choix, &score, &nombre_de_question, json, Profil_json);
    }

	/*========================================*/
	/* PRESENTATION DE LA FIN AVEC SAUVEGARDE */
	/*========================================*/
	char mode;
	if (choix[0][0]) {mode = 'i';}
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
