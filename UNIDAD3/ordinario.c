#include <stdio.h>
#include <stdio.h>

#define MAX 10

struct Frac {
    int num, den;
};

typedef struct Frac Frac;

// Funciones auxiliares para fracciones
int mcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a < 0 ? -a : a;
}

Frac simplificar(Frac f) {
    int d = mcd(f.num, f.den);
    f.num /= d;
    f.den /= d;
    if (f.den < 0) {
        f.num = -f.num;
        f.den = -f.den;
    }
    return f;
}

Frac crear_frac(int num, int den) {
    Frac f = {num, den};
    return simplificar(f);
}

Frac suma(Frac a, Frac b) {
    return simplificar((Frac){a.num * b.den + b.num * a.den, a.den * b.den});
}

Frac resta(Frac a, Frac b) {
    return simplificar((Frac){a.num * b.den - b.num * a.den, a.den * b.den});
}

Frac multiplicar(Frac a, Frac b) {
    return simplificar((Frac){a.num * b.num, a.den * b.den});
}

Frac dividir(Frac a, Frac b) {
    return simplificar((Frac){a.num * b.den, a.den * b.num});
}

Frac opuesto(Frac a) {
    return crear_frac(-a.num, a.den);
}

Frac identidad() {
    return crear_frac(1, 1);
}

Frac cero() {
    return crear_frac(0, 1);
}

// Leer e imprimir matrices
void leer_matriz(Frac M[MAX][MAX], int r, int c, char nombre) {
    printf("Ingrese los valores de la matriz %c en formato a/b:\n", nombre);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int num, den;
            printf("%c[%d][%d] = ", nombre, i + 1, j + 1);
            scanf("%d/%d", &num, &den);
            M[i][j] = crear_frac(num, den);
        }
    }
}

void imprimir_matriz(Frac M[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d/%d\t", M[i][j].num, M[i][j].den);
        }
        printf("\n");
    }
}

// Transpuesta
void transpuesta(Frac A[MAX][MAX], Frac B[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            B[j][i] = A[i][j];
        }
    }
}

// Traza
Frac traza(Frac A[MAX][MAX], int n) {
    Frac tr = cero();
    for (int i = 0; i < n; i++) {
        tr = suma(tr, A[i][i]);
    }
    return tr;
}

// Suma y resta de matrices
void suma_matrices(Frac A[MAX][MAX], Frac B[MAX][MAX], Frac R[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            R[i][j] = suma(A[i][j], B[i][j]);
}

void resta_matrices(Frac A[MAX][MAX], Frac B[MAX][MAX], Frac R[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            R[i][j] = resta(A[i][j], B[i][j]);
}

// Producto de matrices
void producto_matrices(Frac A[MAX][MAX], Frac B[MAX][MAX], Frac R[MAX][MAX], int r1, int c1, int c2) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            R[i][j] = cero();
            for (int k = 0; k < c1; k++) {
                R[i][j] = suma(R[i][j], multiplicar(A[i][k], B[k][j]));
            }
        }
    }
}

// Determinante (recursivo por cofactores)
Frac determinante(Frac A[MAX][MAX], int n) {
    if (n == 1) return A[0][0];
    if (n == 2) {
        return resta(multiplicar(A[0][0], A[1][1]), multiplicar(A[0][1], A[1][0]));
    }
    Frac det = cero();
    Frac signo = identidad();
    Frac sub[MAX][MAX];
    for (int f = 0; f < n; f++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == f) continue;
                sub[subi][subj++] = A[i][j];
            }
            subi++;
        }
        Frac temp = multiplicar(signo, multiplicar(A[0][f], determinante(sub, n - 1)));
        det = suma(det, temp);
        signo = opuesto(signo);
    }
    return det;
}

int main() {
    Frac A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int r, c;

    printf("Introduce el numero de filas: ");
    scanf("%d", &r);
    printf("Introduce el numero de columnas: ");
    scanf("%d", &c);

    if (r > MAX || c > MAX || r < 1 || c < 1) {
        printf("Tamano invalido. Debe ser entre 1 y %d.\n", MAX);
        return 1;
    }

    leer_matriz(A, r, c, 'A');
    leer_matriz(B, r, c, 'B');

    printf("\nMatriz A:\n");
    imprimir_matriz(A, r, c);

    printf("\nMatriz B:\n");
    imprimir_matriz(B, r, c);

    // Transpuestas
    transpuesta(A, C, r, c);
    printf("\nTranspuesta A:\n");
    imprimir_matriz(C, c, r);

    transpuesta(B, C, r, c);
    printf("\nTranspuesta B:\n");
    imprimir_matriz(C, c, r);

    // Trazas (solo si es cuadrada)
    if (r == c) {
        printf("\nTraza A: %d/%d\n", traza(A, r).num, traza(A, r).den);
        printf("Traza B: %d/%d\n", traza(B, r).num, traza(B, r).den);

        // Determinantes
        Frac detA = determinante(A, r);
        Frac detB = determinante(B, r);
        printf("\nDeterminante A: %d/%d\n", detA.num, detA.den);
        printf("Determinante B: %d/%d\n", detB.num, detB.den);

        // Inversas posibles
        if (detA.num == 0) {
            printf("\nLa matriz A no tiene inversa porque su determinante es 0.\n");
        } else {
            printf("Matriz A es invertible.\n");
        }

        if (detB.num == 0) {
            printf("La matriz B no tiene inversa porque su determinante es 0.\n");
        } else {
            printf("Matriz B es invertible.\n");
        }
    } else {
        printf("\nLa matriz no es cuadrada, no se puede calcular traza, determinante ni inversa.\n");
    }

    // Suma
    suma_matrices(A, B, C, r, c);
    printf("\nA + B:\n");
    imprimir_matriz(C, r, c);

    // Resta
    resta_matrices(A, B, C, r, c);
    printf("\nA - B:\n");
    imprimir_matriz(C, r, c);

    // Producto (solo si columnas A == filas B)
    if (c == r) {
        producto_matrices(A, B, C, r, c, c);
        printf("\nA * B:\n");
        imprimir_matriz(C, r, c);
    } else {
        printf("\nNo se puede calcular el producto A*B porque el numero de columnas de A no coincide con el numero de filas de B.\n");
    }

    return 0;
}


struct Frac {
    int num, den;
};

typedef struct Frac Frac;

// Funciones auxiliares para fracciones
int mcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a < 0 ? -a : a;
}

Frac simplificar(Frac f) {
    int d = mcd(f.num, f.den);
    f.num /= d;
    f.den /= d;
    if (f.den < 0) {
        f.num = -f.num;
        f.den = -f.den;
    }
    return f;
}

Frac crear_frac(int num, int den) {
    Frac f = {num, den};
    return simplificar(f);
}

Frac suma(Frac a, Frac b) {
    return simplificar((Frac){a.num * b.den + b.num * a.den, a.den * b.den});
}

Frac resta(Frac a, Frac b) {
    return simplificar((Frac){a.num * b.den - b.num * a.den, a.den * b.den});
}

Frac multiplicar(Frac a, Frac b) {
    return simplificar((Frac){a.num * b.num, a.den * b.den});
}

Frac dividir(Frac a, Frac b) {
    return simplificar((Frac){a.num * b.den, a.den * b.num});
}

Frac opuesto(Frac a) {
    return crear_frac(-a.num, a.den);
}

Frac identidad() {
    return crear_frac(1, 1);
}

Frac cero() {
    return crear_frac(0, 1);
}

// Leer e imprimir matrices
void leer_matriz(Frac M[MAX][MAX], int r, int c, char nombre) {
    printf("Ingrese los valores de la matriz %c en formato a/b:\n", nombre);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int num, den;
            printf("%c[%d][%d] = ", nombre, i + 1, j + 1);
            scanf("%d/%d", &num, &den);
            M[i][j] = crear_frac(num, den);
        }
    }
}

void imprimir_matriz(Frac M[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d/%d\t", M[i][j].num, M[i][j].den);
        }
        printf("\n");
    }
}

// Transpuesta
void transpuesta(Frac A[MAX][MAX], Frac B[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            B[j][i] = A[i][j];
        }
    }
}

// Traza
Frac traza(Frac A[MAX][MAX], int n) {
    Frac tr = cero();
    for (int i = 0; i < n; i++) {
        tr = suma(tr, A[i][i]);
    }
    return tr;
}

// Suma y resta de matrices
void suma_matrices(Frac A[MAX][MAX], Frac B[MAX][MAX], Frac R[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            R[i][j] = suma(A[i][j], B[i][j]);
}

void resta_matrices(Frac A[MAX][MAX], Frac B[MAX][MAX], Frac R[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            R[i][j] = resta(A[i][j], B[i][j]);
}

// Producto de matrices
void producto_matrices(Frac A[MAX][MAX], Frac B[MAX][MAX], Frac R[MAX][MAX], int r1, int c1, int c2) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            R[i][j] = cero();
            for (int k = 0; k < c1; k++) {
                R[i][j] = suma(R[i][j], multiplicar(A[i][k], B[k][j]));
            }
        }
    }
}

// Determinante (recursivo por cofactores)
Frac determinante(Frac A[MAX][MAX], int n) {
    if (n == 1) return A[0][0];
    if (n == 2) {
        return resta(multiplicar(A[0][0], A[1][1]), multiplicar(A[0][1], A[1][0]));
    }
    Frac det = cero();
    Frac signo = identidad();
    Frac sub[MAX][MAX];
    for (int f = 0; f < n; f++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == f) continue;
                sub[subi][subj++] = A[i][j];
            }
            subi++;
        }
        Frac temp = multiplicar(signo, multiplicar(A[0][f], determinante(sub, n - 1)));
        det = suma(det, temp);
        signo = opuesto(signo);
    }
    return det;
}

int main() {
    Frac A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int r, c;

    printf("Introduce el numero de filas: ");
    scanf("%d", &r);
    printf("Introduce el numero de columnas: ");
    scanf("%d", &c);

    if (r > MAX || c > MAX || r < 1 || c < 1) {
        printf("Tamano invalido. Debe ser entre 1 y %d.\n", MAX);
        return 1;
    }

    leer_matriz(A, r, c, 'A');
    leer_matriz(B, r, c, 'B');

    printf("\nMatriz A:\n");
    imprimir_matriz(A, r, c);

    printf("\nMatriz B:\n");
    imprimir_matriz(B, r, c);

    // Transpuestas
    transpuesta(A, C, r, c);
    printf("\nTranspuesta A:\n");
    imprimir_matriz(C, c, r);

    transpuesta(B, C, r, c);
    printf("\nTranspuesta B:\n");
    imprimir_matriz(C, c, r);

    // Trazas (solo si es cuadrada)
    if (r == c) {
        printf("\nTraza A: %d/%d\n", traza(A, r).num, traza(A, r).den);
        printf("Traza B: %d/%d\n", traza(B, r).num, traza(B, r).den);

        // Determinantes
        Frac detA = determinante(A, r);
        Frac detB = determinante(B, r);
        printf("\nDeterminante A: %d/%d\n", detA.num, detA.den);
        printf("Determinante B: %d/%d\n", detB.num, detB.den);

        // Inversas posibles
        if (detA.num == 0) {
            printf("\nLa matriz A no tiene inversa porque su determinante es 0.\n");
        } else {
            printf("Matriz A es invertible.\n");
        }

        if (detB.num == 0) {
            printf("La matriz B no tiene inversa porque su determinante es 0.\n");
        } else {
            printf("Matriz B es invertible.\n");
        }
    } else {
        printf("\nLa matriz no es cuadrada, no se puede calcular traza, determinante ni inversa.\n");
    }

    // Suma
    suma_matrices(A, B, C, r, c);
    printf("\nA + B:\n");
    imprimir_matriz(C, r, c);

    // Resta
    resta_matrices(A, B, C, r, c);
    printf("\nA - B:\n");
    imprimir_matriz(C, r, c);

    // Producto (solo si columnas A == filas B)
    if (c == r) {
        producto_matrices(A, B, C, r, c, c);
        printf("\nA * B:\n");
        imprimir_matriz(C, r, c);
    } else {
        printf("\nNo se puede calcular el producto A*B porque el numero de columnas de A no coincide con el numero de filas de B.\n");
    }

    return 0;
}
