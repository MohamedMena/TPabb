#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // For ssize_t in Linux.

// Funciones de gestion de random
void random_inicializar(){
	unsigned int seed = (unsigned int)time(NULL);
	srand (seed);
}

size_t nuestro_random(size_t lim){
	return rand()%lim;
}

void swap_claves(char** x, char** y){
	char* aux=*x;
	*x=*y;
	*y=aux;
}

void swap_valores(int** x, int** y){
	int* aux=*x;
	*x=*y;
	*y=aux;
}
     
// desordena el vector
void vector_desordenar(char* claves[], int* valores[], size_t largo){
	random_inicializar();
	size_t i;
	size_t rnd;
	
	for (i=0; i<largo;i++){
		rnd=nuestro_random(largo);
		swap_claves(&claves[i], &claves[rnd]);
		swap_valores(&valores[i], &valores[rnd]);
	}

}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/


static void prueba_crear_abb_vacio() {
    abb_t* arbol = abb_crear(strcmp, NULL);

    print_test("Prueba abb crear abb vacio", arbol);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(arbol, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(arbol, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(arbol, "A"));

    abb_destruir(arbol);
    printf("\n");
}

static void prueba_abb_insertar() {
	
    abb_t* arbol = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    // Inserta 1 valor y luego lo borra
    print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(arbol, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(arbol, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

    // Inserta otros 2 valores y no los borra (se destruyen con el abb)
    print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(arbol, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(arbol, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(arbol, clave3));

    abb_destruir(arbol);
    printf("\n");
}

static void prueba_abb_inserto_y_borro() {
	
	abb_t* arbol = abb_crear(strcmp, NULL);
	
	char *clave1 = "Argentina", *valor1 = "Messi";
	char *clave2 = "Republica de Corea", *valor2 = "Son";
	char *clave3 = "Colombia", *valor3 = "James";
	char *clave4 = "Mexico", *valor4 = "Chicarito";
	char *clave5 = "Uruguay", *valor5 = "Suarez";
	char *clave6 = "Alemania", *valor6 = "Kross";
	char *clave7 = "Arabia Saudita", *valor7 = "Al-Sahlawi";
	char *clave8 = "Rusia", *valor8 = "Dzyuba";
	char *clave9 = "Nigeria", *valor9 = "Musa";
	char *clave10 = "Croacia", *valor10 = "Modric";
	char *clave11 = "Portugal", *valor11 = "Ronaldo";
	char *clave12 = "Egipto", *valor12 = "Salah";
	char *clave13 = "España", *valor13 = "Iniesta";
	char *clave14 = "Iran", *valor14 = "Jahanbakhsh";

	
	// Inserto 
	print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1));
	print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2));
	print_test("Prueba abb insertar clave3", abb_guardar(arbol, clave3, valor3));
	print_test("Prueba abb insertar clave4", abb_guardar(arbol, clave4, valor4));
	print_test("Prueba abb insertar clave5", abb_guardar(arbol, clave5, valor5));
	print_test("Prueba abb insertar clave6", abb_guardar(arbol, clave6, valor6));
	print_test("Prueba abb insertar clave7", abb_guardar(arbol, clave7, valor7));
	print_test("Prueba abb insertar clave8", abb_guardar(arbol, clave8, valor8));
	print_test("Prueba abb insertar clave9", abb_guardar(arbol, clave9, valor9));
	print_test("Prueba abb insertar clave10", abb_guardar(arbol, clave10, valor10));
	print_test("Prueba abb insertar clave11", abb_guardar(arbol, clave11, valor11));
	print_test("Prueba abb insertar clave12", abb_guardar(arbol, clave12, valor12));
	print_test("Prueba abb insertar clave13", abb_guardar(arbol, clave13, valor13));
	print_test("Prueba abb insertar clave14", abb_guardar(arbol, clave14, valor14));
	print_test("Prueba abb la cantidad de elementos es 14", abb_cantidad(arbol) == 14);
	
	// Borro
	
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(arbol, clave1) == valor1);
	print_test("Prueba abb borrar clave5, es valor5", abb_borrar(arbol, clave5) == valor5);
	print_test("Prueba abb borrar clave7, es valor7", abb_borrar(arbol, clave7) == valor7);
	print_test("Prueba abb borrar clave10, es valor10", abb_borrar(arbol, clave10) == valor10);
	print_test("Prueba abb la cantidad de elementos es 10", abb_cantidad(arbol) == 10);
	
	
	abb_destruir(arbol);
    printf("\n");
}

static void prueba_abb_inserto_y_borro_destruyo_dato(){
	
	abb_t* arbol = abb_crear(strcmp, NULL);
	
	char *clave1 = "Argentina", *valor1 = "Messi";
	char *clave2 = "Republica de Corea", *valor2 = "Son";
	char *clave3 = "Colombia", *valor3 = "James";
	char *clave4 = "Mexico", *valor4 = "Chicarito";
	char *clave5 = "Uruguay", *valor5 = "Suarez";
	char *clave6 = "Alemania", *valor6 = "Kross";
	char *clave7 = "Arabia Saudita", *valor7 = "Al-Sahlawi";
	char *clave8 = "Rusia", *valor8 = "Dzyuba";
	char *clave9 = "Nigeria", *valor9 = "Musa";
	char *clave10 = "Croacia", *valor10 = "Modric";
	char *clave11 = "Portugal", *valor11 = "Ronaldo";
	char *clave12 = "Egipto", *valor12 = "Salah";
	char *clave13 = "España", *valor13 = "Iniesta";
	char *clave14 = "Iran", *valor14 = "Jahanbakhsh";
	char *clave15 = "Marruecos", *valor15 = "Dirar";

	
	// Inserto y borro
	print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1));
	print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2));
	print_test("Prueba abb insertar clave3", abb_guardar(arbol, clave3, valor3));
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(arbol, clave1) == valor1);
	print_test("Prueba abb borrar clave3, es valor3", abb_borrar(arbol, clave3) == valor3);
	print_test("Prueba abb insertar clave4", abb_guardar(arbol, clave4, valor4));
	print_test("Prueba abb insertar clave5", abb_guardar(arbol, clave5, valor5));
	print_test("Prueba abb insertar clave6", abb_guardar(arbol, clave6, valor6));
	print_test("Prueba abb borrar clave4, es valor4", abb_borrar(arbol, clave4) == valor4);
	print_test("Prueba abb insertar clave7", abb_guardar(arbol, clave7, valor7));
	print_test("Prueba abb insertar clave8", abb_guardar(arbol, clave8, valor8));
	print_test("Prueba abb borrar clave8, es valor8", abb_borrar(arbol, clave8) == valor8);
	print_test("Prueba abb insertar clave10", abb_guardar(arbol, clave10, valor10));
	print_test("Prueba abb borrar clave6, es valor6", abb_borrar(arbol, clave6) == valor6);
	print_test("Prueba abb insertar clave11", abb_guardar(arbol, clave11, valor11));
	print_test("Prueba abb borrar clave11, es valor11", abb_borrar(arbol, clave11) == valor11);
	print_test("Prueba abb insertar clave12", abb_guardar(arbol, clave12, valor12));
	print_test("Prueba abb borrar clave12, es valor12", abb_borrar(arbol, clave12) == valor12);
	print_test("Prueba abb insertar clave13", abb_guardar(arbol, clave13, valor13));
	print_test("Prueba abb borrar clave13, es valor13", abb_borrar(arbol, clave13) == valor13);
	print_test("Prueba abb insertar clave14", abb_guardar(arbol, clave14, valor14));
	print_test("Prueba abb borrar clave14, es valor14", abb_borrar(arbol, clave14) == valor14);
	print_test("Prueba abb insertar clave15", abb_guardar(arbol, clave15, valor15));
	print_test("Prueba abb borrar clave15, es valor15", abb_borrar(arbol, clave15) == valor15);
	print_test("Prueba abb insertar clave9", abb_guardar(arbol, clave9, valor9));
	print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(arbol) == 5);
	
	abb_destruir(arbol);
    printf("\n");
	
}

static void prueba_abb_reemplazar() {
	
    abb_t* arbol = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    // Inserta 2 valores y luego los reemplaza
    print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

    abb_destruir(arbol);
    printf("\n");
}

static void prueba_abb_reemplazar_con_destruir() {
	
    abb_t* arbol = abb_crear(strcmp, free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    // Pide memoria para 4 valores 
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    // Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) 
    print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

    //Se destruye el abb (se debe liberar lo que quedó dentro) 
    abb_destruir(arbol);
     printf("\n");
}

static void prueba_abb_borrar() {
	
    abb_t* arbol = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    // Inserta 3 valores y luego los borra 
    print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1));
    print_test("Prueba abbb insertar clave2", abb_guardar(arbol, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(arbol, clave3, valor3));

    // Al borrar cada elemento comprueba que ya no está pero los otros sí. 
    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(arbol, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(arbol, clave3) == valor3);
    print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(arbol, clave3));
    print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(arbol, clave3));
    print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(arbol, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(arbol, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(arbol, clave1) == valor1);
    print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(arbol, clave3));
    print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(arbol, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(arbol, clave1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);

    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(arbol, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(arbol, clave2) == valor2);
    print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(arbol, clave3));
    print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(arbol, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(arbol, clave2));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

    abb_destruir(arbol);
    printf("\n");
}

static void prueba_abb_clave_vacia() {
	
    abb_t* arbol = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(arbol, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(arbol, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(arbol, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(arbol, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

    abb_destruir(arbol);
    printf("\n");
}

static void prueba_abb_valor_null() {
	
    abb_t* arbol = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    // Inserta 1 valor y luego lo borra 
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(arbol, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(arbol, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(arbol, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(arbol, clave) == valor);
	print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

	abb_destruir(arbol);
    printf("\n");
}

void pruebas_abb_alumno(){
	
	prueba_crear_abb_vacio();
	prueba_abb_insertar();
	prueba_abb_reemplazar();
	prueba_abb_reemplazar_con_destruir();
	prueba_abb_borrar();
	prueba_abb_clave_vacia();
	prueba_abb_valor_null();
	prueba_abb_inserto_y_borro();
    prueba_abb_inserto_y_borro_destruyo_dato();
}
