#include <stdio.h>

struct Estudiante
{
    char nombre[50];
    char grupo[50];
    int matricula;
    int edad;
    char correo[50];
    char direccion[50];
    char rutaulsabus[50];
    float promedioGeneral;
};

int main()
{
    struct Estudiante estudiante1;

    int size;
    printf("Ingrese el tamannio del arreglo; \n");
    scanf("%d", &size);
    struct Estudiante estudiante [size];
    for (int i = 0; i < size; i++)
    {
        printf("ingrese su nombre: ");
        scanf("%s", estudiante1.nombre);

        printf("ingrese su grupo: ");
        scanf("%s", estudiante1.grupo);

        printf("ingrese su matricula: ");
        scanf("%d", estudiante1.matricula);

        printf("ingrese su edad: ");
        scanf("%d", &estudiante1.edad);

        printf("ingrese su correo: ");
        scanf("%s", estudiante1.correo);

        printf("ingrese su direccion: ");
        scanf("%s", estudiante1.direccion);

        printf("ingrese su ruta de ulsabus: ");
        scanf("%s", estudiante1.rutaulsabus);

        printf("ingrese su promedio general: ");
        scanf("%f", estudiante1.promedioGeneral);
        estudiante[i] = estudiante1;

    }
    printf("\nDatos de los estudiantes:\n");
    for (int i = 0; i < size; i++) {
        printf("\nEstudiante %d\n", i + i++);
        printf("Nombre: %s\n", estudiante[i].nombre);
        printf("Grupo: %s\n", estudiante[i].grupo);
        printf("Matricula: %d\n", estudiante[i].matricula);
        printf("Edad: %d\n", estudiante[i].edad);
        printf("Correo: %s\n", estudiante[i].correo);
        printf("Direccion: %s\n", estudiante[i].direccion);
        printf("Ruta Ulsabus: %s\n", estudiante[i].rutaulsabus);
        printf("Promedio General: %.2f\n", estudiante[i].promedioGeneral);
    }
    return 0;
    
}