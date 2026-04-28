/**
 * @file archivos.c
 * @author Leonardo Méndez Lagunes
 * @brief Implementación de la persistencia de datos en archivos .csv usando delimitador pipe: |
 * @version 0.1
 * @date 2026-04-27
 * 
 */

#include "../include/archivos.h"
#include "../include/estructuras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void guardarDatosArchivo(Familia** cabeza_lista, Insumo inventario[], ColaAtencion* cola_medica, ColaAtencion* cola_insumos){

    // 1. Guardar todos los registros de familias en el archivo
    FILE* file_familias=fopen("data/registro_familias.csv","w");
    if(file_familias==NULL){
        fprintf(stderr, "Error: No se pudo crear el archivo");
    } else{
        Familia* aux=*cabeza_lista;
        while(aux!=NULL){
            fprintf(file_familias, "%s|%s|%d|%d|%d|%s|%d\n",
                    aux->folio,
                    aux->nombre_representante,
                    aux->edad_representante,
                    aux->cantidad_integrantes,
                    (int)aux->nivel_asignado,
                    aux->requerimiento_especial,
                    aux->requerimiento_especial_atendido ? 1 : 0);
                aux=aux->siguiente;
        }
        fclose(file_familias);
        printf("Guardado hecho con exito. \n");
    }

    // 2. 
}

void cargarDatosArchivo(Familia** cabeza_lista, Insumo inventario[], ColaAtencion* cola_medica, ColaAtencion* cola_insumos){
    char linea[256];
    char* token;

    // 1. Cargar datos del archivo de los registros al programa
    FILE* file_familias=fopen("data/registro_familias.csv","r");
    if(file_familias!=NULL){
        while(fgets(linea,256,file_familias)!=NULL){
            Familia* nueva_familia=(Familia*)malloc(sizeof(Familia));
            if(nueva_familia==NULL) continue;

            token=strtok(linea,"|");

            if(token) strcpy(nueva_familia->folio,token);
            token=strtok(NULL,"|");
            if(token) strcpy(nueva_familia->nombre_representante,token);
            token=strtok(NULL,"|");
            if(token) nueva_familia->edad_representante=atoi(token);
            token=strtok(NULL,"|");
            if(token) nueva_familia->cantidad_integrantes=atoi(token);
            token=strtok(NULL,"|");
            if(token) nueva_familia->nivel_asignado=(NivelAtencion)atoi(token);
            token=strtok(NULL,"|");
            if(token) strcpy(nueva_familia->requerimiento_especial,token);
            token=strtok(NULL,"|");
            if(token) nueva_familia->requerimiento_especial_atendido=(atoi(token)==1)?true:false;

            // Inserción al frente de la lista
            nueva_familia->siguiente=*cabeza_lista;
            *cabeza_lista=nueva_familia;
        }
        fclose(file_familias);
        printf("Cargado hecho con exito. \n");
    }
}