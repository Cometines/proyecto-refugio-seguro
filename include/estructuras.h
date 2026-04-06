#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H


// ======================
// INVENTARIO
// ======================
typedef struct {
    int id_insumo;
    char nombre[50];
    int cantidad_disponible;
}Insumo;

typedef struct Familia{
    int folio;
    char nombre_representante[50];
    int cantidad_integrantes;
    char necesidades[100];

    struct Familia* siguiente;
}Familia;

typedef struct NodoCola{
    int folio_familia;
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