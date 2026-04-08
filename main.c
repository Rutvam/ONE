#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define PYTHON_CMD "python"
    #define CALCUL_CMD "gcc -shared -fPIC MATIERE\\MATH\\calcule.c -o MATIERE\\MATH\\calcule.dll -lm"
#elif __linux__
    #define PYTHON_CMD "python3"
    #define CALCUL_CMD "gcc -shared -fPIC MATIERE/MATH/calcule.c -o MATIERE/MATH/calcule.so -lm"
#elif __APPLE__
    #define PYTHON_CMD "python3"
    #define CALCUL_CMD "gcc -shared -fPIC -o MATIERE/MATH/calcule.dylib MATIERE/MATH/calcule.c -lm"
#else
    #error "Unsupported OS"
#endif

int main(void) {
    int ret;

    printf("INFO: Compilation of calcule.c\n");
    ret = system(CALCUL_CMD);
    if (ret != 0) {
        printf("ERROR: Compilation of calcule.c failed (code %d)\n", ret);
        return 1;
    }

    char command[512];
    snprintf(command, sizeof(command), "%s main_def.py %s \"%s\"", PYTHON_CMD, "true", "{}");

    ret = system(command);
    if (ret != 0) {
        printf("ERROR: Python script execution failed (code %d)\n", ret);
        return 1;
    }

    return 0;
}