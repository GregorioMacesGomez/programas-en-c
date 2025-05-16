#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

// Función para cambiar el color
void setColor(const char* color) {
    printf("%s",color);
}

int main() {
    FILE *file;
    char nombre[MAX][MAX];
    int edad[MAX];
    char pais[MAX][MAX];
    int cantidad, i;
    char archivo;

    // Abrir el archivo 
    file = fopen("../2salida.csv", "w");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    gotoxy(10, 5);
    printf("Ingrese como quiere que se llame el archivo: ");
    scanf("%s", &archivo);
    getchar(); 
    printf("\033[2J"); // Limpia la pantalla

    printf("\033[2J"); // Limpia la pantalla
    gotoxy(10, 5);
    printf("Ingrese la cantidad de personas: ");
    scanf("%d", &cantidad);
    getchar(); 

    printf("\033[2J"); // Limpia la pantalla

    


    // Pedir datos de las personas
    for (i = 0; i < cantidad; i++) {
        printf("Persona: %d\n", i + 1);

        setColor("\033[44m"); 
        printf("Nombre: ");
        fgets(nombre[i], MAX, stdin);
        nombre[i][strcspn(nombre[i], "\n")] = 0; 
        setColor("\033[0m");


        setColor("\033[42m"); 
        printf("Edad: ");
        scanf("%d", &edad[i]);
        getchar(); 
        setColor("\033[0m");


        setColor("\033[45m"); 
        printf("Pais: ");
        fgets(pais[i], MAX, stdin);
        pais[i][strcspn(pais[i], "\n")] = 0;
        setColor("\033[0m");


        printf("\033[2J"); // Limpia la pantalla
        printf("\n");

    }

    printf("\033[2J"); // Limpia la pantalla

    // Imprimir la tabla
    int ancho = 50;
    for (i = 0; i < ancho; i++) printf("*");
    printf("\n");
    printf("* %-15s * %-5s * %-15s *\n", "Nombre", "Edad", "Pais");
    for (i = 0; i < ancho; i++) printf("*");
    printf("\n");

    for (i = 0; i < cantidad; i++) {
        printf("* %-15s * %-5d * %-15s *\n", nombre[i], edad[i], pais[i]);
    }

    for (i = 0; i < ancho; i++) printf("*");
    printf("\n");

    fprintf(file, "Nombre,Edad,Pais\n");
    for (i = 0; i < cantidad; i++) {
        fprintf(file, "%s,%d,%s\n", nombre[i], edad[i], pais[i]);
    }

    fclose(file);

    printf("\nArchivo '3salida.csv' creado exitosamente.\n");

    return 0;
}
