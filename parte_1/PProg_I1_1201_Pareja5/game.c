
/* ===================================================================
File: game.c
Version: 2.0
Date: 1-10-2018
Autores: Saul Almazan y Alvaro Becerra Jiminez
Description: Contiene todas las funciones que perimiten crear un juego y actualizarlo
Revision historica: 
13-01-2015 versión 1.0 (código inicial)
1-10-2018 versión 2.0 
       Añadidas funciones para coger y soltar objetos y avanzar y retroceder de oca a oca. Además, se han
       modificado las funciones relativas a objetos y jugadores.

=================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "GameReader.h"

#define N_CALLBACK 8

/**Define the function type for the callbacks**/
typedef void (*callback_fn)(Game* game);

/**List of callbacks for each command in the game**/
void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_following(Game* game);
void game_callback_previous(Game* game);
void game_callback_oca_following(Game* game);
void game_callback_oca_previous(Game* game);
void game_callback_take_object(Game* game);
void game_callback_leave_object(Game* game);

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_following,
    game_callback_previous,
    game_callback_oca_following,
    game_callback_oca_previous,
    game_callback_take_object,
    game_callback_leave_object
};

/**Private functions*/

STATUS game_load_spaces(Game* game, char* filename);
Id game_get_space_id_at(Game* game, int position);
STATUS game_set_object_location(Game* game, Id id, Id id_object);


/**Game interface implementation*/

/******************************************************************
 *Funcion :game_create
 *Date: 1-10-2018
 *Autores: Saul Almazan y Alvaro Becerra Jiminez
 *Description: Función que se encarga de crear el juego
 *Input: Game y el nombre del jugador
 *Output: OK si todo funciona bien y ERROR si hay algún fallo.
 ********************************************************************/

STATUS game_create(Game* game, char * name_player) {
    int i;

    for (i = 0; i < MAX_SPACES; i++) {
        game->spaces[i] = NULL;
    }

    game->player = player_create();
    if (game->player == NULL) return ERROR;
    if (player_set_id(game->player, 1) == ERROR) return ERROR; /*En esta primera iteración, suponemos que hay un solo jugador*/
    if (player_set_name(game->player, name_player) == ERROR) return ERROR;
    game->object[0] = object_create(); /*Los objetos, en posteriores itereciones, serán cargados a partir de un fichero de texto.
										Sin embargo, para probar la funcionalidad, incluiremos un objeto con id=1 y con nombre
										"Objeto misterioso" y otro con id=2 y nombre "La saga/fuga de J.B.".*/
    if (game->object[0] == NULL) return ERROR;
    if (object_set_id(game->object[0], 1) == ERROR) return ERROR;
    if (object_set_name(game->object[0], "Objeto misterioso") == ERROR) return ERROR;
    game->object[1] = object_create();
    if (game->object[1] == NULL) return ERROR;
    if (object_set_id(game->object[1], 2) == ERROR) return ERROR;
    if (object_set_name(game->object[1], "La saga/fuga de J.B.") == ERROR) return ERROR;
    game->last_cmd = NO_CMD;

    return OK;
}

/******************************************************************
 *Funcion :game_create_from_file
 *Date: 1-10-2018
 *Autores: Saul Almazan y Alvaro Becerra Jiminez
 *Description: Función que crea un juego desde un fichero
 *Input: Game ,el nombre del fichero donde esta el tablero y el nombre del jugador
 *Output: OK si todo funciona bien y ERROR si hay algún fallo.
 ********************************************************************/

STATUS game_create_from_file(Game* game, char* filename, char* name_player) {

    if (game_create(game, name_player) == ERROR)
        return ERROR;

    if (game_load_spaces(game, filename) == ERROR)
        return ERROR;
    if (player_set_space_id(game->player, game_get_space_id_at(game, 0)) == ERROR) {
        return ERROR;
    }

    game_set_object_location(game, game_get_space_id_at(game, 0), object_get_id(game->object[0])); /*Establecemos los objetos en unas casillas
																									arbitrariamente escogidas*/
    game_set_object_location(game, game_get_space_id_at(game, 4), object_get_id(game->object[1]));

    return OK;
}

/******************************************************************
 *Funcion :game_destroy
 *Date: 1-10-2018
 *Autores: Saul Almazan y Alvaro Becerra Jiminez
 *Description: Función que se encarga de liberar la memoria de game
 *Input: Game game que va a ser liberado
 *Output: OK si todo funciona bien
 ********************************************************************/

STATUS game_destroy(Game* game) {
    int i = 0;

    for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
        space_destroy(game->spaces[i]);
    }
    player_destroy(game->player);
    for (i = 0; (i < MAX_OBJECT) && (game->object[i] != NULL); i++) {
        object_destroy(game->object[i]);
    }

    return OK;
}

/******************************************************************
 *Funcion :game_add_space
 *Date: ??
 *Autores: Codigo Inicial
 *Description: Función que se encarga de añadir espacios
 *Input: Game donde se va a introducir el espacio y el espacio a añadir
 *Output: OK si todo funciona bien y ERROR si hay algun fallo.
 ********************************************************************/

STATUS game_add_space(Game* game, Space* space) {
    int i = 0;

    if (space == NULL) {
        return ERROR;
    }

    while ((i < MAX_SPACES) && (game->spaces[i] != NULL)) {
        i++;
    }

    if (i >= MAX_SPACES) {
        return ERROR;
    }

    game->spaces[i] = space;

    return OK;
}

/******************************************************************
 *Funcion :game_get_space_id_at
 *Date: ??
 *Autores: Código Inicial
 *Description: Función que se encarga de obtener el id de un espacio dada una posición
 *Input: Game y la posicion
 *Output: Id o no_id si hay algun fallo
 ********************************************************************/

Id game_get_space_id_at(Game* game, int position) {

    if (position < 0 || position >= MAX_SPACES) {
        return NO_ID;
    }

    return space_get_id(game->spaces[position]);
}

/******************************************************************
 *Funcion :game_get_space
 *Date: ??
 *Autores: Código inicial
 *Description: Función que se encarga buscar un espacio a través de su id
 *Input: Game y el id del espacio
 *Output: space o NULL si no existe tal espacio
 ********************************************************************/

Space* game_get_space(Game* game, Id id) {
    int i = 0;

    if (id == NO_ID) {
        return NULL;
    }

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        if (id == space_get_id(game->spaces[i])) {
            return game->spaces[i];
        }
    }

    return NULL;
}

/******************************************************************
 *Funcion :game_set_object_location
 *Date: 1-10-2018
 *Autores: Saul Almazan y Alvaro Becerra Jiminez
 *Description: Función que se encarga de establecer la localizacion de un objecto
 *Input: Game, id del espacio donde se debe colocar el objeto y id del objeto
 *Output: OK si todo funciona bien y ERROR si hay algun fallo.
 ********************************************************************/

STATUS game_set_object_location(Game* game, Id id, Id id_object) {
    if (id == NO_ID) {
        return ERROR;
    }
    return space_set_object(game->spaces[id - 1], id_object);
}

/******************************************************************
 *Funcion :game_get_player_location
 *Date: 1-10-2018
 *Autores: Saul Almazan y Alvaro Becerra Jiminez
 *Description: Funcion que se encarga de devolver la localizacion del jugador
 *Input: Game
 *Output: Id o NO_ID si no existe jugador
 ********************************************************************/

Id game_get_player_location(Game* game) {
    return player_get_space_id(game->player);
}

/******************************************************************
 *Funcion :game_get_object_location
 *Date: 1-10-2018
 *Autores: Saul Almazan y Alvaro Becerra Jiminez
 *Description: Función que se encarga de devolver el id del espacio donde se encuentra el objecto
 *Input: Game y id del objeto
 *Output: Id o NO_ID si no existe tal objeto
 ********************************************************************/

Id game_get_object_location(Game* game, Id id) {
    Id id_space = NO_ID;
    int i;
    if (id == NO_ID) return NO_ID;
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        if (id == space_get_object(game->spaces[i])) {
            id_space = i + 1;
            break;
        }
    }
    return id_space;
}

/******************************************************************
 *Funcion :game_get_object_name
 *Date: 1-10-2018
 *Autores: Saul Almazan y Alvaro Becerra Jiminez
 *Description: Función que obtiene y devuelve el nombre de un objeto de juego
 *Input: Game y el Id del objeto
 *Output: char * nombre del objeto.
 ********************************************************************/

char *game_get_object_name(Game *game, Id id) {
    return object_get_name(game->object[id - 1]);
}

/******************************************************************
 *Funcion :game_update
 *Date: ??
 *Autores: Código inicial
 *Description: Función que actualiza el juego
 *Input: Game y un comando T_command
 *Output: OK
 ********************************************************************/

STATUS game_update(Game* game, T_Command cmd) {
    game->last_cmd = cmd;
    (*game_callback_fn_list[cmd])(game);
    return OK;
}

/******************************************************************
 *Funcion :game_get_last_command
 *Date: ??
 *Autores: Código inicial
 *Description: Función que devuelve el último comando
 *Input: Game
 *Output: devuelve el ultimo comando del juego
 ********************************************************************/
T_Command game_get_last_command(Game* game) {
    return game->last_cmd;
}

/******************************************************************
 *Funcion :game_print_data
 *Date: 1-10-2018
 *Autores: Saul Almazan y Alvaro Becerra Jiminez
 *Description: Funcion que escribe los datos de un juego. Se ha modificado para que incluya todos los objetos
 *Input: Game
 *Output: no devuelve nada.
 ********************************************************************/

void game_print_data(Game* game) {
    int i = 0;

    printf("\n\n-------------\n\n");

    printf("=> Spaces: \n");
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        space_print(game->spaces[i]);
    }
    for (i = 0; i < MAX_OBJECT && game->object[i] != NULL; i++) {
        printf("=> Object location: %d\n", (int) game_get_object_location(game, object_get_id(game->object[i])));
    }

    printf("=> Player location: %d\n", (int) game_get_player_location(game));
    printf("prompt:> ");
    return;
}

/******************************************************************
 *Funcion :game_is_over
 *Date: ??
 *Autores: Código inicial
 *Description: Funcion que nos indica si el juego ha acabado
 *Input: Game
 *Output: False
 ********************************************************************/

BOOL game_is_over(Game* game) {
    return FALSE;
}

/**Callbacks implementation for each action */

/******************************************************************
 *Funcion:game_callback_unknown
 *Date: ??
 *Autores: Código inicial
 *Description: Funcion que no hace nada porque no se ha entendido el comando
 *Input: Game
 *Output: nada
 ********************************************************************/

void game_callback_unknown(Game* game) {
}

/******************************************************************
 *Funcion:game_callback_exit
 *Date: ??
 *Autores: Código inicial
 *Description: Funcion que no hace nada y es llamada si el jugador quiere salir
 *Input: Game
 *Output: nada
 ********************************************************************/

void game_callback_exit(Game* game) {
}

/******************************************************************
 *Funcion:game_callback_following
 *Date: ??
 *Autores: Código inicial
 *Description: Funcion que permite ir hacia adelante
 *Input: Game
 *Output: nada
 ********************************************************************/

void game_callback_following(Game* game) {
    int i = 0;
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    space_id = game_get_player_location(game);
    if (space_id == NO_ID) {
        return;
    }

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        current_id = space_get_id(game->spaces[i]);
        if (current_id == space_id) {
            current_id = space_get_south(game->spaces[i]);
            if (current_id != NO_ID) {
                player_set_space_id(game->player, current_id);
            }
            return;
        }
    }
}

/******************************************************************
 *Funcion:game_callback_previous
 *Date: ??
 *Autores: Código inicial
 *Description: Funcion que permite ir hacia atrás
 *Input: Game
 *Output: nada
 ********************************************************************/

void game_callback_previous(Game* game) {
    int i = 0;
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    space_id = game_get_player_location(game);

    if (NO_ID == space_id) {
        return;
    }

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        current_id = space_get_id(game->spaces[i]);
        if (current_id == space_id) {
            current_id = space_get_north(game->spaces[i]);
            if (current_id != NO_ID) {
                player_set_space_id(game->player, current_id);
            }
            return;
        }
    }
}

/******************************************************************
 *Funcion:game_callback_oca_following
 *Date: 1-10-2018
 *Autores: Alvaro Becerra Jiminez
 *Description: Funcion que permite ir de oca a oca
 *Input: Game
 *Output: nada
 ********************************************************************/

void game_callback_oca_following(Game* game) {
    int i = 0;
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    space_id = game_get_player_location(game);
    if (space_id == NO_ID) {
        return;
    }

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        current_id = space_get_id(game->spaces[i]);
        if (current_id == space_id) {
            current_id = space_get_east(game->spaces[i]);
            if (current_id != NO_ID) {
                player_set_space_id(game->player, current_id);
            }
            return;
        }
    }
}

/******************************************************************
 *Funcion:game_callback_oca_previous
 *Date: 1-10-2018
 *Autores: Alvaro Becerra Jiminez
 *Description: Funcion que permite ir de oca a oca hacia atrás
 *Input: Game
 *Output: nada
 ********************************************************************/

void game_callback_oca_previous(Game* game) {
    int i = 0;
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    space_id = game_get_player_location(game);
    if (space_id == NO_ID) {
        return;
    }

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        current_id = space_get_id(game->spaces[i]);
        if (current_id == space_id) {
            current_id = space_get_west(game->spaces[i]);
            if (current_id != NO_ID) {
                player_set_space_id(game->player, current_id);
            }
            return;
        }
    }
}

/******************************************************************
 *Funcion:game_callback_take_object
 *Date: 1-10-2018
 *Autores: Alvaro Becerra Jiminez
 *Description: Funcion que permite dejar un objeto
 *Input: Game
 *Output: nada
 ********************************************************************/

void game_callback_take_object(Game* game) {
    Id id, space_id;
    space_id = game_get_player_location(game);
    if (space_id == NO_ID) {
        return;
    }

    if (player_get_object_id(game->player) != NO_ID && space_get_object(game->spaces[space_id - 1]) != NO_ID) { /*Si el jugador tiene tiene un objeto*/
        id = space_take_object(game->spaces[space_id - 1]);
        space_leave_object(game->spaces[space_id - 1], player_get_object_id(game->player));
        player_set_object_id(game->player, id);
    } else if (space_get_object(game->spaces[space_id - 1]) != NO_ID) { /*Si el jugador tiene no tiene ningún objeto*/
        id = space_take_object(game->spaces[space_id - 1]);
        player_set_object_id(game->player, id);
    }
    return;
}

/******************************************************************
 *Funcion:game_callback_leave_object
 *Date: 1-10-2018
 *Autores: Alvaro Becerra Jiminez
 *Description: Funcion que permite dejar un objeto
 *Input: Game
 *Output: nada
 ********************************************************************/

void game_callback_leave_object(Game* game) {
    Id space_id;
    if (player_get_object_id(game->player) == NO_ID) {
        return;
    }
    space_id = game_get_player_location(game);
    if (space_id == NO_ID) {
        return;
    }
    if (space_get_object(game->spaces[space_id - 1]) != NO_ID) {
        return;
    }
    if ((space_leave_object(game->spaces[space_id - 1], player_get_object_id(game->player))) == ERROR) return;
    player_set_object_id(game->player, NO_ID);
    return;
}

/******************************************************************
 *Funcion :game_reader_load_spaces
 *Date: 1-10-2018
 *Autores: Saul Almazan y Alvaro Becerra Jiminez
 *Description: Funcion que se encarga de cargar los espacios
 *Input: Game y el nombre del fichero donde esta el tablero
 *Output: OK si todo funciona bien y ERROR si hay algun fallo.
 ********************************************************************/

STATUS game_load_spaces(Game* game, char* filename) {
    return game_reader_load_spaces(game, filename);
}
