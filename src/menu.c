/**
 * @file menu.c
 * @author Kelaia Reyes Torres
 * @brief Funciones necesarias para la UI
 * @version 0.1
 * @date 2026-04-11
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//Libreria faltante
#include "../include/menu.h"

void mostrarMenu() {
    printf("\n=========================================\n");
    printf("       REFUGIO SEGURO - SOCONUSCO        \n");
    printf("=========================================\n");
    printf("1. Gestionar Familias (Registro y Censo)\n");
    printf("2. Atender familia (Entregar apoyos / Medico)\n");
    printf("3. Ver reportes (Inventario y Ocupacion)\n");
    printf("4. Ver historial de operaciones\n");
    printf("5. Deshacer ultima accion (Ctrl+Z)\n");
    printf("6. Guardar y Salir\n");
    printf("=========================================\n");
}

/**
 * @brief  Función que valida y devuelve una cantidad entera.
 * 
 * @param mensaje Char constante que recibirá una cadena con la instrucción para el usuario de lo que debe introducir.
 * @return int Retorna lo escrito una vez validado como correcto
 */
int pedirEntero(const char* mensaje){
    int digito = 0, n = 0;
    printf("%s", mensaje);
    do {
        n = scanf("%d", &digito);
        
        // LIMPIEZA DE BUFFER: Destruye el 'Enter' sobrante siempre
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (n != 1) {
            printf("Por favor, ingresa un valor numerico valido: ");
        }
    } while (n != 1);
    return digito;
}

/**
 * @brief Función que valida y devuelve el texto que se solicita.
 * 
 * @param mensaje Char constante que recibirá una cadena con la instrucción para el usuario de lo que debe introducir.
 * @return char* Retorna lo escrito una vez validado como correcto
 */
char* pedirCadena(const char* mensaje){
    char* cadena = malloc(50 * sizeof(char));///* @warning Posible correción del tamaño debido al tamaño de "descripción"

    if (cadena == NULL){//No es 100% seguro que el programa asigne memoria por eso este bloque de código
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
 * @brief Función que simulará una pausa del programa en tiempo de ejecución
 */
void pausarPantalla(){
    int c;
    printf("Presiona Enter para continuar...");
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Función que se encarga de detectar el sistema operativo y usar la instrucción correspondiente para limpiar la consola
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
