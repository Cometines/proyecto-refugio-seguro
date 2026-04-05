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
        operacion_reciente->siguiente=tope_historial;
        *tope_historial=operacion_reciente;
    }
}

/** 
 *  @brief Recoge los valores de la operación nueva.
 *  @param tope_historial Parametro struct de tipo Operacion que almacena el historial de operaciones.
 *  @param tipo Parametro tipo enum que indicará el tipo de operación (REGISTRO_FAMILIA o ENTREGA_APOYO).
 *  @param desc Parametro tipo char que almacena una descripción/reporte de la operación.
 *                      @pre El char que se reciba no debe exceder el tamaño máximo de 100 bytes.
 *                      @pre No debe ser NULL.
 *  @param folio Parametro tipo int que almacena el folio del registro de una familia.
 *  @param id_insumo Parametro tipo int que tiene la finalidad de usarse como id de insumo pero se usa, en contexto de código, como index de un arreglo.
 *                      @invariant Sus valores solo pueden ir de 1 a 5 
 *                      @warning No debe ser NULL y debe cumplir con las condiciones siguientes.
 *                      @pre El valor debe ser tipo int
 *                      @pre Su valor no debe ser menos de 1.
 *                      @pre Su valor no debe sobrepasar 5.
 * 
 *  @param cantidad Parametro de tipo int que almacena la cantidad de un tipo de insumo.
*/
void recogerOperacion(Operacion** tope_historial, TipoOperacion tipo, char* desc, int folio, int id_insumo, int cantidad){
    operacion_reciente = (Operacion*) malloc(sizeof(Operacion*));
    operacion_reciente->tipo = tipo;
    strncpy(operacion_reciente->descripcion, desc, 99);
    operacion_reciente->descripcion[99] = '\0';
    operacion_reciente->folio_involucrado = folio;
    operacion_reciente->id_insumo_involucrado = id_insumo;
    operacion_reciente->cantidad_involucrada = cantidad;
    apilarOperacion(tope_historial);
}

/**
 * @brief Revierte la última acción y la saca de la pila
 * 
 * @param tope_historial Parametro struct de tipo Operacion que almacena el historial de operaciones.
 * @param cabeza_lista Parametro struct de tipo Familia que almacena la lista de familias (Cabeza hace referencia al ultimo familiar registrado).
 *                      @note Aquí solo lo usamos para volver al estado anterior de la estructura.
 * @param inventario Parametro Array que almacena 5 struct no autoreferenciales de tipo Insumo (no es una lista enlazada) y funge como inventario.
 */
void deshacerUltimaOperacion(Operacion** tope_historial, Familia** cabeza_lista, Insumo inventario[]){
    if (!vacio()){//Comprobamos que la pila de operaciones no esté vacía
        printf("No hay registros de operación");
        return;//Interrumpe la función si está vacío (no hay operaciones)
    }
    //Volvemos a los valores anteriores a nuevas operaciones correspondientes
    switch ((*tope_historial)->tipo){
        //Para Familia
        case REGISTRO_FAMILIA:
            Familia* familia_reciente = *cabeza_lista;
            if(*cabeza_lista != NULL)
                return;//Interrumpe la función
            *cabeza_lista = (*cabeza_lista)->siguiente;
            //Borramos (Liberamos usando la palabra reservada free) las operaciones que se introdujeron por último
            free(familia_reciente);
            break;
        
        //Para inventario de insumos
        case ENTREGA_APOYO:
            if(inventario[(*tope_historial)->id_insumo_involucrado].cantidad_disponible <= 0)
                return;//Interrumpe la función
            inventario[(*tope_historial)->id_insumo_involucrado].cantidad_disponible = (*tope_historial)->siguiente->cantidad_involucrada;
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

/**
 * @brief Función que se encarga de mostrar el historial de operaciones registrado.
 * 
 * @param tope_historial Parametro struct de tipo Operacion que almacena el historial de operaciones.
 */
void mostrarHistorial(Operacion* tope_historial){
    if(!vacio()){
        printf("No hay registros de operación\n----------------------\n\n");
        return;//Interrumpe la función si está vacío (no hay operaciones)
    }
    printf("\n----------------------\n");
    printf("\n| Tipo de operación\t| Descripción\t| Folio \t| Id de insumo\t| Cantidad");
    printf("\n----------------------\n");
    for(operacion_reciente = tope_historial;operacion_reciente != NULL;operacion_reciente = operacion_reciente->siguiente)
    {
        printf("| %d ",operacion_reciente->tipo);
        printf("| %s ",operacion_reciente->descripcion);
        printf("| %s ",operacion_reciente->folio_involucrado);
        printf("| %s ",operacion_reciente->id_insumo_involucrado);
        printf("| %s ",operacion_reciente->cantidad_involucrada);
        printf("\n----------------------\n");
    }
}