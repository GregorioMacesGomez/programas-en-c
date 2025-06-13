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
#include </Applications/MAMP/Library/bin/mysql57/include/mysql.h>

// Estructuras de datos para las tablas principales
typedef struct {
    int matricula;
    char nif[12];
    int num_hijos;
    float porc_retencion;
    char banco[50];
    char sucursal[50];
    char cuenta[24];
} Empleado;

typedef struct {
    int id;
    char nombre[100];
} Departamento;

typedef struct {
    int id;
    int empleado_id;
    int ejercicio_fiscal;
    int mes;
    int num_orden;
    float ingreso_total;
    float descuento_total;
} Justificante;

MYSQL *con;

void finish_with_error() {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void conectar() {
    con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() falló\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "root", "basedatos",
        8889, "/Applications/MAMP/tmp/mysql/mysql.sock", 0) == NULL) {
        finish_with_error();
    }
}

int crear_empleado(const Empleado *empleado) {
    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO Empleado(nif, num_hijos, porc_retencion, banco, sucursal, cuenta) "
        "VALUES('%s', %d, %.2f, '%s', '%s', '%s')",
        empleado->nif, empleado->num_hijos, empleado->porc_retencion,
        empleado->banco, empleado->sucursal, empleado->cuenta);

    if (mysql_query(con, query)) {
        finish_with_error();
    }

    return mysql_insert_id(con);
}

int crear_departamento(const char *nombre) {
    char query[256];
    snprintf(query, sizeof(query),
        "INSERT INTO Departamento(nombre) VALUES('%s')", nombre);

    if (mysql_query(con, query)) {
        finish_with_error();
    }

    return mysql_insert_id(con);
}

void asignar_empleado_departamento(int empleado_id, int departamento_id, const char *funcion) {
    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO Empleado_Departamento(empleado_id, departamento_id, funcion) "
        "VALUES(%d, %d, '%s')",
        empleado_id, departamento_id, funcion);

    if (mysql_query(con, query)) {
        finish_with_error();
    }
}

int crear_justificante(const Justificante *justificante) {
    char query[512];
    snprintf(query, sizeof(query),
        "INSERT INTO Justificante(empleado_id, ejercicio_fiscal, mes, num_orden, ingreso_total, descuento_total) "
        "VALUES(%d, %d, %d, %d, %.2f, %.2f)",
        justificante->empleado_id, justificante->ejercicio_fiscal,
        justificante->mes, justificante->num_orden,
        justificante->ingreso_total, justificante->descuento_total);

    if (mysql_query(con, query)) {
        finish_with_error();
    }

    return mysql_insert_id(con);
}

void leer_empleados_con_departamentos() {
    const char *query =
        "SELECT e.matricula, e.nif, d.nombre, ed.funcion "
        "FROM Empleado e "
        "JOIN Empleado_Departamento ed ON e.matricula = ed.empleado_id "
        "JOIN Departamento d ON d.id = ed.departamento_id "
        "ORDER BY e.matricula";

    if (mysql_query(con, query)) {
        finish_with_error();
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error();
    }

    MYSQL_ROW row;
    int last_matricula = -1;

    printf("\n== Empleados con sus departamentos ==\n");

    while ((row = mysql_fetch_row(result))) {
        int matricula = atoi(row[0]);
        const char *nif = row[1];
        const char *dep_nombre = row[2];
        const char *funcion = row[3];

        if (matricula != last_matricula) {
            printf("\nEmpleado Matrícula: %d, NIF: %s\n", matricula, nif);
            printf("Departamentos:\n");
            last_matricula = matricula;
        }

        printf(" - %s (Función: %s)\n", dep_nombre, funcion);
    }

    mysql_free_result(result);
}

void leer_departamentos_con_empleados() {
    const char *query =
        "SELECT d.id, d.nombre, e.matricula, e.nif "
        "FROM Departamento d "
        "JOIN Empleado_Departamento ed ON d.id = ed.departamento_id "
        "JOIN Empleado e ON e.matricula = ed.empleado_id "
        "ORDER BY d.id";

    if (mysql_query(con, query)) {
        finish_with_error();
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error();
    }

    MYSQL_ROW row;
    int last_dep_id = -1;

    printf("\n== Departamentos con sus empleados ==\n");

    while ((row = mysql_fetch_row(result))) {
        int dep_id = atoi(row[0]);
        const char *dep_nombre = row[1];
        int matricula = atoi(row[2]);
        const char *nif = row[3];

        if (dep_id != last_dep_id) {
            printf("\nDepartamento ID: %d, Nombre: %s\n", dep_id, dep_nombre);
            printf("Empleados:\n");
            last_dep_id = dep_id;
        }

        printf(" - Matrícula: %d, NIF: %s\n", matricula, nif);
    }

    mysql_free_result(result);
}

void leer_empleados_con_justificantes() {
    const char *query =
        "SELECT e.matricula, e.nif, j.id, j.ejercicio_fiscal, j.mes, j.num_orden "
        "FROM Empleado e "
        "JOIN Justificante j ON e.matricula = j.empleado_id "
        "ORDER BY e.matricula, j.id";

    if (mysql_query(con, query)) {
        finish_with_error();
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error();
    }

    MYSQL_ROW row;
    int last_matricula = -1;

    printf("\n== Empleados con sus justificantes de nómina ==\n");

    while ((row = mysql_fetch_row(result))) {
        int matricula = atoi(row[0]);
        const char *nif = row[1];
        int justificante_id = atoi(row[2]);
        int ejercicio = atoi(row[3]);
        int mes = atoi(row[4]);
        int orden = atoi(row[5]);

        if (matricula != last_matricula) {
            printf("\nEmpleado Matrícula: %d, NIF: %s\n", matricula, nif);
            printf("Justificantes:\n");
            last_matricula = matricula;
        }

        printf(" - ID: %d, Periodo: %d-%02d, Orden: %d\n", 
               justificante_id, ejercicio, mes, orden);
    }

    mysql_free_result(result);
}

int main() {
    conectar();

    // Crear un empleado
    Empleado emp = {
        .nif = "12345678A",
        .num_hijos = 2,
        .porc_retencion = 15.0,
        .banco = "BBVA",
        .sucursal = "Madrid Centro",
        .cuenta = "ES12345678901234567890"
    };
    int matricula = crear_empleado(&emp);

    // Crear dos departamentos
    int dep1 = crear_departamento("Ventas");
    int dep2 = crear_departamento("TI");

    // Asignar empleado a departamentos
    asignar_empleado_departamento(matricula, dep1, "Comercial");
    asignar_empleado_departamento(matricula, dep2, "Desarrollador");

    // Crear justificantes de nómina
    Justificante just1 = {
        .empleado_id = matricula,
        .ejercicio_fiscal = 2025,
        .mes = 5,
        .num_orden = 1,
        .ingreso_total = 2500.00,
        .descuento_total = 375.00
    };
    crear_justificante(&just1);

    Justificante just2 = {
        .empleado_id = matricula,
        .ejercicio_fiscal = 2025,
        .mes = 6,
        .num_orden = 1,
        .ingreso_total = 2600.00,
        .descuento_total = 390.00
    };
    crear_justificante(&just2);

    // Mostrar relaciones
    leer_empleados_con_departamentos();
    leer_departamentos_con_empleados();
    leer_empleados_con_justificantes();

    mysql_close(con);
    return 0;
}