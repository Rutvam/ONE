#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include <time.h>
#include <string.h>
#include "./core/json.h"
#include "./MATIERE/ENGLISH/english.h"
#include "./MATIERE/MATH/math.h"
void clear() {
    printf("\033[H\033[2J");
    fflush(stdout);
}

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
    int bouton_english_verb = 0;
    
	int bouton_math = 0;
	int bouton_math_basic = 0;

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
	char state[2][22] = {"\033[1;31mOFF\033[0m", "\033[1;32mON\033[0m"};
	char answer_char;

	int choix[2][2] = {{bouton_english, bouton_english_verb}, {bouton_math, bouton_math_basic}};
	int condition = 0;
	while (!condition)
	{
		clear();
		switch (bouton_english)
		{
			case 0:
				printf("[1] English: %s\n", off);
				break;
			case 1:
				printf("[1] English: %s\n", on);
				printf("\t[a] verb: %s\n", state[bouton_english_verb]);
				break;
		}

		switch (bouton_math)
		{
			case 0:
				printf("[2] math: %s\n", off);
				break;
			case 1:
				printf("[2] math: %s\n", on);
				printf("\t[a] basic (+ - * /): %s\n", state[bouton_math_basic]);
				break;
		}
			
		printf("[n] mode normal: %s\n", state[mode_normal]);
		printf("[i] mode infini: %s\n", state[mode_infini]);
		printf("Entrer un de ses caractere (c = continue; q = quitter):\n>>");
		scanf(" %c", &answer_char);

		switch (answer_char)
		{
			case 'q':
				exit(0);
			case 'a':
				printf("Entrer le chiffre entre les crochet \"[]\" de la veleur parent:\n>>");
				char answer_char_2;
				scanf(" %c", &answer_char_2);
				switch (answer_char_2)
				{
					case '1':
						bouton_english_verb = !bouton_english_verb;
						break;
					case '2':
						bouton_math_basic = !bouton_math_basic;
						break;
				};
				break;
			case 'c':
				if ((choix[0][0] && choix[0][1]) || (choix[1][0] && choix[1][1])) {
					condition = 1;
				} else {
					printf("Erreur: choisier une matière");
				};
				break;
			case 'i':
				mode_normal = !mode_normal;
				mode_infini = !mode_infini;
				break;
			case 'n':
				mode_normal = !mode_normal;
				mode_infini = !mode_infini;
				break;
			case '1':
				bouton_english = !bouton_english;
				break;
			case '2':
				bouton_math = !bouton_math;
				break;
		}
		choix[0][0] = bouton_english;
		choix[0][1] = bouton_english_verb;
		choix[1][0] = bouton_math;
		choix[1][1] = bouton_math_basic;
	}


    int nombre_de_question = 0;
    clear();
    if(!mode_infini && mode_normal){
        int nombre = 0;
        printf("Combien de question?\n>>");
        while(scanf("%d", &nombre) != 1 || nombre < 1)
        {
        	printf("Erreur: entrer un nombre!\n");
        	int clean;
        	while ((clean = getchar()) != '\n' && clean != EOF);

        	nombre = 0;
        	printf("Combien de question?\n>>");
        }
        nombre_de_question = nombre;
            
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Nettoyage indispensable

        for(int i = 0; i < nombre; i++)
        {
			int value = -2;
			if ((choix[0][0] && choix[0][1]) || (choix[1][0] && choix[1][1])) {
				int temp_int = rand()%2;
				if (!temp_int && bouton_english) {
					value = question_english(json);
				} else if (temp_int && bouton_math) {
					int a;
					int b;
					char op;
					int result;
					random_value(&a, &b, &op);
					result = opperation_basic(a, b, op);
					value = question_math(a, b, op, result);
				} else {
					i--;
					value = 0;
				}
			} else {
				printf("ERROR: aucune matiere choisi.");
				exit(0);
			}
	        switch(value)
    	    {
    	    	case 2:
					cJSON_Delete(json);
					cJSON_Delete(Profil_json);
					return 0;
                case 1: 
   	                score++;
       	            break;
           	    case 0: 
               	    break;
                case -1:
   	                score--;
       	            break;
       	        case -2:
    				cJSON_Delete(json);
					cJSON_Delete(Profil_json);
       	            return 0;
           	    default:
               	    break;
            }
        }
    } else if(mode_infini && !mode_normal){
        int continu = 1;
        int value = -2;
        while(continu)
        {
			if ((choix[0][0] && choix[0][1]) || (choix[1][0] && choix[1][1])) {
				int temp_int = rand()%2;
				if (!temp_int && bouton_english) {
					value = question_english(json);
				} else if (temp_int && bouton_math) {
					int a;
					int b;
					char op;
					int result;
					random_value(&a, &b, &op);
					result = opperation_basic(a, b, op);
					value = question_math(a, b, op, result);
				} else {
					value = 0;
					nombre_de_question--;
				}
			} else {
				printf("ERROR: aucune matiere choisi.");
				exit(0);
			}
            nombre_de_question++;
	        switch(value)
    	    {
    	    	case 2:
					cJSON_Delete(json);
					cJSON_Delete(Profil_json);
					return 0;
                case 1: 
   	                score++;
       	            break;
           	    case 0: 
               	    break;
                case -1:
   	                continu= 0;
       	            break;
       	        case -2:
    				cJSON_Delete(json);
					cJSON_Delete(Profil_json);
       	            exit(0);
           	    default:
               	    break;
            }
        }
    }
    float pourcentage = 0;
    if ( score >= 1 || nombre_de_question >= 1) {
	    pourcentage = ((float)score/nombre_de_question)*100;
    	printf("\nWow ... Tu as un score de %d en %d question(s)!\nC'est un taux de reussite de %3f%%\n", score, nombre_de_question, pourcentage);
    } else {
    	printf("\nAi ... La prochaine fois cela ira mieux.\nTu peut egalment esseiler le mode normal. même si il y a une mauvaise reponce le quiz continue.\n");
    }
    // --- LOGIQUE DE PROGRESSION & LEVEL UP ---
    int xp_gagne = 0;
    if (mode_normal && !mode_infini) {
	    if(pourcentage >= 75){
        	int bonus = score + level + 100;
        	xp_gagne = (score * nombre_de_question) + bonus;
    	} else if (75 > pourcentage && pourcentage > 50) {
    		int bonus = score + level;
    		xp_gagne = (score * nombre_de_question) + bonus;
    	} else if (pourcentage == 50) {
    		xp_gagne = score * nombre_de_question;
    	} else {
    	    xp_gagne = score;
    	}
    } else if (!mode_normal && mode_infini) {
    	int bonus = score + level;
    	score++;
		xp_gagne = score * nombre_de_question + bonus;
	}
    
    xp += xp_gagne;
    printf("Vous avez gagné %d XP ! (Total: %d XP)\n", xp_gagne, xp);

    // Boucle tant qu'on a assez d'XP pour monter de niveau
    while (xp >= level * 1500) {
        xp = xp - (level * 1500); // Déduction de l'XP consommée pour le passage
        level++;
        printf("\033[1;33mUP ! Tu passes au Niveau %d !\033[0m\n", level);
    }

    if(score > score_max){
        score_max = score;
        printf("\033[1;36mNouveau score maximal pour %s: %d !\033[0m\n", username, score_max);
    }
    
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
