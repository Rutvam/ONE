#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void random_value(int *a, int *b, char *op)
{
	int op_temp;
	op_temp = rand()%0x04;
	if (op_temp == 3) {
		int pro_temp = rand()%2;
		int entier = 20-(rand()%40);
		if (!entier) {entier = 1;}
		int c = 20-(rand()%40);
		if (!pro_temp) {
			*b = entier;
			*a = entier * c;
			*op = '/';
		} else {
			*b = c;
			*a = *b * c;
			*op = '/';
		}
	} else if (op_temp == 2) {
		int pro_temp = rand()%2;
		if (!pro_temp) {
			*a = 20-(rand()%40);
			*b = 20-(rand()%40);
			*op = '*';
		} else {
			int entier = 20-(rand()%40);
			*a = entier;
			*b = entier;
			*op = '*';
		}
	} else if (op_temp) {
		*a = 100-(rand()%200);
		*b = 100-(rand()%200);
		*op = '-';
	} else if (!op_temp) {
		*a = 100-(rand()%200);
		*b = 100-(rand()%200);
		*op = '+';
	}
}

void agrandir_calcul(char calcul[100], int etapes)
{
    // On commence avec un nombre de départ (ex: 7)
    int nombre_depart = 7;
    snprintf(calcul, 100, "%d", nombre_depart);

    char temporaire[100];

    for (int i = 0; i < etapes; i++)
    {
        int op_choix = rand() % 3; // Choix de l'opération pour agrandir

        switch (op_choix)
        {
            case 0:
                // Étape d'addition : "7" devient "(7 + 110)"
                int val_add = rand() % 200;
                snprintf(temporaire, 100, "(%s + %d)", calcul, val_add);
                break;

            case 1:
                // Étape de multiplication : "7" devient "(111 * 7)"
                int val_mult = rand() % 12 + 2;
                snprintf(temporaire, 100, "(%d * %s)", val_mult, calcul);
                break;

            case 2:
                // Étape plus complexe (ex: ajouter une puissance ou fonction)
                // "(expression)" devient "2 * ((expression) + 5)"
                snprintf(temporaire, 100, "2 * (%s + 5)", calcul);
                break;
        }

        // On recopie le résultat agrandi dans notre variable principale
        strncpy(calcul, temporaire, 100);
    }
}

int opperation_basic(int a, int b, char op)
{
	if (op == '+') {
		return a + b;
	} else if (op == '-') {
		return a - b;
	} else if (op == '*') {
		return a * b;
	} else if (op == '/') {
		return a / b;
	} else {
		return 0;
	}
}

int input(char answer[50])
{
    int result = 0;
    int state = 1; // On commence à 1 pour entrer au moins une fois dans la boucle

    while (state)
    {
        // 1. On demande la saisie de l'étape à l'intérieur du while
        scanf("%49s", answer);

        int len = strlen(answer);
        int i = 0;
        for (int j = 0; j >= 49; j++)
        {
        	if (answer[j] == '(')
        	{
				int k = i + 1;
        		while (answer[k] != ')')
        		{
	        		// 2. Gérer le signe du TOUT PREMIER nombre (ex: -5 ou 12)
    	    		int signe_initial = 1;
        			if (answer[i] == '-') {
        			    signe_initial = -1;
        			    i++;
        			} else if (answer[i] == '+') {
        		    	i++;
        			}

        			// 3. Lire le premier nombre
        			int premier_nombre = 0;
        			while (i < len && answer[i] >= '0' && answer[i] <= '9') {
        		    	premier_nombre = (premier_nombre * 10) + (answer[i] - '0');
        		    	i++;
        			}
        			result = premier_nombre * signe_initial;

        			// 4. Parcourir le reste de la chaîne pour les opérations
        			while (i < len) {
        		    	if (answer[i] == '+') {
        		        	i++;
        		        	int valeur_droite = 0;
        		        	while (i < len && answer[i] >= '0' && answer[i] <= '9') {
        		            	valeur_droite = (valeur_droite * 10) + (answer[i] - '0');
        		            	i++;
        		        	}
        		        	result += valeur_droite;
        		    	} 
        		    	else if (answer[i] == '-') {
        		        	i++;
        		        	int valeur_droite = 0;
        		        	while (i < len && answer[i] >= '0' && answer[i] <= '9') {
        		            	valeur_droite = (valeur_droite * 10) + (answer[i] - '0');
        		            	i++;
        		        	}
        		        	result -= valeur_droite;
        		    	}
        		    	else {
        		        	i++; 
        		    	}
        			}

        			// 5. MISE À JOUR DE STATE : On vérifie si l'utilisateur a encore écrit un opérateur 
        			// ou s'il a juste donné le résultat final.
        			state = 0; // Par défaut on suppose qu'il a fini (ex: il a juste écrit un nombre entier)
        		
        			// On affiche l'état actuel du calcul pour aider l'utilisateur
        			printf("[Étape intermédiaire = %d] Continuer le calcul ou donner la réponse finale :\n>> ", result);
        		
        			// On inspecte la chaîne actuelle (jusqu'à sa vraie longueur 'len', pas 50 !)
        			for(int j = 0; j < len; j++)
        			{
        		    	if(answer[j] == '+' || answer[j] == '-' || answer[j] == '*' || answer[j] == '/') {
        		    	    state = 1; // Il y a encore un calcul à faire, on va reboucler !
        		    	}
        			}
        			k++;
    			}	
        	}
        }

        // 2. Gérer le signe du TOUT PREMIER nombre (ex: -5 ou 12)
        int signe_initial = 1;
        if (answer[i] == '-') {
            signe_initial = -1;
            i++;
        } else if (answer[i] == '+') {
            i++;
        }

        // 3. Lire le premier nombre
        int premier_nombre = 0;
        while (i < len && answer[i] >= '0' && answer[i] <= '9') {
            premier_nombre = (premier_nombre * 10) + (answer[i] - '0');
            i++;
        }
        result = premier_nombre * signe_initial;

        // 4. Parcourir le reste de la chaîne pour les opérations
        while (i < len) {
            if (answer[i] == '+') {
                i++;
                int valeur_droite = 0;
                while (i < len && answer[i] >= '0' && answer[i] <= '9') {
                    valeur_droite = (valeur_droite * 10) + (answer[i] - '0');
                    i++;
                }
                result += valeur_droite;
            } 
            else if (answer[i] == '-') {
                i++;
                int valeur_droite = 0;
                while (i < len && answer[i] >= '0' && answer[i] <= '9') {
                    valeur_droite = (valeur_droite * 10) + (answer[i] - '0');
                    i++;
                }
                result -= valeur_droite;
            }
            else {
                i++; 
            }
        }

        // 5. MISE À JOUR DE STATE : On vérifie si l'utilisateur a encore écrit un opérateur 
        // ou s'il a juste donné le résultat final.
        state = 0; // Par défaut on suppose qu'il a fini (ex: il a juste écrit un nombre entier)
        
        // On affiche l'état actuel du calcul pour aider l'utilisateur
        printf("[Étape intermédiaire = %d] Continuer le calcul ou donner la réponse finale :\n>> ", result);
        
        // On inspecte la chaîne actuelle (jusqu'à sa vraie longueur 'len', pas 50 !)
        for(int j = 0; j < len; j++)
        {
            if(answer[j] == '+' || answer[j] == '-' || answer[j] == '*' || answer[j] == '/') {
                state = 1; // Il y a encore un calcul à faire, on va reboucler !
            }
        }
    }

    return result; // Sortie de boucle : l'utilisateur a entré un nombre pur, on renvoie le score final
}

int question_math(int a, int b, char op, int result)
{
	if (a == b && op == '*') {
		printf("%d² = ", a);
	} else if (result == b && op == '/') {
		printf("√%d = ", a);
	} else {
		printf("%d %c %d = ", a, op, b);
	}
	char answer_char[50];
	int answer = input(answer_char);
	if (answer == result) {
		printf("\033[1;32mBonne reponse\033[0m\n\n");
		return 1;
	} else {
		printf("\033[1;31mMauvaise reponse:\033[0m %d\n\n", result);
		return -1;
	}
}
