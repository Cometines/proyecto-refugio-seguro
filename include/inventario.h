#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "estructuras.h"

// ==========================================
// FUNCIONES DEL MANEJO DE INVENTARIP | Randy
// ==========================================

// Inicializa el arreglo con las 5 categorías de insumos en cero
void inicializarInventario(Insumo inventario[]);

// Muestra la tabla con las existencias actuales
void mostrarReporteInventario(Insumo inventario[]);

// Función auxiliar para sumar o restar existencias (se usa al atender o al deshacer)
void actualizarInsumo(Insumo inventario[], int id_insumo, int cantidad);

//sixseven

#endif