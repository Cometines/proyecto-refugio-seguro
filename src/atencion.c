#include "../include/atencion.h"
#include "../include/historial.h"
#include "../include/inventario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool colaVacia(ColaAtencion *cola_objetivo){
    return (cola_objetivo == NULL || cola_objetivo->frente == NULL);
}

static void copiarCola(ColaAtencion* origen, ColaAtencion* destino) {
    inicializarCola(destino);
    if (origen == NULL || colaVacia(origen)) return;
    
    NodoCola* actual = origen->frente;
    while(actual != NULL) {
        // Encolamos la MISMA familia en la nueva cola
        encolarFamilia(destino, actual->datos_familia); 
        actual = actual->siguiente;
    }
}

void inicializarCola(ColaAtencion *cola_objetivo){
    if (cola_objetivo != NULL) {
        cola_objetivo->frente = NULL;
        cola_objetivo->fondo = NULL;
    }
}

void guardarEstadoColas(Colas** historial_colas) {
    Colas* nuevo_estado = (Colas*)malloc(sizeof(Colas));

    if (*historial_colas == NULL) {
        inicializarCola(&nuevo_estado->cola_medica);
        inicializarCola(&nuevo_estado->cola_insumos);
        nuevo_estado->siguiente = NULL;
    } else {
        copiarCola(&(*historial_colas)->cola_medica, &nuevo_estado->cola_medica);
        copiarCola(&(*historial_colas)->cola_insumos, &nuevo_estado->cola_insumos);
        // Lo apilamos encima
        nuevo_estado->siguiente = *historial_colas;
    }

    *historial_colas = nuevo_estado;
}


void encolarFamilia(ColaAtencion *cola_objetivo, Familia *familia_a_encolar){
    NodoCola* nuevo_nodo = (NodoCola*)malloc(sizeof(NodoCola));
    if (nuevo_nodo == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nodo de la cola.\n");
        return;
    }

    nuevo_nodo->datos_familia = familia_a_encolar;
    nuevo_nodo->siguiente = NULL;

    if (colaVacia(cola_objetivo)) {
        cola_objetivo->frente = nuevo_nodo;
        cola_objetivo->fondo = nuevo_nodo;
    } else {
        cola_objetivo->fondo->siguiente = nuevo_nodo;
        cola_objetivo->fondo = nuevo_nodo;
    }
}

Familia* desencolarFamilia(ColaAtencion *cola_objetivo){
    if (colaVacia(cola_objetivo)) {
        printf("----La cola esta vacia----\n");
        return NULL; 
    }

    NodoCola* nodo_a_eliminar = cola_objetivo->frente;
    Familia* familia_extraida = nodo_a_eliminar->datos_familia; // Corregido: era datos_familia, no familia

    cola_objetivo->frente = nodo_a_eliminar->siguiente;

    if (cola_objetivo->frente == NULL) {
        cola_objetivo->fondo = NULL;
    }
    
    free(nodo_a_eliminar);
    return familia_extraida;
}

void enrutarFamilia(ColaAtencion* cola_medica, ColaAtencion* cola_insumos, Familia* nueva_familia){
    if(nueva_familia == NULL) return;

    switch(nueva_familia->nivel_asignado){
        case ATENCION_BASICA:
        case ATENCION_ESPECIAL:
            encolarFamilia(cola_insumos, nueva_familia); 
            printf("Familia con folio: %s formada en COLA DE INSUMOS.\n", nueva_familia->folio);
            break;
        case ATENCION_MEDICA:
        case ATENCION_COMPLETA:
            encolarFamilia(cola_medica, nueva_familia); 
            printf("Familia con folio: %s formada en COLA MEDICA.\n", nueva_familia->folio);
            break;
        default:
            printf("Nivel de atencion desconocido\n");
    }
}

void atenderColaMedica(ColaAtencion* cola_medica, ColaAtencion* cola_insumos, Operacion** tope_historial, Colas** historial_colas){
    guardarEstadoColas(historial_colas);
    if (colaVacia(&(*historial_colas)->cola_medica)) {
        printf("No hay familias en la cola medica.\n");
        return;
    }
    
    Familia* fam_atendida = desencolarFamilia(&(*historial_colas)->cola_medica);
    printf("El medico ha finalizado la atencion de la familia %s.\n", fam_atendida->folio);
    
    // Ahora pasa a la cola de insumos
    recogerOperacion(tope_historial, SERVICIO_MEDICO, "Atención medica realizada", fam_atendida->folio, 0, 0);
    encolarFamilia(&(*historial_colas)->cola_insumos, fam_atendida);
    printf("La familia ha sido transferida a la COLA DE INSUMOS.\n");
}

void atenderColaInsumos(ColaAtencion* cola_insumos, Insumo inventario[], Operacion** tope_historial, Colas** historial_colas){
    guardarEstadoColas(historial_colas);
    if (colaVacia(&(*historial_colas)->cola_insumos)) {
        printf("No hay familias en la cola de insumos.\n");
        return;
    }
    
    Familia* fam = desencolarFamilia(&(*historial_colas)->cola_insumos);
    int intg = fam->cantidad_integrantes;
    
    // Cálculos de raciones en base a la cantidad de integrantes
    int cant_colchonetas = intg * 1;
    int cant_agua = intg * 3;
    int cant_alimentos = intg * 2;
    int cant_higiene = intg * 1;
    int cant_medicamentos = intg * 1;
    
    // Descontar del inventario y registrar en el historial según el ID de inicializarInventario
    
    // 0: Colchonetas
    actualizarInsumo(inventario, 0, -cant_colchonetas);
    //recogerOperacion(tope_historial, ENTREGA_APOYO, "Entrega de Colchonetas", 0, 0, cant_colchonetas);
    
    // 1: Agua
    actualizarInsumo(inventario, 1, -cant_agua);
    //recogerOperacion(tope_historial, ENTREGA_APOYO, "Entrega de Agua", 0, 1, cant_agua);
    
    // 2: Alimentos
    actualizarInsumo(inventario, 2, -cant_alimentos);
    //recogerOperacion(tope_historial, ENTREGA_APOYO, "Entrega de Alimentos", 0, 2, cant_alimentos);
    
    // 3: Kits de higiene
    actualizarInsumo(inventario, 3, -cant_higiene);
    //recogerOperacion(tope_historial, ENTREGA_APOYO, "Entrega de Kits de Higiene", 0, 3, cant_higiene);
    
    // 4: Medicamentos basicos
    actualizarInsumo(inventario, 4, -cant_medicamentos);
    recogerOperacion(tope_historial, ENTREGA_APOYO, "ENTREGA INSUMOS", 0, 0, cant_colchonetas);
    
    fam->requerimiento_especial_atendido = true; // Marcamos a la familia como atendida

    printf("\nSe ha entregado el apoyo completo a la familia %s (Integrantes: %d).\n", fam->folio, intg);
    printf("- %d Colchonetas\n", cant_colchonetas);
    printf("- %d Raciones de Agua\n", cant_agua);
    printf("- %d Raciones de Alimentos\n", cant_alimentos);
    printf("- %d Kits de Higiene\n", cant_higiene);
    printf("- %d Medicamentos Basicos\n", cant_medicamentos);
}

void mostrarEstadoColas(Colas** historial_colas){
    printf("\n=================================================\n");
    printf("           ESTADO ACTUAL DE LAS COLAS            \n");
    printf("=================================================\n\n");
    
    printf(" [+] COLA MEDICA\n");
    printf("+-----------------+----------------------------------+\n");
    printf("| %-15s | %-32s |\n", "Folio", "Representante");
    printf("+-----------------+----------------------------------+\n");
    if (colaVacia(&(*historial_colas)->cola_medica)) {
        printf("| %-50s |\n", " [Cola Vacia]"); 
    } else {
        NodoCola* actual = (*historial_colas)->cola_medica.frente;
        while (actual != NULL) {
            // Corregido: Se usa %s para el folio (es char array) y nombres correctos de la estructura
            printf("| %-15s | %-32.32s |\n", actual->datos_familia->folio, actual->datos_familia->nombre_representante);
            actual = actual->siguiente;
        }
    }
    printf("+-----------------+----------------------------------+\n\n");

    printf(" [+] COLA DE INSUMOS\n");
    printf("+-----------------+----------------------------------+\n");
    printf("| %-15s | %-32s |\n", "Folio", "Representante");
    printf("+-----------------+----------------------------------+\n");
    if (colaVacia(&(*historial_colas)->cola_insumos)) {
        printf("| %-50s |\n", " [Cola Vacia]");
    } else {
        NodoCola* actual = (*historial_colas)->cola_insumos.frente;
        while (actual != NULL) {
            printf("| %-15s | %-32.32s |\n", actual->datos_familia->folio, actual->datos_familia->nombre_representante);
            actual = actual->siguiente;
        }
    }
    printf("+-----------------+----------------------------------+\n\n");
}