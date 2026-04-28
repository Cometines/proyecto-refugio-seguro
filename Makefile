# Variables del compilador
CC = gcc
CFLAGS = -Wall -Wextra -I./include

# Carpetas
SRC_DIR = src
BIN_DIR = bin

# Archivos fuente y el nombre del ejecutable final
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/menu.c $(SRC_DIR)/familias.c $(SRC_DIR)/inventario.c $(SRC_DIR)/atencion.c $(SRC_DIR)/historial.c
EXEC = $(BIN_DIR)/refugio

# Regla principal: compilar todo
all: $(EXEC)

# Cómo construir el ejecutable
$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)

# Regla para limpiar los archivos compilados (útil para reiniciar)
clean:
	rm -f $(BIN_DIR)/*