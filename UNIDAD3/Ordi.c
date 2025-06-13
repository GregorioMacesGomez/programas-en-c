/*/ Tabla Empleado
CREATE TABLE Empleado (
    matricula INT PRIMARY KEY AUTO_INCREMENT,
    nif VARCHAR(12) UNIQUE NOT NULL,
    num_hijos INT NOT NULL DEFAULT 0,
    porc_retencion DECIMAL(5,2) NOT NULL CHECK (porc_retencion BETWEEN 0 AND 100),
    banco VARCHAR(50) NOT NULL,
    sucursal VARCHAR(50) NOT NULL,
    cuenta VARCHAR(24) NOT NULL
) ENGINE=InnoDB;

    Tabla Departamento
CREATE TABLE Departamento (
    id INT PRIMARY KEY AUTO_INCREMENT,
    nombre VARCHAR(100) UNIQUE NOT NULL
) ENGINE=InnoDB;

    Tabla Sede
CREATE TABLE Sede (
    id INT PRIMARY KEY AUTO_INCREMENT,
    departamento_id INT NOT NULL,
    ubicacion VARCHAR(100) NOT NULL,
    FOREIGN KEY (departamento_id) REFERENCES Departamento(id) ON DELETE CASCADE
) ENGINE=InnoDB;

    Tabla Empleado_Departamento (relación N:M)
CREATE TABLE Empleado_Departamento (
    empleado_id INT NOT NULL,
    departamento_id INT NOT NULL,
    funcion VARCHAR(100) NOT NULL,
    PRIMARY KEY (empleado_id, departamento_id),
    FOREIGN KEY (empleado_id) REFERENCES Empleado(matricula) ON DELETE CASCADE,
    FOREIGN KEY (departamento_id) REFERENCES Departamento(id) ON DELETE CASCADE
) ENGINE=InnoDB;

    Tabla ConceptoRetributivo
CREATE TABLE ConceptoRetributivo (
    codigo INT PRIMARY KEY AUTO_INCREMENT,
    descripcion VARCHAR(200) NOT NULL
) ENGINE=InnoDB;

     Tabla Justificante
CREATE TABLE Justificante (
    id INT PRIMARY KEY AUTO_INCREMENT,
    empleado_id INT NOT NULL,
    ejercicio_fiscal YEAR NOT NULL,
    mes TINYINT NOT NULL CHECK (mes BETWEEN 1 AND 12),
    num_orden TINYINT NOT NULL DEFAULT 1,
    ingreso_total DECIMAL(10,2) NOT NULL,
    descuento_total DECIMAL(10,2) NOT NULL,
    UNIQUE (empleado_id, ejercicio_fiscal, mes, num_orden),
    FOREIGN KEY (empleado_id) REFERENCES Empleado(matricula) ON DELETE CASCADE
) ENGINE=InnoDB;

    Tabla LineaJustificante (con restricciones para descuentos)
CREATE TABLE LineaJustificante (
    id INT PRIMARY KEY AUTO_INCREMENT,
    justificante_id INT NOT NULL,
    num_linea INT NOT NULL,
    concepto_id INT NOT NULL,
    cantidad DECIMAL(10,2) NOT NULL,
    base_descuento DECIMAL(10,2) DEFAULT NULL,
    porc_descuento DECIMAL(5,2) DEFAULT NULL,
    tipo ENUM('ingreso', 'descuento') NOT NULL,
    UNIQUE (justificante_id, num_linea),
    FOREIGN KEY (justificante_id) REFERENCES Justificante(id) ON DELETE CASCADE,
    FOREIGN KEY (concepto_id) REFERENCES ConceptoRetributivo(codigo) ON DELETE RESTRICT,
    CONSTRAINT chk_tipo_valores CHECK (
        (tipo = 'ingreso' AND cantidad > 0 AND base_descuento IS NULL AND porc_descuento IS NULL) OR
        (tipo = 'descuento' AND cantidad < 0 AND base_descuento IS NOT NULL AND porc_descuento IS NOT NULL)
    )
) ENGINE=InnoDB;

    Tabla ElementoCoste (con jerarquía)
CREATE TABLE ElementoCoste (
    codigo INT PRIMARY KEY AUTO_INCREMENT,
    descripcion VARCHAR(200) NOT NULL,
    saldo DECIMAL(10,2) NOT NULL DEFAULT 0.00,
    padre_id INT DEFAULT NULL,
    FOREIGN KEY (padre_id) REFERENCES ElementoCoste(codigo) ON DELETE SET NULL
) ENGINE=InnoDB;

     Tabla Imputación (relación N:M entre líneas y elementos de coste)
CREATE TABLE Imputacion (
    linea_id INT NOT NULL,
    elemento_id INT NOT NULL,
    PRIMARY KEY (linea_id, elemento_id),
    FOREIGN KEY (linea_id) REFERENCES LineaJustificante(id) ON DELETE CASCADE,
    FOREIGN KEY (elemento_id) REFERENCES ElementoCoste(codigo) ON DELETE CASCADE
) ENGINE=InnoDB;

    Tabla Liquidación
CREATE TABLE Liquidacion (
    id INT PRIMARY KEY AUTO_INCREMENT,
    elemento_id INT NOT NULL,
    fecha DATE NOT NULL,
    FOREIGN KEY (elemento_id) REFERENCES ElementoCoste(codigo) ON DELETE CASCADE
) ENGINE=InnoDB;

    Tabla ApunteContable
CREATE TABLE ApunteContable (
    id INT PRIMARY KEY AUTO_INCREMENT,
    liquidacion_id INT NOT NULL,
    codigo VARCHAR(20) NOT NULL,
    cantidad DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (liquidacion_id) REFERENCES Liquidacion(id) ON DELETE CASCADE
) ENGINE=InnoDB;

    Tabla Transferencia
CREATE TABLE Transferencia (
    id INT PRIMARY KEY AUTO_INCREMENT,
    liquidacion_id INT NOT NULL,
    banco VARCHAR(50) NOT NULL,
    sucursal VARCHAR(50) NOT NULL,
    cuenta VARCHAR(24) NOT NULL,
    cantidad DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (liquidacion_id) REFERENCES Liquidacion(id) ON DELETE CASCADE
) ENGINE=InnoDB;
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <C:\Program Files\MySQL\MySQL Server 8.0\include\mysql.h>

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

/* ================== ESTRUCTURAS PARA DATOS ================== */

typedef struct {
    char nif[12];
    int num_hijos;
    float porc_retencion;
    char banco[50];
    char sucursal[50];
    char cuenta[24];
} Empleado;

typedef struct {
    char nombre[100];
} Departamento;

typedef struct {
    int departamento_id;
    char ubicacion[100];
} Sede;

typedef struct {
    int empleado_id;
    int departamento_id;
    char funcion[100];
} EmpDepto;

typedef struct {
    char descripcion[200];
} Concepto;

typedef struct {
    int empleado_id;
    int ejercicio_fiscal;
    int mes;
    int num_orden;
    float ingreso_total;
    float descuento_total;
} Justificante;

typedef struct {
    int justificante_id;
    int num_linea;
    int concepto_id;
    float cantidad;
    float base_descuento;
    float porc_descuento;
    char tipo[10]; // "ingreso" o "descuento"
} LineaJustificante;

typedef struct {
    char descripcion[200];
    float saldo;
    int padre_id;
} ElementoCoste;

typedef struct {
    int linea_id;
    int elemento_id;
} Imputacion;

typedef struct {
    int elemento_id;
    char fecha[11]; // YYYY-MM-DD
} Liquidacion;

typedef struct {
    int liquidacion_id;
    char codigo[20];
    float cantidad;
} Apunte;

typedef struct {
    int liquidacion_id;
    char banco[50];
    char sucursal[50];
    char cuenta[24];
    float cantidad;
} Transferencia;

/* ================== DECLARACION DE FUNCIONES ================== */
void finish_with_error();
void conectar();
void insertar_ejemplos_automaticos();
int tabla_vacia(const char *tabla);
void mostrar_tabla(const char *tabla);
void eliminar_por_id(const char *tabla, const char *campo_id);
void menu_tabla(const char *tabla, const char *campo_id, void (*func_insercion)());
void menu_principal();

/* ================== FUNCIONES BASICAS ================== */
void finish_with_error() {
    fprintf(stderr, "Error MySQL: %s\n", mysql_error(conn));
    if (conn) mysql_close(conn);
    exit(1);
}

int tabla_vacia(const char *tabla) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM %s", tabla);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al verificar tabla %s: %s\n", tabla, mysql_error(conn));
        return 0;
    }

    res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "Error al obtener conteo de %s: %s\n", tabla, mysql_error(conn));
        return 0;
    }

    row = mysql_fetch_row(res);
    int count = row ? atoi(row[0]) : 0;
    mysql_free_result(res);

    return count == 0;
}

void conectar() {
    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "Error al iniciar MySQL\n");
        exit(1);
    }

    if (!mysql_real_connect(conn, "localhost", "root", "12345", "contabilidad", 3306, NULL, 0)) {
        finish_with_error();
    }

    printf("\n===========================================\n");
    printf("||   SISTEMA DE GESTION CONTABLE         ||\n");
    printf("||   Conexion a MySQL establecida        ||\n");
    printf("===========================================\n");

    insertar_ejemplos_automaticos();
}

void mostrar_tabla(const char *tabla) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM %s", tabla);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al mostrar %s: %s\n", tabla, mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "Error al obtener resultados de %s: %s\n", tabla, mysql_error(conn));
        return;
    }

    int num_fields = mysql_num_fields(res);
    MYSQL_FIELD *fields = mysql_fetch_fields(res);

    printf("\n=== Registros de %s ===\n", tabla);
    for (int i = 0; i < num_fields; i++) {
        printf("%-20s", fields[i].name);
    }
    printf("\n");

    int registros = 0;
    while ((row = mysql_fetch_row(res))) {
        registros++;
        for (int i = 0; i < num_fields; i++) {
            printf("%-20s", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    if (registros == 0) {
        printf("No hay registros en esta tabla\n");
    } else {
        printf("\nTotal registros: %d\n", registros);
    }

    mysql_free_result(res);
}

void eliminar_por_id(const char *tabla, const char *campo_id) {
    mostrar_tabla(tabla);

    int id;
    printf("\nIngrese el ID a eliminar (0 para cancelar): ");
    scanf("%d", &id);

    if (id == 0) {
        printf("Operación cancelada\n");
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM %s WHERE %s = %d", tabla, campo_id, id);

    if (mysql_query(conn, query)) {
        printf("Error al eliminar: %s\n", mysql_error(conn));
    } else {
        printf("Registro eliminado correctamente\n");
    }

    mostrar_tabla(tabla);
}

/* ================== FUNCION insertar_empleado ================== */
void insertar_empleado() {
    Empleado emp;
    printf("\n=== Nuevo Empleado ===\n");
    printf("NIF (12 caracteres): ");
    scanf("%s", emp.nif);
    printf("Número de hijos: ");
    scanf("%d", &emp.num_hijos);
    printf("Porcentaje de retención: ");
    scanf("%f", &emp.porc_retencion);
    printf("Banco: ");
    scanf("%s", emp.banco);
    printf("Sucursal: ");
    scanf("%s", emp.sucursal);
    printf("Cuenta: ");
    scanf("%s", emp.cuenta);

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO Empleado(nif, num_hijos, porc_retencion, banco, sucursal, cuenta) "
        "VALUES('%s', %d, %.2f, '%s', '%s', '%s')",
        emp.nif, emp.num_hijos, emp.porc_retencion, emp.banco, emp.sucursal, emp.cuenta);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar empleado: %s\n", mysql_error(conn));
    } else {
        printf("Empleado insertado correctamente\n");
    }
}

/* ================== FUNCION insertar_empleados_ejemplo ================== */
void insertar_empleados_ejemplo() {
    char *empleados[] = {
        "INSERT INTO Empleado(nif, num_hijos, porc_retencion, banco, sucursal, cuenta) "
        "VALUES('12345678A', 2, 15.0, 'BBVA', 'Centro', 'ES7621000000001234567890')",
        "INSERT INTO Empleado(nif, num_hijos, porc_retencion, banco, sucursal, cuenta) "
        "VALUES('87654321B', 1, 12.5, 'Santander', 'Norte', 'ES9000490000551234567890')",
        "INSERT INTO Empleado(nif, num_hijos, porc_retencion, banco, sucursal, cuenta) "
        "VALUES('11223344C', 0, 19.0, 'CaixaBank', 'Este', 'ES2100300000031234567890')",
        "INSERT INTO Empleado(nif, num_hijos, porc_retencion, banco, sucursal, cuenta) "
        "VALUES('55667788D', 3, 10.0, 'Sabadell', 'Sur', 'ES0081000000123456789012')",
        "INSERT INTO Empleado(nif, num_hijos, porc_retencion, banco, sucursal, cuenta) "
        "VALUES('99887766E', 1, 14.2, 'Bankia', 'Oeste', 'ES2038000000123456789012')"
    };

    for (int i = 0; i < 5; i++) {
        if (mysql_query(conn, empleados[i])) {
            fprintf(stderr, "Error al insertar empleado %d: %s\n", i+1, mysql_error(conn));
        }
    }
}

/* ================== MENU PARA TABLAS INDIVIDUALES ================== */
void menu_tabla(const char *tabla, const char *campo_id, void (*func_insercion)()) {
    int opcion;
    do {
        printf("\n=== MENU %s ===\n", tabla);
        printf("1. Mostrar registros\n");
        printf("2. Agregar nuevo registro\n");
        printf("3. Eliminar registro por ID\n");
        printf("0. Volver al menú principal\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                mostrar_tabla(tabla);
                break;
            case 2:
                func_insercion();
                break;
            case 3:
                eliminar_por_id(tabla, campo_id);
                break;
        }
    } while (opcion != 0);
}


/* ================== FUNCION insertar_departamento ================== */
void insertar_departamento() {
    Departamento depto;
    printf("\n=== Nuevo Departamento ===\n");
    printf("Nombre del departamento: ");
    scanf(" %[^\n]", depto.nombre);

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO Departamento(nombre) VALUES('%s')",
        depto.nombre);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar departamento: %s\n", mysql_error(conn));
    } else {
        printf("Departamento insertado correctamente\n");
    }
}

/* ================== FUNCION insertar_departamentos_ejemplo ================== */
void insertar_departamentos_ejemplo() {
    char *departamentos[] = {
        "INSERT INTO Departamento(nombre) VALUES('Dirección')",
        "INSERT INTO Departamento(nombre) VALUES('Recursos Humanos')",
        "INSERT INTO Departamento(nombre) VALUES('Contabilidad')",
        "INSERT INTO Departamento(nombre) VALUES('Ventas')",
        "INSERT INTO Departamento(nombre) VALUES('Desarrollo')"
    };

    for (int i = 0; i < 5; i++) {
        if (mysql_query(conn, departamentos[i])) {
            fprintf(stderr, "Error al insertar departamento %d: %s\n", i+1, mysql_error(conn));
        }
    }
}

/* ================== FUNCION insertar_sede ================== */
void insertar_sede() {
    Sede sede;
    printf("\n=== Nueva Sede ===\n");
    printf("ID del Departamento (departamento_id): ");
    scanf("%d", &sede.departamento_id);
    printf("Ubicación: ");
    scanf(" %[^\n]", sede.ubicacion);

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO Sede(departamento_id, ubicacion) VALUES(%d, '%s')",
        sede.departamento_id, sede.ubicacion);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar sede: %s\n", mysql_error(conn));
    } else {
        printf("Sede insertada correctamente\n");
    }
}

/* ================== FUNCION insertar_sedes_ejemplo ================== */
void insertar_sedes_ejemplo() {
    char *sedes[] = {
        "INSERT INTO Sede(departamento_id, ubicacion) VALUES(1, 'Edificio A')",
        "INSERT INTO Sede(departamento_id, ubicacion) VALUES(2, 'Edificio B')",
        "INSERT INTO Sede(departamento_id, ubicacion) VALUES(3, 'Edificio C')",
        "INSERT INTO Sede(departamento_id, ubicacion) VALUES(4, 'Edificio D')",
        "INSERT INTO Sede(departamento_id, ubicacion) VALUES(5, 'Edificio E')"
    };

    for (int i = 0; i < 5; i++) {
        if (mysql_query(conn, sedes[i])) {
            fprintf(stderr, "Error al insertar sede %d: %s\n", i+1, mysql_error(conn));
        }
    }
}

/* ================== FUNCION insertar_emp_depto ================== */
void insertar_emp_depto() {
    EmpDepto emp_depto;
    printf("\n=== Nueva Asignación Empleado - Departamento ===\n");
    printf("ID del Empleado (empleado_id): ");
    scanf("%d", &emp_depto.empleado_id);
    printf("ID del Departamento (departamento_id): ");
    scanf("%d", &emp_depto.departamento_id);
    printf("Función: ");
    scanf(" %[^\n]", emp_depto.funcion);

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO Empleado_Departamento(empleado_id, departamento_id, funcion) "
        "VALUES(%d, %d, '%s')",
        emp_depto.empleado_id, emp_depto.departamento_id, emp_depto.funcion);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar asignación: %s\n", mysql_error(conn));
    } else {
        printf("Asignación insertada correctamente\n");
    }
}

/* ================== FUNCION insertar_emp_deptos_ejemplo ================== */
void insertar_emp_deptos_ejemplo() {
    char *empdeptos[] = {
        "INSERT INTO Empleado_Departamento(empleado_id, departamento_id, funcion) VALUES(1, 1, 'Director')",
        "INSERT INTO Empleado_Departamento(empleado_id, departamento_id, funcion) VALUES(2, 2, 'Recursos Humanos')",
        "INSERT INTO Empleado_Departamento(empleado_id, departamento_id, funcion) VALUES(3, 3, 'Contador')",
        "INSERT INTO Empleado_Departamento(empleado_id, departamento_id, funcion) VALUES(4, 4, 'Vendedor')",
        "INSERT INTO Empleado_Departamento(empleado_id, departamento_id, funcion) VALUES(5, 5, 'Desarrollador')"
    };

    for (int i = 0; i < 5; i++) {
        if (mysql_query(conn, empdeptos[i])) {
            fprintf(stderr, "Error al insertar asignación %d: %s\n", i+1, mysql_error(conn));
        }
    }
}

/* ================== FUNCION insertar_concepto ================== */
void insertar_concepto() {
    Concepto concepto;
    printf("\n=== Nuevo Concepto Retributivo ===\n");
    printf("Descripción: ");
    scanf(" %[^\n]", concepto.descripcion);

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO ConceptoRetributivo(descripcion) VALUES('%s')",
        concepto.descripcion);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar concepto: %s\n", mysql_error(conn));
    } else {
        printf("Concepto insertado correctamente\n");
    }
}

/* ================== FUNCION insertar_conceptos_ejemplo ================== */
void insertar_conceptos_ejemplo() {
    char *conceptos[] = {
        "INSERT INTO ConceptoRetributivo(descripcion) VALUES('Salario Base')",
        "INSERT INTO ConceptoRetributivo(descripcion) VALUES('Plus Transporte')",
        "INSERT INTO ConceptoRetributivo(descripcion) VALUES('IRPF')",
        "INSERT INTO ConceptoRetributivo(descripcion) VALUES('Seguridad Social')",
        "INSERT INTO ConceptoRetributivo(descripcion) VALUES('Bonus Productividad')"
    };

    for (int i = 0; i < 5; i++) {
        if (mysql_query(conn, conceptos[i])) {
            fprintf(stderr, "Error al insertar concepto %d: %s\n", i+1, mysql_error(conn));
        }
    }
}

/* ================== FUNCION insertar_justificante ================== */
void insertar_justificante() {
    Justificante just;
    printf("\n=== Nuevo Justificante ===\n");
    printf("ID del Empleado (empleado_id): ");
    scanf("%d", &just.empleado_id);
    printf("Ejercicio fiscal (YYYY): ");
    scanf("%d", &just.ejercicio_fiscal);
    printf("Mes (1-12): ");
    scanf("%d", &just.mes);
    printf("Número de orden: ");
    scanf("%d", &just.num_orden);
    printf("Ingreso total: ");
    scanf("%f", &just.ingreso_total);
    printf("Descuento total: ");
    scanf("%f", &just.descuento_total);

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO Justificante(empleado_id, ejercicio_fiscal, mes, num_orden, ingreso_total, descuento_total) "
        "VALUES(%d, %d, %d, %d, %.2f, %.2f)",
        just.empleado_id, just.ejercicio_fiscal, just.mes, just.num_orden, just.ingreso_total, just.descuento_total);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar justificante: %s\n", mysql_error(conn));
    } else {
        printf("Justificante insertado correctamente\n");
    }
}

/* ================== FUNCION insertar_justificantes_ejemplo ================== */
void insertar_justificantes_ejemplo() {
    char *justificantes[] = {
        "INSERT INTO Justificante(empleado_id, ejercicio_fiscal, mes, num_orden, ingreso_total, descuento_total) "
        "VALUES(1, 2024, 1, 1, 1500.00, 300.00)",
        "INSERT INTO Justificante(empleado_id, ejercicio_fiscal, mes, num_orden, ingreso_total, descuento_total) "
        "VALUES(2, 2024, 2, 1, 1400.00, 280.00)",
        "INSERT INTO Justificante(empleado_id, ejercicio_fiscal, mes, num_orden, ingreso_total, descuento_total) "
        "VALUES(3, 2024, 3, 1, 1600.00, 320.00)",
        "INSERT INTO Justificante(empleado_id, ejercicio_fiscal, mes, num_orden, ingreso_total, descuento_total) "
        "VALUES(4, 2024, 4, 1, 1550.00, 310.00)",
        "INSERT INTO Justificante(empleado_id, ejercicio_fiscal, mes, num_orden, ingreso_total, descuento_total) "
        "VALUES(5, 2024, 5, 1, 1450.00, 290.00)"
    };

    for (int i = 0; i < 5; i++) {
        if (mysql_query(conn, justificantes[i])) {
            fprintf(stderr, "Error al insertar justificante %d: %s\n", i+1, mysql_error(conn));
        }
    }
}

/* ================== FUNCION insertar_linea_justificante ================== */
void insertar_linea_justificante() {
    LineaJustificante linea;
    printf("\n=== Nueva Línea de Justificante ===\n");
    printf("ID del Justificante (justificante_id): ");
    scanf("%d", &linea.justificante_id);
    printf("Número de línea: ");
    scanf("%d", &linea.num_linea);
    printf("ID del Concepto (concepto_id): ");
    scanf("%d", &linea.concepto_id);
    printf("Cantidad: ");
    scanf("%f", &linea.cantidad);
    printf("Base de descuento (puede ser 0): ");
    scanf("%f", &linea.base_descuento);
    printf("Porcentaje de descuento (puede ser 0): ");
    scanf("%f", &linea.porc_descuento);
    printf("Tipo ('ingreso' o 'descuento'): ");
    scanf(" %[^\n]", linea.tipo);

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO LineaJustificante(justificante_id, num_linea, concepto_id, cantidad, base_descuento, porc_descuento, tipo) "
        "VALUES(%d, %d, %d, %.2f, %.2f, %.2f, '%s')",
        linea.justificante_id, linea.num_linea, linea.concepto_id, linea.cantidad, linea.base_descuento, linea.porc_descuento, linea.tipo);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar línea de justificante: %s\n", mysql_error(conn));
    } else {
        printf("Línea de justificante insertada correctamente\n");
    }
}

/* ================== FUNCION insertar_lineas_justificante_ejemplo ================== */
void insertar_lineas_justificante_ejemplo() {
    char *lineas[] = {
        "INSERT INTO LineaJustificante(justificante_id, num_linea, concepto_id, cantidad, base_descuento, porc_descuento, tipo) "
        "VALUES(1, 1, 1, 1500.00, NULL, NULL, 'ingreso')",
        "INSERT INTO LineaJustificante(justificante_id, num_linea, concepto_id, cantidad, base_descuento, porc_descuento, tipo) "
        "VALUES(2, 1, 2, 100.00, NULL, NULL, 'ingreso')",
        "INSERT INTO LineaJustificante(justificante_id, num_linea, concepto_id, cantidad, base_descuento, porc_descuento, tipo) "
        "VALUES(3, 1, 3, -300.00, 1500.00, 20.00, 'descuento')",
        "INSERT INTO LineaJustificante(justificante_id, num_linea, concepto_id, cantidad, base_descuento, porc_descuento, tipo) "
        "VALUES(4, 1, 4, -310.00, 1550.00, 20.00, 'descuento')",
        "INSERT INTO LineaJustificante(justificante_id, num_linea, concepto_id, cantidad, base_descuento, porc_descuento, tipo) "
        "VALUES(5, 1, 5, 200.00, NULL, NULL, 'ingreso')"
    };

    for (int i = 0; i < 5; i++) {
        if (mysql_query(conn, lineas[i])) {
            fprintf(stderr, "Error al insertar línea %d: %s\n", i+1, mysql_error(conn));
        }
    }
}

/* ================== FUNCION insertar_elemento_coste ================== */
void insertar_elemento_coste() {
    ElementoCoste elem;
    printf("\n=== Nuevo Elemento de Coste ===\n");
    printf("Descripción: ");
    scanf(" %[^\n]", elem.descripcion);
    printf("Saldo: ");
    scanf("%f", &elem.saldo);
    printf("ID del Padre (puede ser NULL, escribe 0 para NULL): ");
    scanf("%d", &elem.padre_id);

    char query[512];
    if (elem.padre_id == 0) {
        snprintf(query, sizeof(query),
            "INSERT INTO ElementoCoste(descripcion, saldo, padre_id) "
            "VALUES('%s', %.2f, NULL)",
            elem.descripcion, elem.saldo);
    } else {
        snprintf(query, sizeof(query),
            "INSERT INTO ElementoCoste(descripcion, saldo, padre_id) "
            "VALUES('%s', %.2f, %d)",
            elem.descripcion, elem.saldo, elem.padre_id);
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar elemento de coste: %s\n", mysql_error(conn));
    } else {
        printf("Elemento de coste insertado correctamente\n");
    }
}

/* ================== FUNCION insertar_elementos_coste_ejemplo ================== */
void insertar_elementos_coste_ejemplo() {
    char *elementos[] = {
        "INSERT INTO ElementoCoste(descripcion, saldo, padre_id) VALUES('Gastos de viaje', 500.00, NULL)",
        "INSERT INTO ElementoCoste(descripcion, saldo, padre_id) VALUES('Material de oficina', 300.00, NULL)",
        "INSERT INTO ElementoCoste(descripcion, saldo, padre_id) VALUES('Formación', 400.00, NULL)",
        "INSERT INTO ElementoCoste(descripcion, saldo, padre_id) VALUES('Marketing', 600.00, NULL)",
        "INSERT INTO ElementoCoste(descripcion, saldo, padre_id) VALUES('Hardware', 800.00, NULL)"
    };

    for (int i = 0; i < 5; i++) {
        if (mysql_query(conn, elementos[i])) {
            fprintf(stderr, "Error al insertar elemento %d: %s\n", i+1, mysql_error(conn));
        }
    }
}

/* ================== FUNCION insertar_imputacion ================== */
void insertar_imputacion() {
    Imputacion imp;
    printf("\n=== Nueva Imputación ===\n");
    printf("ID de Línea de Justificante (linea_id): ");
    scanf("%d", &imp.linea_id);
    printf("ID del Elemento de Coste (elemento_id): ");
    scanf("%d", &imp.elemento_id);

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO Imputacion(linea_id, elemento_id) VALUES(%d, %d)",
        imp.linea_id, imp.elemento_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar imputación: %s\n", mysql_error(conn));
    } else {
        printf("Imputación insertada correctamente\n");
    }
}

/* ================== FUNCION insertar_imputaciones_ejemplo ================== */
void insertar_imputaciones_ejemplo() {
    char *imputaciones[] = {
        "INSERT INTO Imputacion(linea_id, elemento_id) VALUES(1, 1)",
        "INSERT INTO Imputacion(linea_id, elemento_id) VALUES(2, 2)",
        "INSERT INTO Imputacion(linea_id, elemento_id) VALUES(3, 3)",
        "INSERT INTO Imputacion(linea_id, elemento_id) VALUES(4, 4)",
        "INSERT INTO Imputacion(linea_id, elemento_id) VALUES(5, 5)"
    };

    for (int i = 0; i < 5; i++) {
        if (mysql_query(conn, imputaciones[i])) {
            fprintf(stderr, "Error al insertar imputación %d: %s\n", i+1, mysql_error(conn));
        }
    }
}   
/* ================== FUNCION insertar_liquidacion ================== */
void insertar_liquidacion() {
    Liquidacion liq;
    printf("\n=== Nueva Liquidación ===\n");
    printf("ID del Elemento de Coste (elemento_id): ");
    scanf("%d", &liq.elemento_id);
    printf("Fecha (YYYY-MM-DD): ");
    scanf("%s", liq.fecha);

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO Liquidacion(elemento_id, fecha) VALUES(%d, '%s')",
        liq.elemento_id, liq.fecha);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar liquidación: %s\n", mysql_error(conn));
    } else {
        printf("Liquidación insertada correctamente\n");
    }
}

/* ================== FUNCION insertar_liquidaciones_ejemplo ================== */
void insertar_liquidaciones_ejemplo() {
    char *liquidaciones[] = {
        "INSERT INTO Liquidacion(elemento_id, fecha) VALUES(1, '2024-01-31')",
        "INSERT INTO Liquidacion(elemento_id, fecha) VALUES(2, '2024-02-28')",
        "INSERT INTO Liquidacion(elemento_id, fecha) VALUES(3, '2024-03-31')",
        "INSERT INTO Liquidacion(elemento_id, fecha) VALUES(4, '2024-04-30')",
        "INSERT INTO Liquidacion(elemento_id, fecha) VALUES(5, '2024-05-31')"
    };

    for (int i = 0; i < 5; i++) {
        if (mysql_query(conn, liquidaciones[i])) {
            fprintf(stderr, "Error al insertar liquidación %d: %s\n", i+1, mysql_error(conn));
        }
    }
}

/* ================== FUNCION insertar_apunte ================== */
void insertar_apunte() {
    Apunte apunte;
    printf("\n=== Nuevo Apunte Contable ===\n");
    printf("ID de la Liquidación (liquidacion_id): ");
    scanf("%d", &apunte.liquidacion_id);
    printf("Código: ");
    scanf("%s", apunte.codigo);
    printf("Cantidad: ");
    scanf("%f", &apunte.cantidad);

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO ApunteContable(liquidacion_id, codigo, cantidad) VALUES(%d, '%s', %.2f)",
        apunte.liquidacion_id, apunte.codigo, apunte.cantidad);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar apunte: %s\n", mysql_error(conn));
    } else {
        printf("Apunte contable insertado correctamente\n");
    }
}

/* ================== FUNCION insertar_apuntes_ejemplo ================== */
void insertar_apuntes_ejemplo() {
    char *apuntes[] = {
        "INSERT INTO ApunteContable(liquidacion_id, codigo, cantidad) VALUES(1, 'NOM_202401', 5000.00)",
        "INSERT INTO ApunteContable(liquidacion_id, codigo, cantidad) VALUES(2, 'NOM_202402', 4800.00)",
        "INSERT INTO ApunteContable(liquidacion_id, codigo, cantidad) VALUES(3, 'NOM_202403', 5100.00)",
        "INSERT INTO ApunteContable(liquidacion_id, codigo, cantidad) VALUES(4, 'NOM_202404', 4950.00)",
        "INSERT INTO ApunteContable(liquidacion_id, codigo, cantidad) VALUES(5, 'NOM_202405', 5050.00)"
    };

    for (int i = 0; i < 5; i++) {
        if (mysql_query(conn, apuntes[i])) {
            fprintf(stderr, "Error al insertar apunte %d: %s\n", i+1, mysql_error(conn));
        }
    }
}

/* ================== FUNCION insertar_transferencia ================== */
void insertar_transferencia() {
    Transferencia trans;
    printf("\n=== Nueva Transferencia ===\n");
    printf("ID de la Liquidación (liquidacion_id): ");
    scanf("%d", &trans.liquidacion_id);
    printf("Banco: ");
    scanf("%s", trans.banco);
    printf("Sucursal: ");
    scanf("%s", trans.sucursal);
    printf("Cuenta: ");
    scanf("%s", trans.cuenta);
    printf("Cantidad: ");
    scanf("%f", &trans.cantidad);

    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO Transferencia(liquidacion_id, banco, sucursal, cuenta, cantidad) "
        "VALUES(%d, '%s', '%s', '%s', %.2f)",
        trans.liquidacion_id, trans.banco, trans.sucursal, trans.cuenta, trans.cantidad);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar transferencia: %s\n", mysql_error(conn));
    } else {
        printf("Transferencia insertada correctamente\n");
    }
}

/* ================== FUNCION insertar_transferencias_ejemplo ================== */
void insertar_transferencias_ejemplo() {
    char *transferencias[] = {
        "INSERT INTO Transferencia(liquidacion_id, banco, sucursal, cuenta, cantidad) "
        "VALUES(1, 'BBVA', 'Centro', 'ES11112222333344445555', 5000.00)",
        "INSERT INTO Transferencia(liquidacion_id, banco, sucursal, cuenta, cantidad) "
        "VALUES(2, 'Santander', 'Norte', 'ES55554444333322221111', 4800.00)",
        "INSERT INTO Transferencia(liquidacion_id, banco, sucursal, cuenta, cantidad) "
        "VALUES(3, 'CaixaBank', 'Este', 'ES66667777888899990000', 5100.00)",
        "INSERT INTO Transferencia(liquidacion_id, banco, sucursal, cuenta, cantidad) "
        "VALUES(4, 'Sabadell', 'Sur', 'ES12345678901234567890', 4950.00)",
        "INSERT INTO Transferencia(liquidacion_id, banco, sucursal, cuenta, cantidad) "
        "VALUES(5, 'Bankia', 'Oeste', 'ES09876543210987654321', 5050.00)"
    };

    for (int i = 0; i < 5; i++) {
        if (mysql_query(conn, transferencias[i])) {
            fprintf(stderr, "Error al insertar transferencia %d: %s\n", i+1, mysql_error(conn));
        }
    }
}


void insertar_ejemplos_automaticos() {
    if (tabla_vacia("Empleado")) insertar_empleados_ejemplo();
    if (tabla_vacia("Departamento")) insertar_departamentos_ejemplo();
    if (tabla_vacia("Sede")) insertar_sedes_ejemplo();
    if (tabla_vacia("Empleado_Departamento")) insertar_emp_deptos_ejemplo();
    if (tabla_vacia("ConceptoRetributivo")) insertar_conceptos_ejemplo();
    if (tabla_vacia("Justificante")) insertar_justificantes_ejemplo();
    if (tabla_vacia("LineaJustificante")) insertar_lineas_justificante_ejemplo();
    if (tabla_vacia("ElementoCoste")) insertar_elementos_coste_ejemplo();
    if (tabla_vacia("Imputacion")) insertar_imputaciones_ejemplo();
    if (tabla_vacia("Liquidacion")) insertar_liquidaciones_ejemplo();
    if (tabla_vacia("ApunteContable")) insertar_apuntes_ejemplo();
    if (tabla_vacia("Transferencia")) insertar_transferencias_ejemplo();
}


void menu_principal() {
    int opcion;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Empleados\n");
        printf("2. Departamentos\n");
        printf("3. Sedes\n");
        printf("4. Asignaciones Empleado - Departamento\n");
        printf("5. Conceptos Retributivos\n");
        printf("6. Justificantes\n");
        printf("7. Líneas de Justificante\n");
        printf("8. Elementos de Coste\n");
        printf("9. Imputaciones\n");
        printf("10. Liquidaciones\n");
        printf("11. Apuntes Contables\n");
        printf("12. Transferencias\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: menu_tabla("Empleado", "matricula", insertar_empleado); break;
            case 2: menu_tabla("Departamento", "id", insertar_departamento); break;
            case 3: menu_tabla("Sede", "id", insertar_sede); break;
            case 4: menu_tabla("Empleado_Departamento", "empleado_id", insertar_emp_depto); break;
            case 5: menu_tabla("ConceptoRetributivo", "codigo", insertar_concepto); break;
            case 6: menu_tabla("Justificante", "id", insertar_justificante); break;
            case 7: menu_tabla("LineaJustificante", "id", insertar_linea_justificante); break;
            case 8: menu_tabla("ElementoCoste", "codigo", insertar_elemento_coste); break;
            case 9: menu_tabla("Imputacion", "linea_id", insertar_imputacion); break;
            case 10: menu_tabla("Liquidacion", "id", insertar_liquidacion); break;
            case 11: menu_tabla("ApunteContable", "id", insertar_apunte); break;
            case 12: menu_tabla("Transferencia", "id", insertar_transferencia); break;
        }
    } while (opcion != 0);
}

/* ================== MAIN ================== */
int main() {
    conectar();
    menu_principal();

    if (conn) mysql_close(conn);
    return 0;
}