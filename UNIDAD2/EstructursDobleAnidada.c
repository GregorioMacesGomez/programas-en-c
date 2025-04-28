#include <stdio.h>

struct Coordenadas {
    float latitud;
    float longitud;
};

struct Direccion {
    struct Coordenadas coords;
    char calle[50];
};

struct Estudiante {
    struct Direccion direccion;
    char nombre[50];
};

int main() {
    struct Estudiante estudiante;
    
    printf("Ingrese el nombre del estudiante: ");
    scanf("%s", estudiante.nombre);
    
    printf("Ingrese la calle: ");
    scanf("%s", estudiante.direccion.calle);
    
    printf("Ingrese la latitud: ");
    scanf("%f", &estudiante.direccion.coords.latitud);
    
    printf("Ingrese la longitud: ");
    scanf("%f", &estudiante.direccion.coords.longitud);
    
    // Imprimir valores ingresados
    printf("\nDatos del estudiante:\n");
    printf("Nombre: %s\n", estudiante.nombre);
    printf("Calle: %s\n", estudiante.direccion.calle);
    printf("Latitud: %.4f, Longitud: %.4f\n", estudiante.direccion.coords.latitud, estudiante.direccion.coords.longitud);
    
    return 0;
}

