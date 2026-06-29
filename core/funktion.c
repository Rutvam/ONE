#include <stdio.h>
#include <string.h>

void clear()
{
    printf("\033[H\033[2J");
    fflush(stdout);
}

void argv_and_argc_search(int argc, char *argv[], int choix[3][2])
{
    char on[20] = "\033[1;32mON\033[0m";
    char off[21] = "\033[1;31mOFF\033[0m";
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
                choix[1][0] = 1;
                printf("ENGLISH: %s\n", on);
                if (j < argc && !strcmp(argv[j], "verb")) {
                	choix[1][1] = 1;
                	printf("\tVerb: %s\n", on);
                	i++;
                }
            } else if (!strcmp(argv[i], "math")) {
                choix[2][0] = 1;
                printf("MATH: %s\n", on);
                if (j < argc && !strcmp(argv[j], "basic")) {
                    choix[2][1] = 1;
                	printf("\tBasic (+ / * -): %s\n", on);
                }
            } else if (!strcmp(argv[i], "infini")) {
                choix[0][0] = 1;
                choix[0][1] = 0;
                printf("Mode Infini: %s\n", on);
                printf("Mode Normal: %s\n", off);
            } else if (!strcmp(argv[i], "normal")) {
                choix[0][1] = 1;
                choix[0][0] = 0;
                printf("Mode Normal: %s\n", on);
                printf("Mode Infini: %s\n", off);
            } else {
                printf("Warning: The argument \"%s\" is not recognized.\n", argv[i]);
            }
        }
    }
}
