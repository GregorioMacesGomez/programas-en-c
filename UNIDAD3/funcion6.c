#include <stdio.h>
#include <string.h>

int main() {
    char a[] = "hola";
    char *p = strchr(a, 'o');   // Busca la primera 'o' en la cadena
    if (p) {
        printf("%s\n", p);      // Imprime desde esa letra hasta el final
    }
    return 0;
}
//Esta funcion lee la cadena que hayamos asignado antes, despues llmamos a la funcion y podemos
//escoger a partir de que letra le asignemos se imprima despues de esa letra