#ifndef ATENCION_H // if not defined
#define ATENCION_H

#include "estructuras.h"
#include <stdbool.h>

// ===================================
// FUNCIONES PRIMORDIALES PARA COLA (VALERIA)
// ===================================

// Retornar true si está vacía, si no: retornar false
bool colaVacia(ColaAtencion *cola_objetivo){

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
    NodoCola* nuevo_nodo = (NodoCola*)malloc(sizeof(NodoCola));
    if (nuevo_nodo == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nodo de la cola.\n");
        return;
    }

    // Asignar la familia
    
    nuevo_nodo->datos_familia=familia_a_encolar;
    nuevo_nodo->siguiente=NULL;

    // Manejar punteros frente y fondo (caso vacía o con elementos)
    if (colaVacia(cola_objetivo)) {
        cola_objetivo->frente = nuevo_nodo;
        cola_objetivo->fondo = nuevo_nodo;
    } else {
        cola_objetivo->fondo->siguiente = nuevo_nodo;
        cola_objetivo->fondo = nuevo_nodo;
    }

}

// Saca y devuelve al primer elemento en la cola especificada.
Familia* desencolarFamilia(ColaAtencion *cola_objetivo){
    if (colaVacia(cola_objetivo)) {
        return NULL; // No hay familias para desencolar
        printf("----No hay familias para desencolar----");
    }

    // Extraer el primer elemento
    NodoCola* nodo_a_eliminar = cola_objetivo->frente;
    Familia* familia_extraida = nodo_a_eliminar->familia;

    // Actualizar punteros
    cola_objetivo->frente = nodo_a_eliminar->siguiente;

    // Si la cola se quedó vacía, actualizamos el fondo a NULL también
    if (cola_objetivo->frente == NULL) {
        cola_objetivo->fondo = NULL;
    }
    printf("----La familia fue atendida exitosamente----");
    // Liberar la memoria del nodo
    free(nodo_a_eliminar);

    // Retornar el puntero a la Familia
    return familia_extraida;
}

// ===================================
// LÓGICA DEL NEGOCIO
// ===================================

// Función encargada de determinar a que cola se manda a la familia segun el atributo: NivelAtencion
void enrutarFamilia(ColaAtencion* cola_medica, ColaAtencion* cola_insumos, Familia* nueva_familia){
    
    //      USO DE SWITCH
    switch(nueva_familia->nivel_asignado){
        case ATENCION_BASICA:
        case ATENCION_ESPECIAL:
            encolarFamilia(cola_insumos, nueva_familia); 
            printf("Familia con folio: %s formada en cola de insumos.", nueva_familia->folio);
            break;
        case ATENCION_MEDICA:
        case ATENCION_COMPLETA:
            encolarFamilia(cola_medica, nueva_familia); 
            printf("Familia con folio: %s formada en cola medica.", nueva_familia->folio);
            break;
        default:
            printf("Nivel de atencion desconocido");
    }
}
// Atiende a la familia del frente, se guarda la operación y se encola en la cola de insumos
void atenderColaMedica(ColaAtencion* cola_medica, ColaAtencion* cola_insumos, Operacion** tope_historial){
    if (colaVacia(cola_medica)) {
        return;
    }
    // 1. Sacar a la familia de cola_medica
    Familia* Operacion = desencolarFamilia(cola_medica);

    // 2. Crear un registro de Operacion para la pila de historial
    registrarEnHistorial(tope_historial, familia->nivel_asignado, "Atencion Medica Completada");

    // 3. Encolarla automáticamente en cola_insumos
    encolarFamilia(cola_insumos, f);
}

    
// Atiende a la familia del frente, se guarda la operación y se resta en el stock del inventario
void atenderColaInsumos(ColaAtencion* cola_insumos){
 // 1. Sacar a la familia de la cola
    Familia* liberar = desencolarFamilia(cola_insumos);

    if (stock_global != NULL) {
        *stock_global -= insumos_requeridos;
        if (*stock_global < 0) {
            *stock_global = 0; // Evitar stock negativo por seguridad
        }
    }

}

// Imprimir un reporte visual de las familias que están esperando
void mostrarEstadoColas(ColaAtencion* cola_medica, ColaAtencion* cola_insumos){
//IMPRIMIR EL ESTAOD DE LAS COLAS (CON ESTETICA)
// Encabezado principal
    printf("\n=================================================\n");
    printf("           ESTADO ACTUAL DE LAS COLAS            \n");
    printf("=================================================\n\n");
    
    // --- COLA MÉDICA ---
    printf(" [+] COLA MÉDICA\n");
    printf("+------------+----------------------------------+\n");
    printf("| %-10s | %-32s |\n", "Folio", "Apellido");
    printf("+------------+----------------------------------+\n");
    
    if (colaVacia(cola_medica)) {
        // Reservamos 45 espacios (10 del folio + 3 del separador + 32 del apellido)
        printf("| %-45s |\n", " [Cola Vacía]"); 
    } else {
        NodoCola* actual = cola_medica->frente;
        while (actual != NULL) {
            if (actual->familia != NULL) {
                // %-10d reserva 10 espacios para el int
                // %-32.32s reserva 32 espacios y trunca a 32 caracteres max.
                printf("| %-10d | %-32.32s |\n", actual->familia->Folio, actual->familia->Apellido);
            }
            actual = actual->siguiente;
        }
    }
    printf("+------------+----------------------------------+\n\n");

    // --- COLA DE INSUMOS ---
    printf(" [+] COLA DE INSUMOS\n");
    printf("+------------+----------------------------------+\n");
    printf("| %-10s | %-32s |\n", "Folio", "Apellido");
    printf("+------------+----------------------------------+\n");
    
    if (colaVacia(cola_insumos)) {
        printf("| %-45s |\n", " [Cola Vacía]");
    } else {
        NodoCola* actual = cola_insumos->frente;
        while (actual != NULL) {
            if (actual->familia != NULL) {
                printf("| %-10d | %-32.32s |\n", actual->familia->Folio, actual->familia->Apellido);
            }
            actual = actual->siguiente;
        }
    }
    printf("+------------+----------------------------------+\n\n");

}

#endif