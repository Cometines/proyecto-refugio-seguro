#include <stdio.h>
#include <string.h>
#include "inventario.h"
#include "../include/estructuras.h" 

// ==============================
// Inicializar inventario
// ==============================
void inicializarInventario(Insumo inventario[]) {
    strcpy(inventario[0].nombre, "Colchonetas");
    inventario[0].cantidad_disponible = 30;

    strcpy(inventario[1].nombre, "Agua");
    inventario[1].cantidad_disponible = 100;

    strcpy(inventario[2].nombre, "Alimentos");
    inventario[2].cantidad_disponible = 120;

    strcpy(inventario[3].nombre, "Kits de higiene");
    inventario[3].cantidad_disponible = 60;

    strcpy(inventario[4].nombre, "Medicamentos basicos");
    inventario[4].cantidad_disponible = 40;
}

// ==============================
// Mostrar inventario
// ==============================
void mostrarReporteInventario(Insumo inventario[]) {
    printf("\n===== INVENTARIO =====\n");

    for (int i = 0; i < 5; i++) {
        printf("%d. %s - Stock: %d", i, inventario[i].nombre, inventario[i].cantidad_disponible);

        if (inventario[i].cantidad_disponible > 0)
            printf(" (Disponible)");
        else
            printf(" (Agotado)");

        if (inventario[i].cantidad_disponible <= 10)
            printf(" <-- ALERTA: POCAS EXISTENCIAS");

        printf("\n");
    }
}

// ==============================
// Actualizar inventario
// ==============================
void actualizarInsumo(Insumo inventario[], int id_insumo, int cantidad) {
    if (id_insumo < 0 || id_insumo >= 5) {
        printf("ID invalido\n");
        return;
    }

    inventario[id_insumo].cantidad_disponible += cantidad;

    if (inventario[id_insumo].cantidad_disponible < 0)
        inventario[id_insumo].cantidad_disponible = 0;
}

// ==============================
// Calcular entrega
// ==============================
int calcularEntrega(Familia* familia) {
    int agua = 3;
    int alimentos = 2;

    return familia->cantidad_integrantes * (agua + alimentos);
}

// ==============================
// Devolver stock
// ==============================
void devolverStock(Insumo inventario[], int id_insumo, int cantidad) {
    actualizarInsumo(inventario, id_insumo, cantidad);
}