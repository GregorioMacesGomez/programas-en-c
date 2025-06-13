#include <stdio.h>
#include <string.h>

int main() {
    char a[20] = "hola ";    // Cadena base (con espacio suficiente)
    char b[] = "mundo";      // Cadena que se va a pegar
    strcat(a, b);            // Une b al final de a
    printf("%s\n", a);       // Imprime el resultado
    return 0;
}

// junta el valor de a y b con la funcion y la guarda dentro de a y al iinal imprime toda la cadena concatenada y guardada en a 