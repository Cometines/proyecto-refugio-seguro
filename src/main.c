#include <stdio.h>
#include <stdlib.h>

// Módulos del sistema
#include "../include/estructuras.h" 
#include "../include/inventario.h"
#include "../include/familias.h"
#include "../include/atencion.h"
#include "../include/historial.h"
#include "../include/menu.h" 
#include "../include/archivos.h"

int main() {
    // 1. Inicializar variables principales
    Familia* lista_familias = NULL;                 
    
    // Ahora son DOS colas, según la arquitectura que definimos
    ColaAtencion cola_medica;
    ColaAtencion cola_insumos;                       
    
    Insumo inventario[5];                           
    Operacion* historial_operaciones = NULL;        
    
    // 2. Inicializar las estructuras para que no apunten a basura en memoria
    // (Aseguramos que los punteros internos arranquen en NULL y contadores en 0)
    //inicializarCola(&cola_medica);
    //inicializarCola(&cola_insumos);
    // inicializarInventario(inventario); // Descomentar cuando el .c de Randy esté listo

    printf("Iniciando sistema...\n");
    cargarDatosArchivo(&lista_familias, inventario, &cola_medica, &cola_insumos);
    
    int opcion = 0;

    // 3. Bucle principal
    do {
        limpiarConsola(); // Función que agregó Kelaia para mantener limpia la pantalla
        mostrarMenu();
        
        opcion = pedirEntero("Seleccione una opcion: ");

        switch(opcion) {
            case 1:
                limpiarConsola();
                // Ervin ya hizo un submenú completo, ¡lo mandamos llamar directo!
                menuFamilias(&lista_familias);
                break;
                
            case 2:
                limpiarConsola();
                printf("\n--- ENCOLAR PARA ATENCION ---\n");
                printf("Aqui el Integrante 3 pedira el folio, buscara a la familia y llamara a enrutarFamilia()\n");
                // Ejemplo de lo que ira aqui:
                // char* folio = pedirCadena("Ingrese folio: ");
                // Familia* fam = buscarFamiliaPorFolio(lista_familias, folio);
                // if (fam) enrutarFamilia(&cola_medica, &cola_insumos, fam);
                break;
                
            case 3:
                limpiarConsola();
                printf("\n--- ENTREGAR APOYO ---\n");
                printf("Aqui ira un pequeno sub-menu para decidir si se atiende al doctor o insumos\n");
                break;
                
            case 4:
                limpiarConsola();
                printf("\n--- REPORTE CONSOLIDADO ---\n");
                mostrarFamiliasRegistradas(lista_familias); 
                // mostrarReporteInventario(inventario); 
                // mostrarEstadoColas(&cola_medica, &cola_insumos); 
                break;
                
            case 5:
                printf("\n--- DESHACER ULTIMA ACCION ---\n");
                deshacerUltimaOperacion(&historial_operaciones, &lista_familias, inventario);
                break;
                
            case 6:
                printf("\nGuardando datos...\n");
                guardarDatosArchivo(&lista_familias, inventario, &cola_medica, &cola_insumos);
                printf("¡Hasta pronto!\n");
                break;
                
            default:
                printf("\n[!] Opcion no valida (1-6).\n");
        }
        
        // Evitamos pausar la pantalla si entraron al caso 1, porque el menuFamilias ya hace su propia pausa al salir.
        if (opcion != 6 && opcion != 1) {
            pausarPantalla(); 
        }
        
    } while(opcion != 6);

    return 0;
}