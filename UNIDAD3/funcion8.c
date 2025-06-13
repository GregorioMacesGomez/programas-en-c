#include <stdio.h>
#include <string.h>

int main() {
    char a[] = "uno,dos,tres";       // Cadena con separadores
    char *p = strtok(a, ",");        // Primer token separado por coma
    while (p) {
        printf("%s\n", p);           // Imprime cada parte
        p = strtok(NULL, ",");       // Siguiente parte
    }
    return 0;
}
//divide una cadena en partes (tokens) según un delimitador que en este caso asigne  la ","