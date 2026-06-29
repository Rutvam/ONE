#include <cjson/cJSON.h>
#ifndef GESTION_DES_QUIZ_H
#define GESTION_DES_QUIZ_H

void table_des_matiere(int choix[3][2]);
void gamification(int *score, int *score_max, int *level, int *xp, int nombre_de_question, char mode);
void quiz_normal(int choix[3][2], int *score, int *nombre_de_question, cJSON *json, cJSON *Profil_json);
void quiz_infini(int choix[3][2], int *score, int *nombre_de_question, cJSON *json, cJSON *Profil_json);

#endif
