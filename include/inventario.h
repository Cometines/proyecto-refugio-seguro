#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "estructuras.h"
typedef struct {
    char nombre[50];
    int cantidad;
} Insumo;

typedef struct {
    int integrantes;
} Familia;

// ==========================================
// FUNCIONES DEL MANEJO DE INVENTARIO | Randy
// ==========================================

void inicializarInventario(Insumo inventario[]) {
    strcpy(inventario[0].nombre, "Colchonetas");
    inventario[0].cantidad = 30;

    strcpy(inventario[1].nombre, "Agua");
    inventario[1].cantidad = 100;

    strcpy(inventario[2].nombre, "Alimentos");
    inventario[2].cantidad = 120;

    strcpy(inventario[3].nombre, "Kits de higiene");
    inventario[3].cantidad = 60;

    strcpy(inventario[4].nombre, "Medicamentos basicos");
    inventario[4].cantidad = 40;
}

void mostrarReporteInventario(Insumo inventario[]) {
    printf("\n===== INVENTARIO =====\n");

    for (int i = 0; i < 5; i++) {
        printf("%d. %s - Stock: %d", i, inventario[i].nombre, inventario[i].cantidad);

        // Disponibilidad
        if (inventario[i].cantidad > 0) {
            printf(" (Disponible)");
        } else {
            printf(" (Agotado)");
        }

        // Alerta de bajo stock
        if (inventario[i].cantidad <= 10) {
            printf(" <-- ALERTA: POCAS EXISTENCIAS");
        }

        printf("\n");
    }
}

void actualizarInsumo(Insumo inventario[], int id_insumo, int cantidad) {
    if (id_insumo < 0 || id_insumo >= 5) {
        printf("ID de insumo invalido\n");
        return;
    }

    inventario[id_insumo].cantidad += cantidad;

    if (inventario[id_insumo].cantidad < 0) {
        inventario[id_insumo].cantidad = 0;
    }
}

int calcularEntrega(Familia* familia) {
    int total = 0;

    // Ejemplo de medias por persona
    int agua = 3;        // 3 unidades por persona
    int alimentos = 2;   // 2 unidades por persona

    total = familia->integrantes * (agua + alimentos);

    return total;
}

void devolverStock(Insumo inventario[], int id_insumo, int cantidad) {
    actualizarInsumo(inventario, id_insumo, cantidad);
}


#endif