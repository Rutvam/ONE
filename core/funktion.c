#include <stdio.h>

void clear()
{
    printf("\033[H\033[2J");
    fflush(stdout);
}
