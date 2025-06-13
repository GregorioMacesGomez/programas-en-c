#include <stdio.h>

void hanoi(char torre1, char torre2, char torre3, int disco) {
    if (disco == 1) {
        printf("Mover disco 1 desde torre %c a torre %c\n", torre1, torre3);
    } else {
        hanoi(torre1, torre3, torre2, disco - 1);
        printf("Mover disco %d desde torre %c a torre %c\n", disco, torre1, torre3);
        hanoi(torre2, torre1, torre3, disco - 1);
    }
}

int main() {
    int discos;
    char torre1, torre2, torre3;

    printf("Ingrese número de discos: ");
    scanf("%d", &discos);

    if (discos < 1) {
        printf("Número de discos inválido.\n");
        return 1;
    }

    printf("Nombre de la Torre 1: ");
    scanf(" %c", &torre1);  

    printf("Nombre de la Torre 2: ");
    scanf(" %c", &torre2);

    printf("Nombre de la Torre 3: ");
    scanf(" %c", &torre3);

    printf("\nMovimientos necesarios:\n");
    hanoi(torre1, torre2, torre3, discos);

    return 0;
}
