/**
 * @file familias.c
 * @author Feliciano Gonzalez Ervin Antonio
 * @brief Archivo .c que busca implementar todas las funcionalidades del alta de familias
 * @version 0.1
 * @date 2026-04-08
 */

#include "../include/menu.h"
#include "../include/familias.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Funcion de apoyo recibe una cadena y la convierte toda a mayusculas.
 * @param cadena es la dirección de memoria de la cadena a hacer mayuscula
 */
static void convertirAMayusculas(char *cadena){
    for(int i=0; cadena[i]; i++){
        cadena[i] = toupper(cadena[i]);
    }
}

/**
 * @brief funcion de apoyo que corrobora si la lista esta vacia
 * 
 * @param cabeza_lista puntero hacia la cabeza de lista
 * @return true valor retornado si la lista esta vacia
 * @return false valor retornado si la lista no esta vacia
 */
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
    char *nombre_temporal;
    int edad_temporal;
    do{
        nombre_temporal = pedirCadena("Ingrese el nombre del representante de la familia");
        edad_temporal = pedirEntero("Ingrese la edad del representante: ");
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
static void nivelAtencionFamilia(NivelAtencion *nivel_asignado,char *requerimiento_especial, bool *requerimiento_especial_atentido){
    do
    {
        printf("Por favor seleccione el tipo de atencion que requiere la familia\n");
        printf("Nota : Por defecto todas las familias seran referidas a la zona de insumos\n");
        printf("1. Atencion basica(Solo necesita insumos).\n");
        printf("2. Atención medica\n");
        printf("3.Atencion especial \n");
        printf("4.Atencion completa\n");
        nivel_asignado = pedirEntero ("");
        //Arranca los valores con valores iniciales para evitar problemas con valores basura en la ram
        strcpy(requerimiento_especial,"Vacio");
        *requerimiento_especial_atentido = false;

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
                requerimiento_especial = pedirCadena("Ingrese su requerimiento especial:");
                break;
            case ATENCION_COMPLETA:
                printf("Seleccionaste: Completa\n");
                requerimiento_especial = pedirCadena("Ingrese su requerimiento especial:");
                break;
            default:
                printf("Opcion no valida, intenta de nuevo.\n");
                break;

        }
    } while (*nivel_asignado < 1 || *nivel_asignado > 4);
    
}

static void confirmarOperacion(const char *prefijo_operacion,Familia *Operacion){
    bool flag=false;
    int op;
    do{
        printf("%s\n",prefijo_operacion);
        printf("1. Confirmar operación\n");
        printf("2. Cancelar la operación\n");
        op = pedirEntero("Ingrese su opción: \n");
        switch (op)
        {
        case 1:
            printf("La operación ha sido confirmada\n");
            flag=true;
            break;
        case 2:
            printf("La operación ha sido cancelada exitosamente\n");
            free(Operacion);
            flag=true;
            break;
        default: printf("Opción no valida\n");
            break;
        }
    }while (flag!=true);

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
    familia_nueva = (struct Familia*) calloc (1,sizeof(struct Familia));
    
    //verificación de que exista la memoria reservada para el registro y asi evitar un error.
    if(familia_nueva == NULL){
        printf("Error fatal, no fue posible el registro de la familia por espacio insuficiente en la memoria\n");
        return;
    } 

    //Registro de la familia y sus campos.
    strcpy(familia_nueva->nombre_representante,nombre_valido);
    familia_nueva->edad_representante = edad_valida;
    familia_nueva->cantidad_integrantes = pedirEntero ("Ingrese la cantidad de integrantes de la familia");

    nivelAtencionFamilia(&familia_nueva->nivel_asignado,familia_nueva->requerimiento_especial, &familia_nueva->requerimiento_especial_atendido);

    //generación y asignación del folio.
    generarFolio("FAM",familia_nueva->folio);

    confirmarOperacion("¿Desea confirmar el registro de la familia?",familia_nueva);
    //inserción en la lista
    familia_nueva ->siguiente= *cabeza_lista;
    *cabeza_lista = familia_nueva;
} 

/**
 * @brief Función que imprimi a una familia con el formato de tabla
 * 
 * @param familia es la dirección de memoria de la familia a imprimir
 */
static void imprimirFichaFamiliar(Familia* familia){
    printf("%-15s %-30s %-8d %-15d ", familia->folio, familia->nombre_representante, familia->edad_representante, familia->cantidad_integrantes);
        switch (familia->nivel_asignado)
        {
            case ATENCION_BASICA:   printf("%-15s\n", "Basica"); break;
            case ATENCION_MEDICA:   printf("%-15s\n", "Medica"); break;
            case ATENCION_ESPECIAL: printf("%-15s\n", "Especial"); break;
            case ATENCION_COMPLETA: printf("%-15s\n", "Completa"); break;
            default:                printf("%-15s\n", "No asignado"); break;
        }
        if (familia->nivel_asignado > ATENCION_MEDICA){
            printf(" -> REQUERIMIENTO: %-50s | ESTADO: %s\n", familia->requerimiento_especial,familia->requerimiento_especial_atendido ? "Atendido" : "Pendiente");
        }
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
        imprimirFichaFamiliar(aux);
        aux = aux ->siguiente;
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
} 

/**
 * @brief Función que busca a una familia mediante un folio 
 * 
 * @param cabeza_lista es el puntero a la cabeza de la lista , y se usa para tener acceso a lista
 * @param folio Es el folio de la familia a buscar
 * @return Familia* devuelve la dirección de memoria del nodo de la familia encontrada 
 * @return NULL valor devolvido si no se encuentra a la familia
 */
Familia* buscarFamiliaPorFolio(Familia* cabeza_lista, char *folio){
    Familia *aux = cabeza_lista;
    if(listaVacia(aux)){
        printf("La lista de familias esta vacia por lo que no se puede realizar una busqueda\n");
        return NULL;
    }
    convertirAMayusculas(folio);
    while(aux != NULL){
        if(strcmp(aux->folio, folio) == 0){
            printf("La familia con folio %s ha sido encontrada exitosamente\n", folio);
            return aux;
        }
        aux = aux->siguiente;
    }
    printf("La familia con folio %s no ha sido encontrada en la lista\n", folio);
    return NULL;
    
}

/**
 * 
 * @brief Función encargada de gestionar los métodos del módulo del alta de familias.
 * Despliega un menú interactivo para realizar altas, búsquedas y visualización de registros.
 * 
 * @param[in,out] puntero_lista_main Doble puntero hacia la lista que se encuentra en el main.
 * Es fundamental para que las modificaciones (como el alta de una familia) persistan 
 * en la estructura original del programa.
 */
void menuFamilias (Familia** puntero_lista_main){
    Familia *aux;
    int op;
    char *folio;
    do
    {
        printf("Bienvenido al area del manejo de las familias\n");
        printf("1. Alta de una familia\n");
        printf("2. Buscar Familia(mediante folio)\n");
        printf("3. Imprimir Familias\n");
        printf("4. Salir del area de familias\n");
        op = pedirEntero("Ingrese la operacion a realizar: \n");

        switch (op)
        {
        case 1:
            registrarFamilia(puntero_lista_main);
            break;

        case 2:
            folio = pedirCadena("Ingrese el folio de la familia que desea buscar: ");
            if(folio != NULL) {
                aux = buscarFamiliaPorFolio(*puntero_lista_main,folio);
                if(aux != NULL){
                    printf("La familia con folio %s ha sido encontrada exitosamente\n", folio);
                    imprimirFichaFamiliar(aux);
                }else {
                    printf("La familia con folio %s no ha sido encontrada en la lista\n",folio);
                }
                free(folio);
            } 
            break;

        case 3: 
            mostrarFamiliasRegistradas(*puntero_lista_main);
            break;

        case 4: 
            printf("Regresando al menu principal..\n");
            break;

        default: printf("[!] Opcion no valida (1-4).\n");
            break;
        }
        
        if(op == 4)
            pausarPantalla();
    } while (op!=4);
    
}


