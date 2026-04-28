/**
 * @file historial.c
 * @author Kelaia Reyes Torres
 * @brief Archivo .c con el objetivo de implementar funciones que manejen al historial
 * @version 0.1
 * @date 2026-04-03
 * 
 */
#include "../include/historial.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 *  @note El orden de estas funciones static (En este contexto, llamadas Helper Functions)
 *                   es importante debido a la forma de compilar de C.
*/


static Operacion* operacion_reciente;
static Operacion* primer_operacion = NULL;

/**
 *  @brief Función de apoyo que retorna un valor boleano dependiendo el estado de la pila (Vacio o no)
 *  @return true o false
*/
static bool vacio(){
    if (primer_operacion == NULL)
        return true;
    return false;
}

static bool tipoOperacionVacia(TipoOperacion tipo, Familia** cabeza_lista, Insumo inventario[]){
    if (tipo == REGISTRO_FAMILIA && cabeza_lista == NULL)
        return true;
    if (tipo == ENTREGA_APOYO && inventario[operacion_reciente->estructuras.id_insumo_involucrado].cantidad_disponible <= 0)
        return true;
    return false;
}

/** 
 *  @brief Función de apoyo que guarda la nueva acción en la cima de la pila.
 *  @param tope_historial Parametro struct de tipo Operacion que almacena el historial de operaciones
*/
static void apilarOperacion(Operacion** tope_historial){
    if(primer_operacion == NULL){
        operacion_reciente->siguiente=NULL;
        *tope_historial=primer_operacion=operacion_reciente;
    }
    else{
        operacion_reciente->siguiente=*tope_historial;
        *tope_historial=operacion_reciente;
    }
}

void recogerOperacion(Operacion** tope_historial, TipoOperacion tipo, char* desc, int folio, int id_insumo, int cantidad){
    operacion_reciente = (Operacion*) malloc(sizeof(Operacion));
    operacion_reciente->tipo = tipo;
    strncpy(operacion_reciente->descripcion, desc, 99);
    operacion_reciente->descripcion[99] = '\0';

    if (tipo == REGISTRO_FAMILIA) {
        operacion_reciente->estructuras.folio_involucrado = folio;
    }
    else if (tipo == ENTREGA_APOYO) {
        operacion_reciente->estructuras.id_insumo_involucrado = id_insumo;
        operacion_reciente->estructuras.cantidad_involucrado = cantidad;
    }
    apilarOperacion(tope_historial);
}

void deshacerUltimaOperacion(Operacion** tope_historial, Familia** cabeza_lista, ColaAtencion** cola_atencion, Insumo inventario[]){
    if (vacio()){//Comprobamos que la pila de operaciones no esté vacía
        printf("No hay registros de operación");
        return;//Interrumpe la función si está vacío (no hay operaciones)
    }
    if(tipoOperacionVacia((*tope_historial)->tipo, cabeza_lista, inventario))//Comprobamos si el tipo de operación que se revertirá se encuentra en el estado necesario (no vacio)
        return;//Interrumpimos la funcion

    //Volvemos a los valores anteriores a nuevas operaciones correspondientes
    switch ((*tope_historial)->tipo){
        //Para Familia
        case REGISTRO_FAMILIA:{
            Familia* familia_reciente = *cabeza_lista;
            ColaAtencion* cola_atencion_reciente = *cola_atencion;
            *cabeza_lista = (*cabeza_lista)->siguiente;
            (*cola_atencion)->frente = (*cola_atencion)->frente->siguiente;
            
            //Borramos (Liberamos usando la palabra reservada free) las operaciones que se introdujeron por último
            free(familia_reciente);
            free(cola_atencion_reciente);
            break;
        }
        //Para inventario de insumos
        case ENTREGA_APOYO:
            inventario[(*tope_historial)->estructuras.id_insumo_involucrado].cantidad_disponible = (*tope_historial)->siguiente->estructuras.cantidad_involucrado;
            break;
        
        default:
            //Mensjaje de error.
            fprintf(stderr, "No fue posible detectar un tipo de operación");
            return;
    }
    //Para historial de operaciones
    *tope_historial = (*tope_historial)->siguiente;
    //Borramos (Liberamos usando la palabra reservada free) las operaciones que se introdujeron por último
    free(operacion_reciente);
    //Reiniciamos primer_operacion (fondo) como NULL para evitar un error de memoria
    if (*tope_historial == NULL)
        primer_operacion = NULL;  
}

void mostrarHistorial(Operacion** tope_historial){
    if(vacio()){
        printf("No hay registros de operación\n----------------------\n\n");
        return;//Interrumpe la función si está vacío (no hay operaciones)
    }
    
    printf("\n----------------------\n");
    printf("\n| Tipo de operación\t| Descripción\t| Folio \t| Id de insumo\t| Cantidad");
    printf("\n----------------------\n");
    for(operacion_reciente = (*tope_historial);operacion_reciente != NULL;operacion_reciente = operacion_reciente->siguiente)
    {
        printf("| %d ",operacion_reciente->tipo);
        printf("| %s ",operacion_reciente->descripcion);
        if(operacion_reciente->tipo == REGISTRO_FAMILIA){
            printf("| %d ",operacion_reciente->estructuras.folio_involucrado);
            printf("Sin dato");
            printf("Sin dato");
        }
        else if(operacion_reciente->tipo == ENTREGA_APOYO){
            printf("Sin dato");
            printf("| %d ",operacion_reciente->estructuras.id_insumo_involucrado);
            printf("| %d ",operacion_reciente->estructuras.cantidad_involucrado);
        }
        printf("\n----------------------\n");
    }
}