#include <stdio.h>

int sumaEnteros(int number) {
    if (number == 1)
        return 1;
    else
        return number + sumaEnteros(number - 1);
}

int main() {
    int n;

    printf("Ingrese número a sumar: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Error: Ingrese un número válido mayor a 0...\n");
        return 1;
    }

    int resultado = sumaEnteros(n);
    printf("La suma de los números desde 1 hasta %d es: %d\n", n, resultado);

    return 0;
}
