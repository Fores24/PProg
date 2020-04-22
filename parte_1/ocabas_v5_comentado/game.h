/**
 * @brief It defines the game interface
 * for each command
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "space.h"
#include "command.h"
#include "object.h"
#include "player.h"
#define MAX_OBJECT 2

typedef struct _Game {
    Player *player;
    Object *object[MAX_OBJECT];
    Space* spaces[MAX_SPACES + 1];
    T_Command last_cmd;
} Game;

STATUS game_create(Game* game, char * name_player);
STATUS game_create_from_file(Game* game, char* filename, char* name_player);
STATUS game_update(Game* game, T_Command cmd);
STATUS game_destroy(Game* game);
BOOL game_is_over(Game* game);
void game_print_screen(Game* game);
void game_print_data(Game* game);
Space* game_get_space(Game* game, Id id);
Id game_get_player_location(Game* game);
Id game_get_object_location(Game* game, Id id);
char *game_get_object_name(Game *game, Id id);
T_Command game_get_last_command(Game* game);
STATUS game_add_space(Game* game, Space* space);
#endif
