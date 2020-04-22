/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "GameReader.h"

#define N_CALLBACK 8

/**
   Define the function type for the callbacks
 */
typedef void (*callback_fn)(Game* game);

/**
   List of callbacks for each command in the game
 */
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

/**
   Private functions
 */

STATUS game_load_spaces(Game* game, char* filename);
Id game_get_space_id_at(Game* game, int position);
STATUS game_set_object_location(Game* game, Id id, Id id_object);

/**
   Game interface implementation
 */

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
	Sin embargo, para probar la funcionalidad, incluiremos un objeto con id=1 y con nombre "Objeto misterioso" y otro con id=2 y nombre
	"La saga/fuga de J.B.".*/
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

STATUS game_create_from_file(Game* game, char* filename, char* name_player) {

    if (game_create(game, name_player) == ERROR)
        return ERROR;

    if (game_load_spaces(game, filename) == ERROR)
        return ERROR;
    if (player_set_space_id(game->player, game_get_space_id_at(game, 0)) == ERROR) {
        return ERROR;
    }

    game_set_object_location(game, game_get_space_id_at(game, 0), object_get_id(game->object[0]));
    game_set_object_location(game, game_get_space_id_at(game, 4), object_get_id(game->object[1]));

    return OK;
}

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

Id game_get_space_id_at(Game* game, int position) {

    if (position < 0 || position >= MAX_SPACES) {
        return NO_ID;
    }

    return space_get_id(game->spaces[position]);
}

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

STATUS game_set_object_location(Game* game, Id id, Id id_object) {
    if (id == NO_ID) {
        return ERROR;
    }
    return space_set_object(game->spaces[id - 1], id_object);
}

Id game_get_player_location(Game* game) {
    return player_get_space_id(game->player);
}

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

char *game_get_object_name(Game *game, Id id) {
    return object_get_name(game->object[id - 1]);
}

STATUS game_update(Game* game, T_Command cmd) {
    game->last_cmd = cmd;
    (*game_callback_fn_list[cmd])(game);
    return OK;
}

T_Command game_get_last_command(Game* game) {
    return game->last_cmd;
}

void game_print_data(Game* game) {
    int i = 0;

    printf("\n\n-------------\n\n");

    printf("=> Spaces: \n");
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        space_print(game->spaces[i]);
    }
    for (i = 0; i < MAX_OBJECT && game->spaces[i] != NULL; i++) {
        printf("=> Object location: %d\n", (int) game_get_object_location(game, i + 1));
    }

    printf("=> Player location: %d\n", (int) game_get_player_location(game));
    printf("prompt:> ");
}

BOOL game_is_over(Game* game) {
    return FALSE;
}

/**
   Callbacks implementation for each action
 */

void game_callback_unknown(Game* game) {
}

void game_callback_exit(Game* game) {
}

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

void game_callback_take_object(Game* game) {
    Id id, space_id;
    space_id = game_get_player_location(game);
    if (space_id == NO_ID) {
        return;
    }

    if (player_get_object_id(game->player) != NO_ID && space_get_object(game->spaces[space_id - 1]) != NO_ID) {
        id = space_take_object(game->spaces[space_id - 1]);
        space_leave_object(game->spaces[space_id - 1], player_get_object_id(game->player));
        player_set_object_id(game->player, id);
    } else if (space_get_object(game->spaces[space_id - 1]) != NO_ID) {
        id = space_take_object(game->spaces[space_id - 1]);
        player_set_object_id(game->player, id);
    }
    return;
}

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

/*Lectura de espacios*/

STATUS game_load_spaces(Game* game, char* filename) {
    return game_reader_load_spaces(game, filename);
}
