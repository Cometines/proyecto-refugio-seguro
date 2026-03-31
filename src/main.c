#include <stdio.h>
#include <stdlib.h>

// Módulos del sistema
#include "../include/estructuras.h" 
#include "../include/inventario.h"
#include "../include/familias.h"
#include "../include/atencion.h"
#include "../include/historial.h"
#include "../include/menu.h" 

int main() {
    // 1. Inicializar variables
    Familia* lista_familias = NULL;                 
    ColaAtencion cola_espera = {NULL, NULL};                       
    Insumo inventario[5];                           
    Operacion* historial_operaciones = NULL;        
    
    inicializar_inventario(inventario);

    // 2. Cargar datos previos
    printf("Iniciando sistema...\n");
    // cargar_datos_csv(&lista_familias, inventario);
    
    int opcion = 0;

    // 3. Bucle principal con tu nueva UI
    do {
        mostrarMenu();
        
        opcion = pedirEntero("Seleccione una opcion: ");

        switch(opcion) {
            case 1:
                printf("\n--- ALTA DE FAMILIAS ---\n");
                // registrar_familia(&lista_familias);
                break;
            case 2:
                printf("\n--- ENCOLAR PARA ATENCION ---\n");
                break;
            case 3:
                printf("\n--- ENTREGAR APOYO ---\n");
                break;
            case 4:
                printf("\n--- REPORTE CONSOLIDADO ---\n");
                break;
            case 5:
                printf("\n--- DESHACER ULTIMA ACCION ---\n");
                break;
            case 6:
                printf("\nGuardando datos...\n");
                // guardar_datos_csv(lista_familias, inventario);
                printf("¡Hasta pronto!\n");
                break;
            default:
                printf("\n[!] Opcion no valida (1-6).\n");
        }
        
        if (opcion != 6) {
            pausarPantalla(); // Para que el usuario alcance a leer lo que pasó
        }
        
    } while(opcion != 6);

    return 0;
}