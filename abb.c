#include "abb.h"
#include <string.h>
struct abb_nodo{
	void* dato;
	char* clave;
	abb_nodo_t* izq;
	abb_nodo_t* der;
};

struct abb{
	abb_nodo_t* raiz;
	size_t cantidad;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
};

/* ******************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/


char *duplicar_clave(const char *clave){
char *dup_clave = malloc(sizeof(char)*(strlen(clave) + 1));
	if(dup_clave == NULL){
		return NULL;
	}
	strcpy(dup_clave, clave);
	return dup_clave;
}

abb_nodo_t* abb_nodo_crear(const char* clave, void* dato){
	abb_nodo_t* nuevo_nodo = malloc(sizeof(abb_nodo_t));

	if(!nuevo_nodo) return NULL;
	nuevo_nodo->clave = duplicar_clave(clave);
	nuevo_nodo->dato = dato;

	nuevo_nodo->izq = NULL;
	nuevo_nodo->der = NULL;

	return nuevo_nodo;
}

bool abb_es_nodo_hoja(abb_nodo_t* nodo_actual){
	if(nodo_actual->izq == NULL && nodo_actual->der == NULL) {
		return true;
	}
	return false;
}

abb_nodo_t* abb_buscar_padre(abb_nodo_t* padre, const char* clave, abb_comparar_clave_t cmp){
	if(!padre) return NULL;

	if(abb_es_nodo_hoja(padre)) return padre;

	if(cmp(padre->clave, clave) < 0){
		if(!padre->der) return padre;

		if(cmp(padre->der->clave, clave) == 0) return padre;	

		return abb_buscar_padre(padre->der, clave, cmp);
	}else if(cmp(padre->clave, clave) > 0){
		if(!padre->izq) return padre;

		if(cmp(padre->izq->clave, clave) == 0) return padre;	
		
		return abb_buscar_padre(padre->izq, clave, cmp);
	}

	return padre;
}

abb_nodo_t* abb_buscar_nodo(abb_nodo_t* padre, const char* clave, abb_comparar_clave_t cmp){
	if(!padre) return NULL;

	if(cmp(padre->clave, clave) == 0){
		return padre;
	}else if(cmp(padre->clave, clave) < 0){
		return abb_buscar_nodo(padre->der, clave, cmp);
	}

	return abb_buscar_nodo(padre->izq, clave, cmp);
}

void abb_swap_nodos(abb_nodo_t* padre, abb_nodo_t* hijo){
	char* clave_aux= padre->clave;
	void* dato_aux= padre->dato;
	padre->clave= hijo->clave;
	padre->dato= hijo->dato;
	hijo->clave= clave_aux;
	hijo->dato= dato_aux;
}

void* abb_borrar_nodo(abb_nodo_t* nodo_borrar) {
	void* dato= nodo_borrar->dato;
	free(nodo_borrar->clave);
	free(nodo_borrar);
	return dato;
}

void* abb_borrar_hoja(abb_t* arbol, abb_nodo_t* padre, abb_nodo_t* hijo){
	if(arbol->raiz == hijo){
		arbol->raiz = NULL;
	}
	if(arbol->cmp(padre->clave, hijo->clave) < 0){
		padre->der = NULL;
	}else if (arbol->cmp(padre->clave, hijo->clave) > 0){
		padre->izq = NULL;
	}

	return abb_borrar_nodo(hijo);
}


void abb_actualizar_nodo(abb_nodo_t* padre, abb_nodo_t* hijo,  abb_destruir_dato_t destruir_dato){
	abb_swap_nodos(padre, hijo);
	void* dato = abb_borrar_nodo(hijo);

	if(destruir_dato != NULL) destruir_dato(dato);
}

abb_nodo_t* abb_buscar_hijo(abb_nodo_t* padre){
	if(padre->izq != NULL) return padre->izq;

	return padre->der;
}

bool abb_es_nodo_un_hijo(abb_nodo_t* nodo_actual) {
	if(nodo_actual->izq != NULL && nodo_actual->der == NULL) {
		return true;
	}else if(nodo_actual->der != NULL && nodo_actual->izq == NULL){
		return true;
	}
	return false;
}

void* abb_borrar_un_hijo(abb_t* arbol, abb_nodo_t* nodo_padre, abb_nodo_t* nodo_hijo){
	
	if(nodo_hijo == arbol->raiz){
		arbol->raiz = abb_buscar_hijo(nodo_hijo);
	}

	if(arbol->cmp(nodo_padre->clave, nodo_hijo->clave) < 0){
		nodo_padre->der = abb_buscar_hijo(nodo_hijo);
	}else if(arbol->cmp(nodo_padre->clave, nodo_hijo->clave) > 0){
		nodo_padre->izq = abb_buscar_hijo(nodo_hijo);
	}

	return abb_borrar_nodo(nodo_hijo);
}

bool abb_es_nodo_dos_hijos(abb_nodo_t* nodo_hijo){
	if(nodo_hijo->izq != NULL && nodo_hijo->der != NULL) return true;

	return false;
}

abb_nodo_t* abb_buscar_reemplazante(abb_nodo_t* padre){
	abb_nodo_t* nodo_actual = padre->der;
	while(nodo_actual->izq != NULL){
		nodo_actual = nodo_actual->izq;
	}

	return nodo_actual;
}

void* abb_borrar_dos_hijos(abb_t* arbol, abb_nodo_t* nodo_padre, abb_nodo_t* nodo_hijo){
	abb_nodo_t* reemplazante = abb_buscar_reemplazante(nodo_hijo);
	abb_nodo_t* padre_reemplazante = abb_buscar_padre(nodo_hijo, reemplazante->clave, arbol->cmp);
	abb_swap_nodos(nodo_hijo, reemplazante);
	void* dato = NULL;
	if(reemplazante->der != NULL){
		dato = abb_borrar_un_hijo(arbol, padre_reemplazante, reemplazante);
	}else{
		dato = abb_borrar_hoja(arbol, padre_reemplazante, reemplazante);
	}

	return dato;
}

/* ******************************************************************
 *                     PRIMITIVAS
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* nuevo_abb = malloc(sizeof(abb_t));

	if(!nuevo_abb) return NULL;
	nuevo_abb->raiz = NULL;
	nuevo_abb->cantidad = 0;
	nuevo_abb->cmp = cmp;
	nuevo_abb->destruir_dato = destruir_dato;

	return nuevo_abb;
}


bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

	abb_nodo_t* nuevo_nodo = abb_nodo_crear(clave, dato);
	if(!nuevo_nodo) return false;

	abb_nodo_t* padre = abb_buscar_padre(arbol->raiz, clave, arbol->cmp);
	if(!padre){
		arbol->raiz = nuevo_nodo;
		arbol->cantidad++;
	}else{
		if(arbol->cmp(padre->clave, clave) < 0){
			if(!padre->der){
				padre->der = nuevo_nodo;
				arbol->cantidad++;
			}else{
				abb_actualizar_nodo(padre, nuevo_nodo, arbol->destruir_dato);	
			} 
		}else if(arbol->cmp(padre->clave, clave) > 0){
			if(!padre->izq){
				padre->izq = nuevo_nodo;
				arbol->cantidad++;
			}else{
				abb_actualizar_nodo(padre, nuevo_nodo, arbol->destruir_dato);	
			} 
		}else{
			abb_actualizar_nodo(padre, nuevo_nodo, arbol->destruir_dato);
		}
	}
	
	return true;
}

void *abb_borrar(abb_t *arbol, const char *clave){
	if(!arbol->raiz) return NULL;

	abb_nodo_t* nodo_hijo = abb_buscar_nodo(arbol->raiz, clave, arbol->cmp);
	if(!nodo_hijo) return NULL;
	abb_nodo_t* nodo_padre = abb_buscar_padre(arbol->raiz, clave, arbol->cmp);
	void* dato = NULL;

	if(abb_es_nodo_hoja(nodo_hijo)){
		dato = abb_borrar_hoja(arbol, nodo_padre, nodo_hijo);
	}else if(abb_es_nodo_un_hijo(nodo_hijo)){
		dato = abb_borrar_un_hijo(arbol, nodo_padre, nodo_hijo);
	}else if(abb_es_nodo_dos_hijos(nodo_hijo)){
		dato = abb_borrar_dos_hijos(arbol, nodo_padre, nodo_hijo);
	}

	arbol->cantidad--;

	return dato;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	abb_nodo_t* nodo = abb_buscar_nodo(arbol->raiz, clave, arbol->cmp);

	if(!nodo) return NULL;
	return nodo->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	abb_nodo_t* nodo = abb_buscar_nodo(arbol->raiz, clave, arbol->cmp);

	if(!nodo) return false;
	return true;
}

size_t abb_cantidad(abb_t *arbol){
	return arbol->cantidad;
}

void _abb_destruir(abb_t* arbol, abb_nodo_t* nodo_actual) {
	if(nodo_actual == NULL) {
		return;
	}
	_abb_destruir(arbol, nodo_actual->izq);
	_abb_destruir(arbol, nodo_actual->der);
	void* dato = abb_borrar_nodo(nodo_actual);
	
	if(arbol->destruir_dato != NULL) {
		arbol->destruir_dato(dato);
	}
}

void abb_destruir(abb_t *arbol){
	_abb_destruir(arbol, arbol->raiz);
	free(arbol);
}