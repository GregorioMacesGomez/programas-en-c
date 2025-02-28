#include <stdio.h>
int main (){
    int opc;
    int num1;
    int num2;
    int suma, resta, multi, div;
    printf("%s\n","seleccione una opcion");
    printf("%s\n","1-sumar");
    printf("%s\n","2-restar");
    printf("%s\n","3-multiplicacion");
    printf("%s\n","4-division");
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:
        printf("%s\n", "dame el primer numero");
        scanf("%d", &num1);
        printf("%s\n", "dame el segundo numero");
        scanf("%d", &num2);  
        suma=(num1+num2);
        printf("%s%d\n", "el resultado es:\t", suma);
        break;
    case 2:
        printf("%s\n", "dame el primer numero");
        scanf("%d", &num1);
        printf("%s\n", "dame el segundo numero");
        scanf("%d", &num2);  
        resta=(num1-num2);
        printf("%s%d\n", "el resultado es:\t", resta);
        break; 
    case 3:
        printf("%s\n", "dame el primer numero");
        scanf("%d", &num1);
        printf("%s\n", "dame el segundo numero");
        scanf("%d", &num2);  
        multi=(num1*num2);
        printf("%s%d\n", "el resultado es:\t", multi);
        break;
    case 4:
        printf("%s\n", "dame el primer numero");
        scanf("%d", &num1);
        printf("%s\n", "dame el segundo numero");
        scanf("%d", &num2);  
        div=(num1/num2);
        printf("%s%d\n", "el resultado es:\t", div);
        break;
    default:
        printf("%s\n","no ha seleccionado una opcion valida");
        break;
    }
    return 0;
}