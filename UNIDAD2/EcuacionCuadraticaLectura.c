#include <stdio.h> // Incluir librería estándar para entrada y salida
#include <math.h> // Incluir librería matemática para cálculos
#include <string.h> // Incluir librería para manipulación de cadenas

// Definir estructura para la ecuación cuadrática
struct Ecuacion {
    int coefA; // Coeficiente a
    int coefB; // Coeficiente b
    int coefC; // Coeficiente c
    int disc; // Discriminante
    float raiz1; // Primera raíz
    float raiz2; // Segunda raíz
    char estado[30]; // Estado de la solución
};

int main() { // Función principal
    int cantidad; // Variable para almacenar la cantidad de ecuaciones
    printf("Ingrese el número de ecuaciones a resolver: "); // Solicitar cantidad
    scanf("%d", &cantidad); // Leer la cantidad ingresada

    struct Ecuacion lista[cantidad]; // Declarar arreglo de estructuras

    for (int i = 0; i < cantidad; i++) { // Ciclo para leer coeficientes
        printf("Ingrese los valores de la ecuación %d:\n", i + 1); // Indicar ecuación
        printf("a: "); scanf("%d", &lista[i].coefA); // Leer coefA
        printf("b: "); scanf("%d", &lista[i].coefB); // Leer coefB
        printf("c: "); scanf("%d", &lista[i].coefC); // Leer coefC
    }

    for (int i = 0; i < cantidad; i++) { // Ciclo para calcular soluciones
        lista[i].disc = (lista[i].coefB * lista[i].coefB) - (4 * lista[i].coefA * lista[i].coefC); // Calcular discriminante
        if (lista[i].disc < 0) { // Si no hay solución real
            strcpy(lista[i].estado, "SIN SOLUCION"); // Asignar estado
            lista[i].raiz1 = 0; // No hay raíz 1
            lista[i].raiz2 = 0; // No hay raíz 2
        } else { // Si hay solución real
            lista[i].raiz1 = (-lista[i].coefB + sqrt(lista[i].disc)) / (2 * lista[i].coefA); // Calcular raíz 1
            lista[i].raiz2 = (-lista[i].coefB - sqrt(lista[i].disc)) / (2 * lista[i].coefA); // Calcular raíz 2
            strcpy(lista[i].estado, "SOLUCION EXISTE"); // Asignar estado
        }
    }
    
    printf("\na\tb\tc\tx1\tx2\tEstado\n"); // Encabezado de tabla
    for (int i = 0; i < cantidad; i++) { // Ciclo para imprimir resultados
        printf("%d	%d	%d	%.2f	%.2f	%s\n", lista[i].coefA, lista[i].coefB, lista[i].coefC, lista[i].raiz1, lista[i].raiz2, lista[i].estado); // Imprimir valores
    }

    return 0; // Finalizar programa
}
