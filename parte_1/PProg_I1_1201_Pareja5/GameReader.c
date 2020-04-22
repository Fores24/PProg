
/* ===================================================================
File: GameReader.c
Version: 1.0
Date: 1-10-2018
Autores: Saul Almazan y Alvaro Becerra Jiminez
Description: Módulo que permite cargar los espacios de un archivo a un juego
Revision historica: 
1-10-2018 versión 1.0

=================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GameReader.h"

/******************************************************************
 *Funcion :game_reader_load_spaces
 *Date: 1-10-2018
 *Autor: Saul Almazan
 *Description: Funcion que se encarga de leer los espacios y cargarlos
 *Input: Game y el nombre del fichero donde esta el tablero
 *Output: OK si todo funciona bien y ERROR si hay algun fallo.
 ********************************************************************/

STATUS game_reader_load_spaces(Game* game, char* filename) {
    FILE* file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char* toks = NULL;
    Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
    Space* space = NULL;
    STATUS status = OK;
    if (!filename) {
        return ERROR;
    }

    file = fopen(filename, "r");
    if (file == NULL) {
        return ERROR;
    }

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#s:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            north = atol(toks);
            toks = strtok(NULL, "|");
            east = atol(toks);
            toks = strtok(NULL, "|");
            south = atol(toks);
            toks = strtok(NULL, "|");
            west = atol(toks);
#ifdef DEBUG
            printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
            space = space_create(id);
            if (space != NULL) {
                space_set_name(space, name);
                space_set_north(space, north);
                space_set_east(space, east);
                space_set_south(space, south);
                space_set_west(space, west);
                game_add_space(game, space);
            }
        }
    }

    if (ferror(file)) {
        status = ERROR;
    }

    fclose(file);

    return status;
}