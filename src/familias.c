#include "../include/familias.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
static int count=0;

void registrarFamilia(Familia** cabeza_lista){
    count++;
    int aleatorio = (rand() % 900) + 100;
    struct Familia * familiaNueva;
    familiaNueva = (struct Familia*) malloc (sizeof(struct Familia)); //Se reserva memoria en la variable creada 
    printf("Ingrese el nombre del representante de la familia(Debe de ser mayor de edad)\n");
    scanf("%s", familiaNueva->nombre_representante);
    printf("Ingrese la cantidad de integrantes de la familia)\n");
    scanf("%d",& familiaNueva->cantidad_integrantes);
    printf("Ingrese las necesidades de la familia\n");
    scanf("%s", familiaNueva->necesidades);
    snprintf(familiaNueva->folio,12,"%s-%03d-%d", "FAM", count,aleatorio);

    familiaNueva ->siguiente= *cabeza_lista;
    *cabeza_lista = familiaNueva;
} 