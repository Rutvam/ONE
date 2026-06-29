#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include "./gestion_des_quiz.h"
#include "./funktion.h"
#include "../MATIERE/ENGLISH/english.h"
#include "../MATIERE/MATH/math.h"

void table_des_matiere(int choix[3][2])
{
	char off[22] = "\033[1;31mOFF\033[0m";
	char on[21] = "\033[1;32mON\033[0m";
	char state[2][22] = {"\033[1;31mOFF\033[0m", "\033[1;32mON\033[0m"};
	char answer_char;

	int condition = 0;
	while (!condition)
	{
		clear();
		switch (choix[1][0])
		{
			case 0:
				printf("[1] English: %s\n", off);
				break;
			case 1:
				printf("[1] English: %s\n", on);
				printf("\t[a] verb: %s\n", state[choix[1][1]]);
				break;
		}

		switch (choix[2][0])
		{
			case 0:
				printf("[2] math: %s\n", off);
				break;
			case 1:
				printf("[2] math: %s\n", on);
				printf("\t[a] basic (+ - * /): %s\n", state[choix[2][1]]);
				break;
		}
			
		printf("[n] mode normal: %s\n", state[ choix[0][1] ]);
		printf("[i] mode infini: %s\n", state[ choix[0][0] ]);
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
						choix[1][1] = !choix[1][1];
						break;
					case '2':
						choix[2][1] = !choix[2][1];
						break;
				};
				break;
			case 'c':
				if ((choix[1][0] && choix[1][1]) || (choix[2][0] && choix[2][1])) {
					condition = 1;
				} else {
					printf("Erreur: choisier une matière");
				};
				break;
			case 'i':
				choix[0][0] = !choix[0][0];
				choix[0][1] = !choix[0][1];
				break;
			case 'n':
				choix[0][0] = !choix[0][0];
				choix[0][1] = !choix[0][1];
				break;
			case '1':
				choix[1][0] = !choix[1][0];
				break;
			case '2':
				choix[2][0] = !choix[2][0];
				break;
		}
	}
}

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
	printf("score: %d\n", *score);
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
	printf("score: %d\n", *score);
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
