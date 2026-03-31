#ifndef ATENCION_H
#define ATENCION_H

#include "estructuras.h"

// ===================================================
// FUNCIONES DE LA COLA (COLA DE ATENCION) | Elizabeth
// ===================================================


// Pide un folio y lo agrega al final de la cola
void encolarFamilia(ColaAtencion* cola);

// Saca al primero de la cola, le entrega apoyos (modifica inventario) y guarda la acción en la pila
void atenderFamilia(ColaAtencion* cola, Insumo inventario[], Operacion** tope_historial);

// Función auxiliar para saber si hay gente esperando
int colaVacia(ColaAtencion* cola);

#endif // ATENCION_H