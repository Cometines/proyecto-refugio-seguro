#include <stdio.h>
#include <stdlib.h>
#include "../include/menu.h"

void mostrar_menu_principal() {
    printf("\n=========================================\n");
    printf("       REFUGIO SEGURO - SOCONUSCO        \n");
    printf("=========================================\n");
    printf("1. Registrar nueva familia (Censo)\n");
    printf("2. Formar familia en cola de atencion\n");
    printf("3. Atender familia (Entregar apoyos)\n");
    printf("4. Ver reportes (Inventario y Ocupacion)\n");
    printf("5. Deshacer ultima accion (Ctrl+Z)\n");
    printf("6. Guardar y Salir\n");
    printf("=========================================\n");
}

// --- Detección del Sistema Operativo ---

#ifdef _WIN32
    // Si es Windows, incluir la librería de Windows para Sleep()
    #include <windows.h>
#else
    // Si no es Windows (asumimos UNIX: Linux/macOS), incluir unistd.h
    #include <unistd.h> // Para usleep()
#endif

// ----------------------------------------

/**
 * @brief 
 * 
 * @param mensaje 
 * @return int 
 */
int pedirEntero(const char* mensaje){
    int digito = 0, n = 0;
    printf("%s", mensaje);
    do
    {
        n = scanf("%d", &digito);
        if (n !=1)
        {
            printf("Por favor, ingresa un valor númerico valido: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                // Descarta caracteres
            }
        }
    } while (n!=1);
    return digito;
}

/**
 * @brief 
 * 
 * @param mensaje 
 * @return char* 
 */
char* pedirCadena(const char* mensaje){
    char* cadena = malloc(50 * sizeof(char));

    if (cadena == NULL){
        fprintf(stderr, "Error: No fue posible asignar memoria");
        return NULL;
    }
    else{
        printf("%s", mensaje);
        fgets(cadena, 50, stdin);
        cadena[strcspn(cadena, "\n")] = '\0';
    }
    
    return cadena;
}

/**
 * @brief 
 * 
 */
void pausarPantalla(){
    int c;
    printf("Presiona Enter para continuar...");
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief 
 * 
 */
void limpiarConsola(){
    #ifdef _WIN32
        // Código para Windows
        system("cls");
    #else
        // Código para UNIX (Linux/macOS)
        system("clear");
    #endif
}