#include <math.h>   // pour pow
#include <stdio.h>  // pour printf si besoin

double calculate_percentage(int correct_answers, int total_questions) {
    return (total_questions > 0) ? (double)correct_answers * 100.0 / total_questions : 0.0;
} 

int opperateur(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '#': return (int)pow(a, b);  // puissance a^b
        default:
            printf("Opérateur inconnu: %c\n", op);
            return 0; // valeur par défaut
    }
}