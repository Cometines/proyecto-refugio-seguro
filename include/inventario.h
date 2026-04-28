#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "estructuras.h"

// Inicializa el inventario
void inicializarInventario(Insumo inventario[]);

// Muestra inventario y alertas
void mostrarReporteInventario(Insumo inventario[]);

// Suma o resta stock
void actualizarInsumo(Insumo inventario[], int id_insumo, int cantidad);

// Calcula insumos según integrantes
int calcularEntrega(Familia* familia);

// Devuelve stock (deshacer)
void devolverStock(Insumo inventario[], int id_insumo, int cantidad);

#endif