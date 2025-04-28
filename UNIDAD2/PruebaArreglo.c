#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

int main (){
    setlocale(LC_ALL,"");

    int numeros [] = {12,20,30,40};
    int size = sizeof (numeros)/ sizeof(numeros[0]);

    printf("Tamaño: %d\n", size);
    for (int i = 0; i<size; i++){
        printf("numeros[%d] = %d\n", i, numeros[i]);
    }
    return EXIT_SUCCESS;
}