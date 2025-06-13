#include <stdio.h>
#include <string.h>

int main() {
    char a[] = "hola";       // Cadena de origen
    char b[10];              // Cadena de destino (espacio suficiente)
    strcpy(b, a);            // Copia el contenido de a en b
    printf("%s\n", b);       // Imprime b
    return 0;
}

//este codigo lee el vlaor de la primera cadera, despues le asigna su contenido a la otra variable que igual sea de cadena
//imprime la segunda cadena