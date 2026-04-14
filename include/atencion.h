#ifndef ATENCION_H // if not defined
#define ATENCION_H

#include "estructuras.h"
#include <stdbool.h>

// ===================================
// FUNCIONES PRIMORDIALES PARA COLA
// ===================================

// Para inicializar los punteros de la cola (frente y fondo)=null;
void inicializarCola(ColaAtencion *cola_objetivo);

// Recibe a que cola se van a mandar, recibe la familia que se va a encolar
void encolarFamilia(ColaAtencion *cola_objetivo, Familia *familia_a_encolar);

// Saca y devuelve al primer elemento en la cola especificada.
Familia* desencolarFamilia(ColaAtencion *cola_objetivo);

// Retornar true si está vacía, si no: retornar false
bool colaVacia(ColaAtencion *cola_objetivo);

// ===================================
// LÓGICA DEL NEGOCIO
// ===================================

// Función encargada de determinar a que cola se manda a la familia segun el atributo: NivelAtencion
void enrutarFamilia(ColaAtencion* cola_medica, ColaAtencion* cola_insumos, Familia* nueva_familia);

// Atiende a la familia del frente, se guarda la operación y se encola en la cola de insumos
void atenderColaMedica(ColaAtencion* cola_medica, ColaAtencion* cola_insumos, Operacion** tope_historial);

// Atiende a la familia del frente, se guarda la operación y se resta en el stock del inventario
void atenderColaInsumos(ColaAtencion* cola_insumos);

// Buscar a la familia con requerimiento especial y atenderlo (marcar como true el campo)
void entregarRequerimientoEspecial(Familia* familia_objetivo,Operacion** tope_historial);

// Imprimir un reporte visual de las familias que están esperando
void mostrarEstadoColas(ColaAtencion* cola_medica, ColaAtencion* cola_insumos);

#endif