#include <stdio.h>
#include <string.h>

int main() {
    char a[] = "hola";       // Primera cadena
    char b[] = "hola";       // Segunda cadena
    if (strcmp(a, b) == 0) { // Compara si son iguales
        printf("iguales\n");
    } else {
        printf("diferentes\n");
    }
    return 0;
}

//verifica si a y b tienen el mismo valor y medinate un if se puede verificar para ver si son iguales o no