/**
 * @file historial.c
 * @author Kelaia Reyes Torres
 * @brief Archivo .c con el objetivo de implementar funciones que manejen al historial
 * @version 0.1
 * @date 2026-04-03
 * 
 */
#include "../include/historial.h"
#include "../include/atencion.h"
#include "../include/inventario.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 *  @note El orden de estas funciones static (En este contexto, llamadas Helper Functions)
 *                   es importante debido a la forma de compilar de C.
*/


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

static bool tipoOperacionVacia(Operacion** tope_historial, Familia** cabeza_lista, Insumo inventario[]){
    Operacion* tipo = *tope_historial;
    if (tipo == REGISTRO_FAMILIA && cabeza_lista == NULL)
        return true;
    if (tipo == ENTREGA_APOYO && inventario[(*tope_historial)->estructuras.id_insumo_involucrado].cantidad_disponible <= 0)
        return true;
    return false;
}

/** 
 *  @brief Función de apoyo que guarda la nueva acción en la cima de la pila.
 *  @param tope_historial Parametro struct de tipo Operacion que almacena el historial de operaciones
*/
static void apilarOperacion(Operacion** tope_historial, Operacion* operacion_reciente){
    if(primer_operacion == NULL){
        operacion_reciente->siguiente=NULL;
        *tope_historial=primer_operacion=operacion_reciente;
    }
    else{
        operacion_reciente->siguiente=*tope_historial;
        *tope_historial=operacion_reciente;
    }
}

static void deshacerEnrutarFamilia(Operacion** tope_historial, Familia** cabeza_lista, Colas** historial_colas) {
    if (historial_colas == NULL || *historial_colas == NULL) return;

    // 1. ELIMINAR DE LA LISTA PRINCIPAL
    if (*cabeza_lista != NULL) {
        *cabeza_lista = (*cabeza_lista)->siguiente;
        printf("Registro de familia eliminado de la lista principal.\n");
    }

    // 2. REVERTIR ESTADO DE LAS COLAS
        Colas* estado_a_eliminar = *historial_colas;

        while (!colaVacia(&estado_a_eliminar->cola_medica)) {
            desencolarFamilia(&estado_a_eliminar->cola_medica);
        }
        while (!colaVacia(&estado_a_eliminar->cola_insumos)) {
            desencolarFamilia(&estado_a_eliminar->cola_insumos);
        }

        // Retrocedemos al snapshot anterior
        *historial_colas = (*historial_colas)->siguiente;
        free(estado_a_eliminar);
}

void recogerOperacion(Operacion** tope_historial, TipoOperacion tipo, char* desc, char* folio, int id_insumo, int cantidad){
    Operacion* operacion_reciente = (Operacion*) malloc(sizeof(Operacion));
    operacion_reciente->tipo = tipo;
    strncpy(operacion_reciente->descripcion, desc, 99);
    operacion_reciente->descripcion[99] = '\0';
    
    if (tipo == REGISTRO_FAMILIA || tipo == SERVICIO_MEDICO) {
        strncpy(operacion_reciente->estructuras.folio_involucrado, folio, 15);
        operacion_reciente->estructuras.folio_involucrado[15] = '\0';
    }
    else if (tipo == ENTREGA_APOYO) {
        operacion_reciente->estructuras.id_insumo_involucrado = id_insumo;
        operacion_reciente->estructuras.cantidad_involucrado = cantidad;
    }
    apilarOperacion(tope_historial, operacion_reciente);
}

void deshacerUltimaOperacion(Operacion** tope_historial, Familia** cabeza_lista, Insumo inventario[], Colas** historial_colas){
//    printf("hola entrada");
    if (vacio()){//Comprobamos que la pila de operaciones no esté vacía
        printf("No hay registros de operación\n");
        return;//Interrumpe la función si está vacío (no hay operaciones)
    }
    //printf("hola if");
    if(tipoOperacionVacia(tope_historial, cabeza_lista, inventario))//Comprobamos si el tipo de operación que se revertirá se encuentra en el estado necesario (no vacio)
        return;//Interrumpimos la funcion

//    printf("hola switch");
    //Volvemos a los valores anteriores a nuevas operaciones correspondientes
    switch ((*tope_historial)->tipo){
        //Para Familia
        case REGISTRO_FAMILIA:{
            deshacerEnrutarFamilia(tope_historial, cabeza_lista, historial_colas);
            //Borramos (Liberamos usando la palabra reservada free) las operaciones que se introdujeron por último
            break;
        }
        //Para inventario de insumos
        case ENTREGA_APOYO: {
        //cant_colchonetas = 1 por integrante de familia por lo tanto intg = cantidad de colchonetas (cantidad_involucrado)
//            printf("hola entrega");
            int intg = (*tope_historial)->estructuras.cantidad_involucrado;

            actualizarInsumo(inventario, 0, (intg * 1)); 
            actualizarInsumo(inventario, 1, (intg * 3)); 
            actualizarInsumo(inventario, 2, (intg * 2)); 
            actualizarInsumo(inventario, 3, (intg * 1)); 
            actualizarInsumo(inventario, 4, (intg * 1));

            Colas* estado_a_eliminar = *historial_colas;

            while (!colaVacia(&estado_a_eliminar->cola_medica)) 
                desencolarFamilia(&estado_a_eliminar->cola_medica);
            while (!colaVacia(&estado_a_eliminar->cola_insumos))
                desencolarFamilia(&estado_a_eliminar->cola_insumos);

            // Retrocedemos al snapshot anterior
            *historial_colas = (*historial_colas)->siguiente;
            free(estado_a_eliminar);

            printf("Se ha revertido la entrega de insumos y devuelto todo el stock.\n");
            break;
        }
        case SERVICIO_MEDICO:
            if (historial_colas != NULL && (*historial_colas)->siguiente != NULL) {
                Colas* estado_equivocado = *historial_colas;
                
                // Es vital vaciar los nodos NodoCola de este estado para evitar fugas de memoria
                while(!colaVacia(&estado_equivocado->cola_medica)) 
                    desencolarFamilia(&estado_equivocado->cola_medica);
                while(!colaVacia(&estado_equivocado->cola_insumos)) 
                    desencolarFamilia(&estado_equivocado->cola_insumos);

                *historial_colas = (*historial_colas)->siguiente;
                
                free(estado_equivocado);
                printf("El estado de las colas ha sido revertido exitosamente.\n");
            }
            break;

        default:
            //Mensjaje de error.
            fprintf(stderr, "No fue posible detectar un tipo de operación");
            return;
    }
    //Para historial de operaciones
    Operacion* operacion_reciente = *tope_historial;
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
    
    printf("\n-------------------------------------------------------------------\n");
    printf("| %-15s | %-30s | %-20s | %-15s | %-15s |", "TIPO", "DESCRIPCIÓN", "FOLIO", "ID INSUMO", "CANTIDAD INT");
    printf("\n-------------------------------------------------------------------\n");
    Operacion* i;
    for(i = (*tope_historial); i != NULL; i = i->siguiente)
    {
        if(i->tipo == REGISTRO_FAMILIA){
            printf("| %-15s ", "REGISTRO");
            printf("| %-30s ",i->descripcion);
            printf("| %-20s ",i->estructuras.folio_involucrado);
            printf("| %-15s ", "N/A");
            printf("| %-15s ", "N/A");
        }
        else if(i->tipo == ENTREGA_APOYO){
            printf("| %-15s ", "ENTREGA");
            printf("| %-30s ",i->descripcion);
            printf("| %-20s ", "N/A");
            printf("| %-15d ",i->estructuras.id_insumo_involucrado);
            printf("| %-15d ",i->estructuras.cantidad_involucrado);
        }
        else if(i->tipo == SERVICIO_MEDICO){
            printf("| %-15s ", "MEDICO");
            printf("| %-30s ",i->descripcion);
            printf("| %-10s ",i->estructuras.folio_involucrado);
            printf("| %-15s ", "N/A");
            printf("| %-15s ", "N/A");
        }
        printf("\n-------------------------------------------------------------------\n");
    }
}