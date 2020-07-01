#include "migration.h"
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

static int callbackMultiple(void *data, int argc, char **argv, char **azColName) {
    //@TODO: hacer la callback para juntar los datos del select
    return 0;
}

static int callbackSingle(void *data, int argc, char **argv, char **azColName) {
    //@TODO: hacer el calback para un solo dato
    return 0;
    }


void createTables(string database) {
    sqlite3 *db;
    char *zErrMsg;
    string sql;

    int rc = sqlite3_open(database.c_str(), &db);
    
    if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      getchar();
   }   
   rc = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "Execution Failed: %s\n", &zErrMsg);
      getchar();
   }
   
    sql = "DROP TABLE IF EXISTS CIUDAD;";
    sqlite3_exec(db, sql.c_str(), 0, NULL, &zErrMsg);
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      getchar();
    }
    
    sql = "DROP TABLE IF EXISTS PROVINCIA;";
    sqlite3_exec(db, sql.c_str(), 0, NULL, &zErrMsg);
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      getchar();
    }
    
    sql =    "CREATE TABLE PROVINCIA("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombre varchar(50) NOT NULL UNIQUE,"
                    "codigo varchar(2) NOT NULL UNIQUE,"
                    "capital_id int);";

    rc = sqlite3_exec(db, sql.c_str(), 0, NULL, &zErrMsg);
    
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      getchar();
    }
   
   sql =    "CREATE TABLE CIUDAD("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "nombre varchar(50) NOT NULL UNIQUE,"
            "cp varchar(10) NOT NULL UNIQUE,"
            "population int,"
            "prov_id INTEGER not null,"
            "FOREIGN KEY (prov_id) REFERENCES PROVINCIA(id));";

    rc = sqlite3_exec(db, sql.c_str(), 0, NULL, &zErrMsg);
    
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      getchar();
   }

    sql =   "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Ciudad de Buenos Aires', 'DF');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Buenos Aires', 'BA');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Catamarca', 'CA');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Chaco', 'CH');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Chubut', 'CT');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Córdoba', 'CB');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Corrientes', 'CR');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Entre Ríos', 'ER');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Formosa', 'FO');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Jujuy', 'JY');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('La Pampa', 'LP');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('La Rioja', 'LR');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Mendoza', 'MZ');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Misiones', 'MI');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Neuquén', 'NQ');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Río Negro', 'RN');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Salta', 'SA');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('San Juan', 'SJ');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('San Luis', 'SL');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Santa Cruz', 'SC');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Santa Fe', 'SF');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Santiago del Estero', 'SE');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Tierra del Fuego', 'TF');" \
            "INSERT INTO PROVINCIA ('nombre', 'codigo') VALUES ('Tcucumán', 'TU');";
            
    rc = sqlite3_exec(db, sql.c_str(), 0, NULL, &zErrMsg);
    
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      getchar();
   }
    
    if (rc == SQLITE_OK) {
        printf("Operación realizada con éxito!\n\n");
        }
        
    sqlite3_close(db);
    
    }
