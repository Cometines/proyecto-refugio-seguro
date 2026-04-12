#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include<stdbool.h>


typedef struct {
    int id_insumo;
    char nombre[50];
    int cantidad_disponible;
}Insumo;


typedef enum{
    ATENCION_BASICA=1,   // Solo se le encola para recibir insumos
    ATENCION_MEDICA=2,   // Se encola para atención médica, después para recibir insumos
    ATENCION_ESPECIAL=3, // 
    ATENCION_COMPLETA=4
}NivelAtencion;

typedef struct Familia{
    char folio[16];
    char nombre_representante[50];
    int edad;
    int cantidad_integrantes;
    char necesidad_especial[100];
    bool requiere_atencion_medica;

    struct Familia* siguiente;
}Familia;

typedef struct NodoCola{
    char folio_familia[16];
    struct NodoCola* siguiente;
}ColaAtencion;

typedef enum{
    REGISTRO_FAMILIA = 1,
    ENTREGA_APOYO = 2
}TipoOperacion;

typedef struct Operacion{
    TipoOperacion tipo;
    char descripcion[100];

    int folio_involucrado;
    int id_insumo_involucrado;
    int cantidad_involucrada;

    struct Operacion* siguiente;
}Operacion;


#endif