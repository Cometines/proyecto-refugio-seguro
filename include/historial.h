#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "estructuras.h"

// ==========================================
// FUNCIONES DE LA PILA (HISTORIAL) | Kelaia
// ==========================================

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
void recogerOperacion(Operacion** tope_historial, TipoOperacion tipo, char* desc, int folio, int id_insumo, int cantidad);

/**
 * @brief Revierte la última acción y la saca de la pila
 * 
 * @param tope_historial Parametro struct de tipo Operacion que almacena el historial de operaciones.
 * @param cabeza_lista Parametro struct de tipo Familia que almacena la lista de familias (Cabeza hace referencia al ultimo familiar registrado).
 *                      @note Aquí solo lo usamos para volver al estado anterior de la estructura.
 * @param inventario Parametro Array que almacena 5 struct no autoreferenciales de tipo Insumo (no es una lista enlazada) y funge como inventario.
 */
void deshacerUltimaOperacion(Operacion** tope_historial, Familia** cabeza_lista, ColaAtencion** cola_atencion, Insumo inventario[]);

/**
 * @brief Función que se encarga de mostrar el historial de operaciones registrado.
 * 
 * @param tope_historial Parametro struct de tipo Operacion que almacena el historial de operaciones.
 */
void mostrarHistorial(Operacion** tope_historial);

#endif // HISTORIAL_H