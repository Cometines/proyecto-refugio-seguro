#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Módulos del sistema
#include "../include/estructuras.h" 
#include "../include/inventario.h"
#include "../include/familias.h"
#include "../include/atencion.h"
#include "../include/historial.h"
#include "../include/menu.h" 
#include "../include/archivos.h"

int main() {
    srand(time(NULL));

    // 1. Inicializar variables principales
    Familia* lista_familias = NULL;                 
    ColaAtencion cola_medica;
    ColaAtencion cola_insumos;                       
    Insumo inventario[5];                           
    Operacion* historial_operaciones = NULL;        
    
    // 2. Inicializar las estructuras
    inicializarCola(&cola_medica);
    inicializarCola(&cola_insumos);
    inicializarInventario(inventario);

    printf("Iniciando sistema...\n");
    cargarDatosArchivo(&lista_familias, inventario, &cola_medica, &cola_insumos);
    
    int opcion = 0;

    // 3. Bucle principal
    do {
        limpiarConsola(); 
        mostrarMenu();
        
        opcion = pedirEntero("Seleccione una opcion: ");

        switch(opcion) {
            case 1:
                limpiarConsola();
                menuFamilias(&lista_familias, &cola_medica, &cola_insumos);
                break;
                
            case 2: {
                limpiarConsola();
                printf("\n--- ATENCION EN VENTANILLA ---\n");
                printf("1. Atender al siguiente paciente en la Cola Medica\n");
                printf("2. Entregar insumos a la siguiente familia en la Cola de Insumos\n");
                int sub_op = pedirEntero("Seleccione la accion: ");
                
                if (sub_op == 1) {
                    atenderColaMedica(&cola_medica, &cola_insumos, &historial_operaciones);
                } else if (sub_op == 2) {
                    atenderColaInsumos(&cola_insumos, inventario, &historial_operaciones);
                } else {
                    printf("Opcion no valida.\n");
                }
                break;
            }
                
            case 3:
                limpiarConsola();
                printf("\n--- REPORTE CONSOLIDADO ---\n");
                mostrarFamiliasRegistradas(lista_familias); 
                mostrarReporteInventario(inventario); 
                mostrarEstadoColas(&cola_medica, &cola_insumos); 
                break;
                
            case 4:
                printf("\n--- DESHACER ULTIMA ACCION ---\n");
                ColaAtencion *ptr = &cola_medica;
                deshacerUltimaOperacion(&historial_operaciones, &lista_familias, &ptr, inventario);
                break;
                
            case 5:
                printf("\nGuardando datos en disco...\n");
                guardarDatosArchivo(&lista_familias, inventario, &cola_medica, &cola_insumos);
                printf("¡Sistema cerrado exitosamente, hasta pronto!\n");
                break;
                
            default:
                printf("\n[!] Opcion no valida (1-5).\n");
        }
        
        if (opcion != 5 && opcion != 1) {
            pausarPantalla(); 
        }
        
    } while(opcion != 5);

    return 0;
}