#ifndef FAMILIAS_H
#define FAMILIAS_H

#include "estructuras.h"

// ==========================================
// FUNCIONES DEL REGISTRO DE FAMILIAS | Ervin
// ==========================================

// Pide los datos al usuario, crea un nodo y lo enlaza al final de la lista
void registrarFamilia(Familia** cabeza_lista, ColaAtencion* cola_medica, ColaAtencion* cola_insumos);

// Imprime todas las familias registradas (para el reporte consolidado)
void mostrarFamiliasRegistradas(Familia* cabeza_lista);

// Busca una familia específica por su número de folio (útil para la atención)
Familia* buscarFamiliaPorFolio(Familia* cabeza_lista, char *folio);

// Funcion que gestiona los metodos de familia
void menuFamilias(Familia** puntero_lista_main, ColaAtencion* cola_medica, ColaAtencion* cola_insumos);

#endif 