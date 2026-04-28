#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "estructuras.h"

/**
 * @brief Carga familias, inventario y reconstruye el estado de las colas desde disco (lectura de archivo).
 * 
 * @param cabeza_lista 
 * @param inventario 
 * @param cola_medica 
 * @param cola_insumos 
 */
void cargarDatosArchivo(Familia** cabeza_lista, Insumo inventario[], ColaAtencion* cola_medica, ColaAtencion* cola_insumos);

/**
 * @brief Guarda familias, inventario y la secuencia de folios en las colas en un archivo .csv
 * 
 * @param cabeza_lista 
 * @param inventario 
 * @param cola_medica 
 * @param cola_insumos 
 */
void guardarDatosArchivo(Familia** cabeza_lista, Insumo inventario[], ColaAtencion* cola_medica, ColaAtencion* cola_insumos);

#endif