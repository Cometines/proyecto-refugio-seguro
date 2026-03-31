#ifndef MENU_H
#define MENU_H

// ================================
// FUNCIONES DEL MENÚ (UI) | Kelaia
// ================================

// Muestra el diseño visual del menú principal
void mostrarMenu();

// Pide un número al usuario y evita que el programa colapse si meten letras
int pedirEntero(const char* mensaje);

// Pausa el sistema hasta que el usuario presione Enter (útil para leer reportes)
void pausarPantalla();

#endif // UI_H