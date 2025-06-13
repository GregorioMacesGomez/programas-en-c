#include <stdio.h>
#include <string.h>

int main() {
    char a[] = "casa";
    char *p = strrchr(a, 'a');   // Busca la última 'a'
    if (p) {
        printf("%s\n", p);       // Imprime desde la última 'a'
    }
    return 0;
}
//busca la última aparición de un carácter en la cadena en este caso yo elegi la a porque aparece 2 veces 
//pero puede ser cualquer letra 