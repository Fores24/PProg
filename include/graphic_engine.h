/**
 * @brief En este fichero estaran las funciones relacionadas con la interfaz gráfica
 * @file graphic_engine.h
 * @author Manuel Suarez, Saul Almazán, Álvaro Becerra, Rodrigo Lardiés
 * @version 2.0
 * @date 8/11/2018
 */


#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__


#include "space.h"
#include "player.h"
#include "game.h"
#include "screen.h"
#define TAM_CASILLA 34/*!<Número de espacios en blanco en una casilla entre las dos |*/
#define TAM_TOTAL_CASILLA 42 /*!<Caracteres máximos de una casilla*/


typedef struct _Graphic_engine Graphic_engine; /*!< Estructura de la interfaz grafica */


/**
 * @brief crea una interfaz grafica
 * @author Manuel Suarez, Saul Almazán, Álvaro Becerra, Rodrigo Lardiés
 * @date 8/11/2018
 * @return Graphic_engine (la interfaz que hemos creado)
 */
Graphic_engine* graphic_engine_create();

/**
 * @brief destruye una interfaz grafica
 * @author Manuel Suarez, Saul Almazán, Álvaro Becerra, Rodrigo Lardiés
 * @date 8/11/2018
 * @param ge (la interfaz que se va a destruir)
 * @return void (no devuelve nada)
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief hace la interfaz grafica del juego
 * @author Manuel Suarez, Saul Almazán, Álvaro Becerra, Rodrigo Lardiés
 * @date 8/11/2018
 * @param ge (la interfaz que se va a usar)
 * @param game (El juego que se va a usar)
 * @return void (no devuelve nada)
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);


#endif
