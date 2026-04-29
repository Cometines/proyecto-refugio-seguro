#ifndef ATENCION_H // if not defined
#define ATENCION_H

#include "estructuras.h"
#include <stdbool.h>

// ===================================
// FUNCIONES PRIMORDIALES PARA COLA (VALERIA)
// ===================================

// Retornar true si está vacía, si no: retornar false
bool colaVacia(ColaAtencion *cola_objetivo);{

    return (cola_objetivo == NULL || cola_objetivo->frente == NULL);
    printf("\n----COLA VACIA----\n");
}
// Para inicializar los punteros de la cola (frente y fondo)=null;
/**
 * @brief Inicializa una estructura de datos de tipo Cola.
 *
 * Esta función prepara una cola para su uso inicial estableciendo sus 
 * punteros de control (`frente` y `fondo`) a NULL, lo que indica lógicamente 
 * que la cola está vacía. Incluye una validación de seguridad para evitar 
 * una violación de acceso a memoria (segmentation fault) si se pasa un 
 * puntero nulo.
 *
 * @param cola_objetivo Puntero a la estructura Cola que se va a inicializar. 
 * Si el puntero pasado es NULL, la función termina de manera 
 * segura sin realizar ninguna operación.
 */
void inicializarCola(ColaAtencion *cola_objetivo){
    if (cola_objetivo != NULL) {
        cola_objetivo->frente = NULL;
        cola_objetivo->fondo = NULL;
    }
}


// Recibe a que cola se van a mandar, recibe la familia que se va a encolar
void encolarFamilia(ColaAtencion *cola_objetivo, Familia *familia_a_encolar){
    //colaVacia();
    cola_objetivo* nuevoNodo = (cola_objetivo*)malloc(sizeof(cola_objetivo));
    if (nuevoNodo == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nodo de la cola.\n");
        return;
    }

    // Asignar la familia
    nuevoNodo->familia = f;
    nuevoNodo->siguiente = NULL;

    // Manejar punteros frente y fondo (caso vacía o con elementos)
    if (colaVacia(cola_objetivo)) {
        cola_objetivo->frente = nuevoNodo;
        cola_objetivo->fondo = nuevoNodo;
    } else {
        cola_objetivo->fondo->siguiente = nuevoNodo;
        cola_objetivo->fondo = nuevoNodo;
    }
}

// Saca y devuelve al primer elemento en la cola especificada.
Familia* desencolarFamilia(ColaAtencion *cola_objetivo){
    if (colaVacia(cola_objetivo)) {
        return NULL; // No hay familias para desencolar
        printf("No hay familias para desencolar");
    }

    // Extraer el primer elemento
    NodoCola* nodoAExtraer = cola_objetivo->frente;
    Familia* familiaExtraida = nodoAEliminar->familia;

    // Actualizar punteros
    cola_objetivo->frente = cola_objetivo->frente->siguiente;

    // Si la cola se quedó vacía, actualizamos el fondo a NULL también
    if (cola_objetivo->frente == NULL) {
        cola_objetivo->fondo = NULL;
    }

    // Liberar la memoria del nodo
    free(nodoAEliminar);

    // Retornar el puntero a la Familia
    return familiaExtraida;
}

// ===================================
// LÓGICA DEL NEGOCIO
// ===================================

// Función encargada de determinar a que cola se manda a la familia segun el atributo: NivelAtencion
void enrutarFamilia(ColaAtencion* cola_medica, ColaAtencion* cola_insumos, Familia* nueva_familia){
    if (f == NULL) return;
    //      USO DE SWITCH

// Atiende a la familia del frente, se guarda la operación y se encola en la cola de insumos
void atenderColaMedica(ColaAtencion* cola_medica, ColaAtencion* cola_insumos, Operacion** tope_historial);
if (colaVacia(cola_medica)) {
        return;
    }
    
// Atiende a la familia del frente, se guarda la operación y se resta en el stock del inventario
void atenderColaInsumos(ColaAtencion* cola_insumos);

// Buscar a la familia con requerimiento especial y atenderlo (marcar como true el campo)
void entregarRequerimientoEspecial(Familia* familia_objetivo,Operacion** tope_historial);

// Imprimir un reporte visual de las familias que están esperando
void mostrarEstadoColas(ColaAtencion* cola_medica, ColaAtencion* cola_insumos);

#endif