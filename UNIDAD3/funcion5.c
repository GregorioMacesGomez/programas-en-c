#include <stdio.h>
#include <string.h>

int main() {
    char a[] = "hola";
    char b[] = "holi";
    if (strncmp(a, b, 3) == 0) {  // Compara solo los primeros 3 caracteres
        printf("iguales\n");
    } else {
        printf("diferentes\n");
    }
    return 0;
}

//Hace casi lo mismo de la funcion pasada pero no compara toda la cadena solo los primeros 3 caracteres
//esto depende de cuantos caracteres quiere que compare 