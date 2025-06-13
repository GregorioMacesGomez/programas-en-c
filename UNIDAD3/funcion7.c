#include <stdio.h>
#include <string.h>

int main() {
    char a[] = "hola mundo";
    char *p = strstr(a, "mun");   // Busca la subcadena "mun"
    if (p) {
        printf("%s\n", p);        // Imprime desde "mun" hasta el final
    }
    return 0;
}

// Hace casi lo mismo que la funcion pasada