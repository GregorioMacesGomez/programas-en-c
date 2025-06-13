#include <stdio.h>
#include <stdlib.h>
#include <C:\Program Files\MySQL\MySQL Server 8.0\include\mysql.h>

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

    if (mysql_real_connect(con, "localhost", "root", "12345", "basedatos", 
        3306, NULL, 0) == NULL) {
        finish_with_error();
    }
}

void crear_persona(const char *nombre, int edad) {
    char query[256];
    snprintf(query, sizeof(query),
             "INSERT INTO personas(nombre, edad) VALUES('%s', %d)", nombre, edad);
    if (mysql_query(con, query)) {
        finish_with_error();
    } else {
        printf("Persona creada.\n");
    }
}

void leer_personas() {
    if (mysql_query(con, "SELECT id, nombre, edad FROM personas")) {
        finish_with_error();
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error();
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s\t", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(result);
}

void actualizar_persona(int id, const char *nuevo_nombre, int nueva_edad) {
    char query[256];
    snprintf(query, sizeof(query),
             "UPDATE personas SET nombre='%s', edad=%d WHERE id=%d",
             nuevo_nombre, nueva_edad, id);
    if (mysql_query(con, query)) {
        finish_with_error();
    } else {
        printf("Persona actualizada.\n");
    }
}

void eliminar_persona(int id) {
    char query[128];
    snprintf(query, sizeof(query), "DELETE FROM personas WHERE id=%d", id);
    if (mysql_query(con, query)) {
        finish_with_error();
    } else {
        printf("Persona eliminada.\n");
    }
}

int main() {
    conectar();

    crear_persona("Ana", 28);
    leer_personas();
    actualizar_persona(1, "Ana María", 29);
    eliminar_persona(1);

    mysql_close(con);
    return 0;
}


/**
 * 
# Install MySQL development library (for Ubuntu/Debian-based systems)

sudo apt-get install libmysqlclient-dev



# For macOS, use Homebrew

brew install mysql-client



# Compile the program with the correct include and library paths

gcc -o Demo /Users/nittos/Documents/GitHub/C_Programs/4.BaseDatos/Demo.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient

gcc -o Demo Demo.c \
  -I/usr/local/opt/mysql-client/include \
  -L/usr/local/opt/mysql-client/lib \
  -lmysqlclient

chmod +x Demo

./Demo
 */