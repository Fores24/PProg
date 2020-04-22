/** @brief Implementacion del modulo encargado de
*   cargar los espacios
*
* @file GameReader.c
* @author Saul Almazan y Alvaro Becerra Jimenez
* @version 1.0*/

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"
STATUS game_create_from_file(Game* game, char* filename);
STATUS game_load_spaces(Game* game, char* filename);


#endif
