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

static void convertirAMayusculas(char *cadena){
    for(int i=0; cadena[i]; i++){
        cadena[i] = toupper(cadena[i]);
    }
}

static bool listaVacia(Familia *cabeza_lista){
    Familia *aux = cabeza_lista;
    if(aux == NULL)
        return true;
    return false;
}

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
 * @brief Funcion para generar un folio en base a un prefijo asignado.
 * @param prefijo_folio Prefijo que determina el tipo de folio (ejem. FAM, MED, AUX).
 * @note el prefijo pasado como parametro no debe de ser mayor a 7 caracteres,
 * ya que en la estructura el folio es de tamaño 16, por lo que deben ser prefijos
 * cortos y conciso, para evitar un error de desbordamiento.
 * @param destino_folio Puntero que determina el destino del folio generado.
 * 
 */
static void generarFolio(const char *prefijo_folio,char *destino_folio){
    if (strlen(prefijo_folio)>7) {
        printf("Debug: El prefijo '%s' es muy largo. Se truncará.\n", prefijo_folio);
    }
    static int count=1; // Contador estático que rastrea el número total de familias registradas.
    int aleatorio;
    aleatorio = (rand() % 900) + 100;
    snprintf(destino_folio,16,"%s-%03d-%d", prefijo_folio, count,aleatorio);
    count++;
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
 * @brief Gestiona la asignación del nivel de atención y requerimientos especiales de una familia.
 * Esta función despliega un menú interactivo que permite al usuario seleccionar entre cuatro 
 * niveles de atención. Si el nivel seleccionado es 'Atención Especial' (3) o 'Atención Completa' (4), 
 * solicita información adicional sobre la necesidad específica y marca el estado como pendiente.
 * Utiliza un bucle do-while para garantizar que la selección del nivel sea válida (rango 1-4).
 * @param nivel_asignado Puntero al entero (o enum) donde se almacenará el nivel seleccionado por el usuario.
 * @param requerimiento_especial Puntero a la cadena de caracteres donde se guardará la descripción de la necesidad (solo niveles 3 y 4).
 * @param requerimiento_especial_atentido Puntero al valor booleano que se inicializa en 'false' si existe un requerimiento especial.
 * * @note El uso de punteros permite que los cambios realizados dentro de la función se reflejen directamente en la estructura original de la familia.
 */
static void nivelAtencionFamilia(int *nivel_asignado,char *requerimiento_especial, bool *requerimiento_especial_atentido){
    do
    {
        printf("Por favor seleccione el tipo de atencion que requiere la familia\n");
        printf("Nota : Por defecto todas las familias seran referidas a la zona de insumos\n");
        printf("1. Atencion basica(Solo necesita insumos).\n");
        printf("2. Atención medica\n");
        printf("3.Atencion especial \n");
        printf("4.Atencion completa\n");
        scanf("%d", nivel_asignado);
        switch (*nivel_asignado)
        {
            case ATENCION_BASICA:
                printf("Seleccionaste: Basica\n");
                break;
            case ATENCION_MEDICA:
                printf("Seleccionaste: Medica\n");
                break;
            case ATENCION_ESPECIAL:
                printf("Seleccionaste: Especial\n");
                printf("Ingrese su requerimiento especial: \n");
                scanf("%s",requerimiento_especial);
                *requerimiento_especial_atentido = false;
                break;
            case ATENCION_COMPLETA:
                printf("Seleccionaste: Completa\n");
                printf("Ingrese su requerimiento especial: \n");
                scanf("%s",requerimiento_especial);
                *requerimiento_especial_atentido = false;
                break;
            default:
                printf("Opcion no valida, intenta de nuevo.\n");
                break;

        }
    } while (*nivel_asignado < 1 || *nivel_asignado > 4);
    
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
    strcpy(familia_nueva->nombre_representante,nombre_valido);
    familia_nueva->edad_representante = edad_valida;
    printf("Ingrese la cantidad de integrantes de la familia)\n");
    scanf("%d",& familia_nueva->cantidad_integrantes);


    nivelAtencionFamilia(&familia_nueva->nivel_asignado,familia_nueva->requerimiento_especial, &familia_nueva->requerimiento_especial_atendido);

    //generación y asignación del folio.
    generarFolio("FAM",familia_nueva->folio);

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
    printf("\n%-15s %-30s %-8s %-15s %-15s\n", "FOLIO", "REPRESENTANTE", "EDAD", "INTEGRANTES", "NIVEL");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    
    while(aux != NULL){
        printf("%-15s %-30s %-8d %-15d ", aux->folio, aux->nombre_representante, aux->edad_representante, aux->cantidad_integrantes);
        switch (aux->nivel_asignado)
        {
            case ATENCION_BASICA:   printf("%-15s\n", "Basica"); break;
            case ATENCION_MEDICA:   printf("%-15s\n", "Medica"); break;
            case ATENCION_ESPECIAL: printf("%-15s\n", "Especial"); break;
            case ATENCION_COMPLETA: printf("%-15s\n", "Completa"); break;
            default:                printf("%-15s\n", "No asignado"); break;
        }
        if (aux->nivel_asignado > ATENCION_MEDICA){
            printf(" -> REQUERIMIENTO: %-50s | ESTADO: %s\n", aux->requerimiento_especial,aux->requerimiento_especial_atendido ? "Atendido" : "Pendiente");
        }
        aux = aux ->siguiente;
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
} 

Familia* buscarFamiliaPorFolio(Familia* cabeza_lista, char *folio){
    Familia *aux = cabeza_lista;
    if(listaVacia(aux)){
        printf("La lista de familias esta vacia por lo que no se puede realizar una busqueda\n");
        return;
    }
    convertirAMayusculas(folio);
    while(aux != NULL){
        if(strcmp(aux->folio, folio) == 0){
            printf("La familia con folio %s ha sido encontrada exitosamente\n");
            return aux;
        }
        aux = aux->siguiente;
    }
    printf("La familia con folio %s no ha sido encontrada en la lista\n");
    return NULL;
    
}

