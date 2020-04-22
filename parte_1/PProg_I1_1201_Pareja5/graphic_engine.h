

/* ===================================================================
File: graphic_engine.h
Version: 1.0
Date: 18-01-2017
Autores: Profesores PPROG
Description: Prototipos de las funciones de la máquina gráfica
Revision historica: 
13-01-2015 versión 1.0 (código inicial)
=================================================================== */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__


#include "space.h"
#include "player.h"
#include "game.h"
#include "screen.h"


typedef struct _Graphic_engine Graphic_engine;

Graphic_engine* graphic_engine_create();
void graphic_engine_destroy(Graphic_engine *ge);
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);
void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif
