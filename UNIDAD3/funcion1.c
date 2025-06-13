#include <stdio.h>      // Librería para printf
#include <string.h>     // Librería para usar strlen

int main() {
    char texto[] = "hola";       // Creamos una cadena
    int len = strlen(texto);     // strlen mide cuántos caracteres tiene
    printf("%d\n", len);         // Imprime el resultado
    return 0;
}
//lee la cadena y cuenta las letras y luego imprime el numero de letras que tiene 