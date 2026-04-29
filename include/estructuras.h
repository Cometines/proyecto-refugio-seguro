#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include<stdbool.h>

typedef struct {
    int id_insumo;
    char nombre[50];
    int cantidad_disponible;
}Insumo;


typedef enum{
    ATENCION_BASICA=1,   // Va directo a la fila de insumos
    ATENCION_MEDICA=2,   // FilaMedica -> FilaInsumos
    ATENCION_ESPECIAL=3, // Va directo a la fila de insumos, anota requerimiento especial
    ATENCION_COMPLETA=4  // FilaMedica -> FilaInsumos, anota requerimiento especial
}NivelAtencion;

typedef struct Familia{
    char folio[16]; 
    char nombre_representante[50];
    int edad_representante; // Si <18, entonces no se puede registrar como representante
    int cantidad_integrantes;

    NivelAtencion nivel_asignado; // Almacena el nivel de atención asignado a la familia

    // Solo se usan cuando el nivel asignado es 3 o 4
    char requerimiento_especial[100]; //Si el nivel asignado es 1 o 2, = "Sin requerimientos especiales"
    bool requerimiento_especial_atendido; //True = Atendida , False = Pendiente

    struct Familia* siguiente;
}Familia;

//Nodo de genérico que sirve para cualquiera de las colas
typedef struct NodoCola{
    Familia datos_familia; //Apunta a la familia directamente en la lista
    struct NodoCola* siguiente;
}NodoCola;

//Estructura de las colas
//En el main.c se instanciarán: ColaAtencion cola_medica; y ColaAtencion cola_insumos;
typedef struct{
    NodoCola* frente;
    NodoCola* fondo;
}ColaAtencion;

typedef enum{
    REGISTRO_FAMILIA = 1,
    ENTREGA_APOYO = 2
}TipoOperacion;

typedef union Estructuras{
    struct familia{
        int folio_involucrado;
    };

    struct inventario{
        int id_insumo_involucrado;
        int cantidad_involucrado;
    };

}Estructuras;

typedef struct Operacion{
    TipoOperacion tipo;
    char descripcion[100];
    Estructuras estructuras;

    struct Operacion* siguiente;
}Operacion;
#endif