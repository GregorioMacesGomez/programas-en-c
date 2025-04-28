#include <stdio.h>

struct Duennio {
    char nombre[50];
    char apellido[50];
    int edad;
    char gradoestudio[50];
    char direccion[50];
};

struct Mochila {
    char color[50];
    char marca[50];
    char tamannio[50];
    int cierre;
    int correas;
    int numerobolsas;
    char portalaptop[50];
    struct Duennio duennio;
};

int main() {
    int n;

    printf("Ingrese el numero de personas con mochila: ");
    scanf("%d", &n);
    getchar(); 

    struct Mochila mochilas[n]; 

    for (int i = 0; i < n; i++) {
        printf("\nIngrese los datos del Dueño %d\n", i + 1);

        printf("Nombre: ");
        scanf(" %[^\n]", mochilas[i].duennio.nombre);

        printf("Apellido: ");
        scanf(" %[^\n]", mochilas[i].duennio.apellido);

        printf("Edad: ");
        scanf("%d", &mochilas[i].duennio.edad);
        getchar(); 

        printf("Grado de Estudio: ");
        scanf(" %[^\n]", mochilas[i].duennio.gradoestudio);

        printf("Direccion: ");
        scanf(" %[^\n]", mochilas[i].duennio.direccion);

        printf("Color de la Mochila: ");
        scanf(" %[^\n]", mochilas[i].color);

        printf("Ingrese marca: ");
        scanf(" %[^\n]", mochilas[i].marca);

        printf("Ingrese el tamaño (Chica, Mediana, Grande): ");
        scanf(" %[^\n]", mochilas[i].tamannio);

        printf("Ingrese numero de cierres: ");
        scanf("%d", &mochilas[i].cierre);

        printf("Ingrese Numero de Correas: ");
        scanf("%d", &mochilas[i].correas);

        printf("Numero de bolsas: ");
        scanf("%d", &mochilas[i].numerobolsas);

        printf("¿Tiene portalaptop? (si/no): ");
        scanf(" %[^\n]", mochilas[i].portalaptop);
    }

    // Encabezado de la tabla
    printf("\n%-10s | %-10s | %-5s | %-20s | %-15s | %-10s | %-10s | %-10s | %-6s | %-7s | %-7s | %-15s\n", 
        "Nombre", "Apellido", "Edad", "Grado de Estudio", "Direccion", "Color", "Marca", "Tamaño", "Cierre", "Correas", "Bolsas", "Portalaptop");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Impresión de datos
    for (int i = 0; i < n; i++) {
        printf("%-10s | %-10s | %-5d | %-20s | %-15s | %-10s | %-10s | %-10s | %-6d | %-7d | %-7d | %-15s\n",
            mochilas[i].duennio.nombre,
            mochilas[i].duennio.apellido,
            mochilas[i].duennio.edad,
            mochilas[i].duennio.gradoestudio,
            mochilas[i].duennio.direccion,
            mochilas[i].color,
            mochilas[i].marca,
            mochilas[i].tamannio,
            mochilas[i].cierre,
            mochilas[i].correas,
            mochilas[i].numerobolsas,
            mochilas[i].portalaptop);
    }

    return 0;
}