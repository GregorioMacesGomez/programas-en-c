#include <stdio.h> // Librería estándar para entrada y salida
#include <math.h>  // Librería matemática para cálculos

// Estructura para almacenar datos del rectángulo
struct Cuadrilatero {
    float a1, b1, a2, b2, a3, b3, a4, b4; // Coordenadas de los vértices
    float lado1, lado2, lado3, lado4, perimetro, area; // Variables para cálculos
};

// Estructura para almacenar datos del triángulo
struct Tri {
    float p1, q1, p2, q2, p3, q3; // Coordenadas de los vértices
    float ladoA, ladoB, ladoC, perimetro, area; // Variables para cálculos
};

int main() {
    int seleccion; // Variable para la opción del usuario
    printf("Seleccione una figura para calcular su perímetro y área:\n"); // Mensaje al usuario
    printf("1. Rectángulo\n"); // Opción 1
    printf("2. Triángulo\n"); // Opción 2
    scanf("%d", &seleccion); // Leer la opción ingresada

    switch (seleccion) { // Evaluar la opción seleccionada
        case 1: { // Caso para el rectángulo
            struct Cuadrilatero rect; // Declarar estructura para el rectángulo
            printf("Ingrese las coordenadas del rectángulo:\n"); // Pedir coordenadas
            printf("a1: "); scanf("%f", &rect.a1); // Leer coordenada a1
            printf("b1: "); scanf("%f", &rect.b1); // Leer coordenada b1
            printf("a2: "); scanf("%f", &rect.a2); // Leer coordenada a2
            printf("b2: "); scanf("%f", &rect.b2); // Leer coordenada b2
            printf("a3: "); scanf("%f", &rect.a3); // Leer coordenada a3
            printf("b3: "); scanf("%f", &rect.b3); // Leer coordenada b3
            printf("a4: "); scanf("%f", &rect.a4); // Leer coordenada a4
            printf("b4: "); scanf("%f", &rect.b4); // Leer coordenada b4
            
            // Calcular la longitud de cada lado del rectángulo
            rect.lado1 = sqrt(pow(rect.a2 - rect.a1, 2) + pow(rect.b2 - rect.b1, 2));
            rect.lado2 = sqrt(pow(rect.a3 - rect.a2, 2) + pow(rect.b3 - rect.b2, 2));
            rect.lado3 = sqrt(pow(rect.a4 - rect.a3, 2) + pow(rect.b4 - rect.b3, 2));
            rect.lado4 = sqrt(pow(rect.a1 - rect.a4, 2) + pow(rect.b1 - rect.b4, 2));
            rect.perimetro = rect.lado1 + rect.lado2 + rect.lado3 + rect.lado4; // Calcular el perímetro
            rect.area = rect.lado1 * rect.lado2; // Calcular el área
            
            // Mostrar resultados
            printf("Perímetro del rectángulo: %.2f\n", rect.perimetro);
            printf("Área del rectángulo: %.2f\n", rect.area);
            break;
        }
        case 2: { // Caso para el triángulo
            struct Tri triangulo; // Declarar estructura para el triángulo
            printf("Ingrese las coordenadas del triángulo:\n"); // Pedir coordenadas
            printf("p1: "); scanf("%f", &triangulo.p1); // Leer coordenada p1
            printf("q1: "); scanf("%f", &triangulo.q1); // Leer coordenada q1
            printf("p2: "); scanf("%f", &triangulo.p2); // Leer coordenada p2
            printf("q2: "); scanf("%f", &triangulo.q2); // Leer coordenada q2
            printf("p3: "); scanf("%f", &triangulo.p3); // Leer coordenada p3
            printf("q3: "); scanf("%f", &triangulo.q3); // Leer coordenada q3
            
            // Calcular la longitud de cada lado del triángulo
            triangulo.ladoA = sqrt(pow(triangulo.p2 - triangulo.p1, 2) + pow(triangulo.q2 - triangulo.q1, 2));
            triangulo.ladoB = sqrt(pow(triangulo.p3 - triangulo.p2, 2) + pow(triangulo.q3 - triangulo.q2, 2));
            triangulo.ladoC = sqrt(pow(triangulo.p1 - triangulo.p3, 2) + pow(triangulo.q1 - triangulo.q3, 2));
            triangulo.perimetro = triangulo.ladoA + triangulo.ladoB + triangulo.ladoC; // Calcular el perímetro
            
            // Calcular el área utilizando la fórmula determinante
            triangulo.area = fabs((triangulo.p1 * (triangulo.q2 - triangulo.q3) + triangulo.p2 * (triangulo.q3 - triangulo.q1) + triangulo.p3 * (triangulo.q1 - triangulo.q2)) / 2);
            
            // Mostrar resultados
            printf("Perímetro del triángulo: %.2f\n", triangulo.perimetro);
            printf("Área del triángulo: %.2f\n", triangulo.area);
            break;
        }
        default:
            printf("Opción no válida.\n"); // Mensaje de error si la opción no es válida
    }
    return 0; // Finalizar programa
}
