#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include "gestion_des_quiz.h"
#include "../MATIERE/ENGLISH/english.h"
#include "../MATIERE/MATH/math.h"

void gamification(int *score, int *score_max, int *level, int *xp, int nombre_de_question, char mode)
{
    float pourcentage = 0;
    if (nombre_de_question > 0) {
	    pourcentage = ((float)(*score)/nombre_de_question)*100;
    	printf("\nWow ... Tu as un score de %d en %d question(s)!\nC'est un taux de reussite de %3f%%\n", *score, nombre_de_question, pourcentage);
    } else {
    	printf("\nAi ... La prochaine fois cela ira mieux.\nTu peut egalment esseiler le mode normal. même si il y a une mauvaise reponce le quiz continue.\n");
    }
    // --- LOGIQUE DE PROGRESSION & LEVEL UP ---
    int xp_gagne = 0;
    if (mode == 'n') {
	    if(pourcentage >= 75){
        	int bonus = (*score) + (*level) + 100;
        	xp_gagne = ((*score) * nombre_de_question) + bonus;
    	} else if (75 > pourcentage && pourcentage > 50) {
    		int bonus = (*score) + (*level);
    		xp_gagne = ((*score) * nombre_de_question) + bonus;
    	} else if (pourcentage == 50) {
    		xp_gagne = (*score) * nombre_de_question;
    	} else {
    	    xp_gagne = (*score);
    	}
    } else if (mode == 'i') {
    	(*score)++;
		xp_gagne = (*score) * nombre_de_question;
		if (*score >= 10)
		{
	    	int bonus = (*score) + (*level);
			xp_gagne += bonus;
		}
	}
    
    (*xp) += xp_gagne;
    printf("Vous avez gagné %d XP ! (Total: %d XP)\n", xp_gagne, *xp);

    // Boucle tant qu'on a assez d'XP pour monter de niveau
    while (*xp >= (*level) * 1500) {
        (*xp) = (*xp) - ((*level) * 1500); // Déduction de l'XP consommée pour le passage
        (*level)++;
        printf("\033[1;33mUP ! Tu passes au Niveau %d !\033[0m\n", *level);
    }

    if(*score > *score_max){
        *score_max = *score;
        printf("\033[1;36mNouveau score maximal: %d !\033[0m\n", *score_max);
    }
}

void quiz_normal(int choix[2][2], int *score, int *nombre_de_question, cJSON *json, cJSON *Profil_json) {
	printf("score: %d", *score);
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
    (*nombre_de_question) = nombre;
            
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Nettoyage indispensable

    for(int i = 0; i < nombre; i++)
    {
		int value = -2;
		if ((choix[0][0] && choix[0][1]) || (choix[1][0] && choix[1][1])) {
			int temp_int = rand()%2;
			if (!temp_int && choix[0][0] && choix[0][1]) {
				value = question_english(json);
			} else if (temp_int && choix[1][0] && choix[1][1]) {
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
				exit(0);
            case 1: 
   	            (*score)++;
   	            break;
       	    case 0: 
           	    break;
            case -1:
   	            (*score)--;
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
void quiz_infini(int choix[2][2], int *score, int *nombre_de_question, cJSON *json, cJSON *Profil_json)
{
	printf("score: %d", *score);
    int continu = 1;
    int value = -2;
    while(continu)
    {
		if ((choix[0][0] && choix[0][1]) || (choix[1][0] && choix[1][1])) {
			int temp_int = rand()%2;
			if (!temp_int && choix[0][0] && choix[0][1]) { // bouton anglais et verb active
				value = question_english(json);
			} else if (temp_int && choix[1][0] && choix[1][1]) {
				int a;
				int b;
				char op;
				int result;
				random_value(&a, &b, &op);
				result = opperation_basic(a, b, op);
				value = question_math(a, b, op, result);
			} else {
				value = 0;
				(*nombre_de_question)--;
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
				exit(0);
            case 1: 
   	            (*score)++;
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
