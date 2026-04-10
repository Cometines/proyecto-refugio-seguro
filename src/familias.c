/**
 * @file familias.c
 * @author Feliciano Gonzalez Ervin Antonio
 * @brief Archivo .c que busca implementar todas las funcionalidades del alta de familias
 * @version 0.1
 * @date 2026-04-08
 */


#include "../include/familias.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/**
 * @var count
 * @brief Contador estático que rastrea el número total de familias registradas.
 * Se utiliza para la generación incremental de folios (ej. FAM-001, FAM-002).
 */
static int count=0;

/**
 * @brief Función de apoyo que verifica si un campo de edad es mayor de edad.
 * @param edad Valor entero que representa los años de la persona a validar.
 * @return True si la edad recibida en el parametro es mayor de edad y false en el caso contrario.
 */
static bool mayorEdad(int edad){
    if(edad>=18)

        return true;
    return false;    
}

/**
 * @brief Función de apoyo que valida que el representante sea apto(mayor de edad).
 * @param nombre_direccion[out] Puntero que contiene la direccion de memoria en donde se va a guardar
 * el nombre del representante despues de la validación.
 * @param edad_direccion[out] Puntero que contiene la direccion de memoria en donde se va a guardar
 * la edad del representante despues de la validación.
 */
static void validarDatosRepresentante(char *nombre_direccion, int *edad_direccion){
    bool flag=false;
    char nombre_temporal[50];
    int edad_temporal;
    do{
        printf("Ingrese el nombre del representante de la familia\n");
        scanf("%s", nombre_temporal);
        printf("Ingrese la edad del representante\n");
        scanf("%d", & edad_temporal);
        if ( ( flag=mayorEdad(edad_temporal) ) == false ){
            printf("La edad del representante no es la adecuada, por lo que ingrese a una persona apta para el registro\n");
        }
    }while(flag != true);
    *edad_direccion = edad_temporal;
    strcpy(nombre_direccion, nombre_temporal);
}

/**
 * @brief Función que hace el alta de las familias en la lista.
 * @param cabeza_lista Doble puntero a la estructura Familia. 
 * Se pasa por referencia (puntero a puntero) para permitir que la función 
 * modifique la dirección de memoria de la cabeza original de la lista, 
 * permitiendo la inserción de nuevos nodos.
 */
void registrarFamilia(Familia** cabeza_lista){
    //validación de los datos del representante.
    char nombre_valido[50];
    int edad_valida=0;
    validarDatosRepresentante(nombre_valido,&edad_valida);

    //reservación de memoria.
    struct Familia * familia_nueva;
    familia_nueva = (struct Familia*) malloc (sizeof(struct Familia));
    
    //verificación de que exista la memoria reservada para el registro y asi evitar un error.
    if(familia_nueva == NULL){
        printf("Error fatal, no fue posible el registro de la familia por espacio insuficiente en la memoria\n");
        return;
    } 

    //Registro de la familia y sus campos.
    count++;
    strcpy(familia_nueva->nombre_representante,nombre_valido);
    familia_nueva->edad = edad_valida;
    printf("Ingrese la cantidad de integrantes de la familia)\n");
    scanf("%d",& familia_nueva->cantidad_integrantes);
    printf("Ingrese las necesidades de la familia\n");
    scanf("%s", familia_nueva->necesidad_especial);

    //generación y asignación del folio.
    int aleatorio = (rand() % 900) + 100;
    snprintf(familia_nueva->folio,12,"%s-%03d-%d", "FAM", count,aleatorio);

    //inserción en la lista
    familia_nueva ->siguiente= *cabeza_lista;
    *cabeza_lista = familia_nueva;
} 

/**
 * @brief Funcion que permite imprimir la lista de las familias.
 * @param cabeza_lista Puntero de la estructura Familia.
 * Se pasa como puntero, para que la funcion pueda tener acceso a la lista y asi poder imprimirla.
 */
void mostrarFamiliasRegistradas(Familia* cabeza_lista){
    struct Familia *aux= cabeza_lista;
    if(aux == NULL){
        printf("Aun no existen familias registradas\n");
        return;
    }
    printf("%-50s %-20s %-5s %-15s \n","NOMBRE DEL REPRESENTANTE","EDAD DEL REPRESENTANTE","CANT. DE INTEGRANTES", "NOM. DE FOLIO");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    
    while(aux != NULL){
        printf("%-50s %-20d %-5d %-15s",aux->nombre_representante,aux->edad,aux->cantidad_integrantes,aux->folio);
        printf("\n");
        aux = aux ->siguiente;
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
} 


