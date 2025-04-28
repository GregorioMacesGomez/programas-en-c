#include <stdio.h>
int main (){
    printf("%s\n", "seleccione una opcion");
    printf("%s\n", "a) Seleccionar opcion 1");
    printf("%s\n", "b) seleccionar opcion 2");
    char opc;
    scanf("%c", &opc);
    switch (opc)
    {
    case 'a':
        printf ("%s\n", "seleccione opc1");
        break;
    case 'b':
        printf("%s\n", "selecciona opc 2");
        break;
    default:
        printf("%s\n", "Opcion invalida");
        break;
    }
    return 0;
}