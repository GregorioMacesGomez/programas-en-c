#include <stdio.h>
#include <string.h>

int main() {
    char a[] = "hola";              // Cadena origen
    char b[10];                     // Cadena destino
    memcpy(b, a, 5);                // Copia 5 bytes (incluye '\0')
    printf("%s\n", b);              // Imprime lo copiado
    return 0;
}
//copia bloques de memoria (puede ser texto, arrays, etc).