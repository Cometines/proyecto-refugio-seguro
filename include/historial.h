#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "estructuras.h"

// ==========================================
// FUNCIONES DE LA PILA (HISTORIAL) | Kelaia
// ==========================================

// Guarda una nueva acción en la cima de la pila
void apilarOperacion(Operacion** tope_historial, TipoOperacion tipo, char* desc, int folio, int id_insumo, int cantidad);

// Revierte la última acción y la saca de la pila
void deshacerUltimaOperacion(Operacion** tope_historial, Familia** cabeza_lista, Insumo inventario[]);

// Muestra las últimas acciones realizadas
void mostrarHistorial(Operacion* tope_historial);

#endif // HISTORIAL_H