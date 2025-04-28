#include <math.h>
#include <stdio.h>

struct Coordenada{
    int x;
    int y;
};

int main() {
    int opc;
    printf ("%s\n", "Selecciona una opcion: ");
    printf ("%s\n", "1. Cuadrado");
    printf ("%s\n", "2. Triangulo");
    scanf ("%d", &opc);

    switch (opc){
        case 1: //Cuadrado
        struct Coordenada arreglo [4];
        for (int i=0; i<=4; i++){
            int posicion= i+1;
            printf ("%s%d\n", "Ingrese cordenada x", posicion );
            scanf(" %d[^\n]", arreglo[i].x)
            printf ("%s%d\n", "Ingrese cordenada y", posicion );
            scanf(" %d[^\n]", arreglo[i].y)

        }
        float ab= sqrt(
            pow (arreglo[1].x - arreglo[0].x)+
            pow (arreglo[1].y - arreglo[0].y));
        
        float bc = sqrt(
            pow (arreglo[1].x - arreglo[0].x)+
            pow (arreglo[1].y - arreglo[0].y));
        
    }

}