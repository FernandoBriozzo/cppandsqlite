#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <list>
#include "migration.h"
#include <wchar.h>
#include <locale.h>

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

static int callback2(void* data, int argc, char** argv, char** azColName) {
    //int * a = reinterpret_cast<int*>(data);
    //*a = std::atoi(argv[0]);
    string query, query2, query3 = "";
    query = "SELECT c.nombre, c.cp, c.population FROM CIUDAD c INNER JOIN PROVINCIA p on c.prov_id = p.id WHERE p.id = ";
    query2 = argv[0];
    query3 = query + query2;
    sqlite3 *db;
    char *zErrMsg = 0;
    sqlite3_open("test.db", &db);
    sqlite3_exec(db, query3.c_str(), callback, NULL, &zErrMsg);
    sqlite3_close(db);
    return 0;
    }
    
static int callback3(void * notUsed, int argc, char **argv, char **azColName) {
      printf("%s : %s\n", argv[0], argv[1]);
   return 0;
}

struct ciudad {
    int id;
    string nombre;
    string cp;
    int provid;
    };

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    string sql;
    string input;
    int c, d = 99;
    string id, nombre, cp, pob, nombreProv, prov_id, valor;
    int* provid;
    int* h = 0;

   //createTables("test.db");

   rc = sqlite3_open("test.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      getchar();
      return(0);
   } else {
      //fprintf(stderr, "Opened database successfully\n");
   }
   sqlite3_exec(db, "PRAGMA foreign_keys = on", 0, NULL, NULL);
    cout<<"Bienvenido, esta es una pequeña aplicación que le permitirá crear, mostrar, modificar y eliminar ciudades dentro de una base de datos"<<endl<<endl;
    while(c =! 0) {
        cout<<  "Elija la opción que desea realizar: \n" \
                "1: Crear ciudad nueva.\n" \
                "2: Modificar ciudad existente.\n" \
                "3: Eliminar ciudad existente.\n" \
                "4: Mostrar listado de todas las ciudades.\n" \
                "5: Mostrar las ciudades de una provincia determinada.\n"\
                "6: Borrar la Base de Datos\n"\
                "0: Salir"<<endl;
    
        getline(cin,input);
        c = std::atoi(input.c_str());
        switch(c) {
            case 1:
                cout<<"Ingrese el nombre de la ciudad: (0: Volver)\n";
                getline(cin, nombre);
                if (nombre == "0") break;
                cout<<"Ingrese el código postal de la ciudad: (0: Volver)\n";
                getline(cin, cp);
                if (cp == "0") break;
                cout<<"Ingrese la población de la ciudad: (0: Volver)\n";
                getline(cin, pob);
                if (pob == "0") break;
                sql = "SELECT * FROM PROVINCIA;";
                cout<<endl;
                sqlite3_exec(db, sql.c_str(), callback3, NULL, &zErrMsg);
                cout<<"\nIngrese el id de la provincia: (0: Volver)\n";
                getline(cin, prov_id);
                if (prov_id == "0") break;
                sql = "INSERT INTO CIUDAD ('nombre', 'cp', 'population', 'prov_id') VALUES ('" + nombre + "', '" + cp + "', '" + pob + "', '" + prov_id + "');";
                rc = sqlite3_exec(db, sql.c_str(), 0, NULL, &zErrMsg);
                if( rc != SQLITE_OK ){
                    fprintf(stderr, "SQL error: %s\n", zErrMsg);
                    sqlite3_free(zErrMsg);
                } else {
                    fprintf(stdout, "Ciudad Ingresada Correctamente\n\n");
                }
                break;
            case 2:
                cout<<"Ingrese el id de la ciuad a Modificar: \n";
                sql ="SELECT id, nombre from CIUDAD;";
                sqlite3_exec(db, sql.c_str(), callback3, NULL, NULL);
                cout<<"0: Salir\n";
                getline(cin, id);
                if (id == "0") break;
                cout<<  "Elija el valor que quiera cambiar: \n" \
                        "1: nombre.\n" \
                        "2: código postal.\n" \
                        "3: población. \n" \
                        "0: Volver\n";
                getline(cin, valor);
                if (valor == "0") break;
                d = std::atoi(valor.c_str());
                switch(d) {
                    case 1:
                        cout<<"Ingrese el nuevo nombre: ";
                        getline(cin, valor);
                        sql = "UPDATE CIUDAD SET 'nombre' = '" + valor + "' where id = " + id;
                        rc = sqlite3_exec(db, sql.c_str(), 0, NULL, &zErrMsg);
                        if( rc != SQLITE_OK ){
                            fprintf(stderr, "SQL error: %s\n", zErrMsg);
                            sqlite3_free(zErrMsg);
                        } else {
                            fprintf(stdout, "Ciudad Modificada Correctamente\n\n");
                        }
                        break;
                    case 2:
                        cout<<"Ingrese el nuevo código postal: ";
                        getline(cin, valor);
                        sql = "UPDATE CIUDAD SET 'cp' = '" + valor + "' where id = " + id;
                        rc = sqlite3_exec(db, sql.c_str(), 0, NULL, &zErrMsg);
                        if( rc != SQLITE_OK ){
                            fprintf(stderr, "SQL error: %s\n", zErrMsg);
                            sqlite3_free(zErrMsg);
                        } else {
                            fprintf(stdout, "Ciudad Modificada Correctamente\n\n");
                        }
                        break;
                    case 3:
                        cout<<"Ingrese la nueva población: ";
                        getline(cin, valor);
                        sql = "UPDATE CIUDAD SET 'population' = '" + valor + "' where id = " + id;
                        rc = sqlite3_exec(db, sql.c_str(), 0, NULL, &zErrMsg);
                        if( rc != SQLITE_OK ){
                            fprintf(stderr, "SQL error: %s\n", zErrMsg);
                            sqlite3_free(zErrMsg);
                        } else {
                            fprintf(stdout, "Ciudad Modificada Correctamente\n\n");
                        }
                        break;
                    default :
                        cout<<"opcion no válida";
                    }
                
                break;
            case 3:
                cout<<"Elija el id de la ciudad a eliminar: \n";
                sql ="SELECT id, nombre FROM CIUDAD;";
                sqlite3_exec(db, sql.c_str(), callback3, NULL, NULL);
                cout<<"0: Volver\n";
                getline (cin, input);
                if (input == "0") break;
                sql = "DELETE FROM CIUDAD WHERE ID = " + input;
                rc = sqlite3_exec(db, sql.c_str(), 0, NULL, &zErrMsg);
                if( rc != SQLITE_OK ){
                    fprintf(stderr, "SQL error: %s\n", zErrMsg);
                    sqlite3_free(zErrMsg);
                } else {
                    fprintf(stdout, "Ciudad eliminada exitosamente\n");
                }
                break;
            case 4:
                sql = "SELECT c.nombre as 'Nombre', c.cp as 'Código Postal', c.population as 'Población', p.nombre as 'Provincia' FROM CIUDAD c inner join PROVINCIA p on c.prov_id = p.id;";
                sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
                break;
            case 5:
                cout<<"Escriba el id de la Provincia:\n";
                sql = "SELECT id, nombre FROM PROVINCIA;";
                sqlite3_exec(db, sql.c_str(), callback3, NULL, NULL);
                cout<<"0: Volver\n";
                getline(cin, valor);
                if (valor == "0") break;
                sql = "SELECT * FROM PROVINCIA WHERE id = '" + valor + "';";
                sqlite3_exec(db, sql.c_str(), callback2, &provid, &zErrMsg);
                break;
            case 6:
                createTables("test.db");
                break;
            case 0:
                cout<<"Hasta luego!"<<endl;
                getchar();
                exit(0);
            default:
                cout<<  "La opcion que eligio no es válida.\n";
        }
    }
    // Execute SQL statement 
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }
    
    sqlite3_close(db);
    getchar();
}
