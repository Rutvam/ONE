/*
 * ONE - Application console d'entraînement multi-matières.
 *
 * Fichier principal qui gère :
 * - authentification
 * - sélection des matières/modes
 * - boucle de jeu (normal / infinite)
 * - intégration IA (INLL)
 *
 * Ce programme est prévu pour être compilé et exécuté depuis la ligne de commande.
 *
 * gcc -o main main.c
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int main(void) {
    const char *VERSION = "0.11.0";
    char answer[8];
    bool test = false;
    char command[256];

    printf("Lancer en mode test ? (y/n): ");
    if (fgets(answer, sizeof(answer), stdin) != NULL) {
        /* on ne garde que la première lettre */
        if (answer[0] == 'y' || answer[0] == 'Y') {
            test = true;
        } else if (answer[0] == 'n' || answer[0] == 'N') {
            test = false;
        } else {
            printf("Réponse invalide. Utilisation du mode normal par défaut.\n");
            test = false;
        }
    }

    /* Construire la commande pour lancer le script Python */
    sprintf(command, "python main_def.py %s \"%s\"", test ? "true" : "false", "{}");

    /* Exécuter le script Python */
    int result = system(command);
    if (result != 0) {
        printf("Erreur lors de l'exécution du script Python.\n");
        return 1;
    }

    return 0;
}
