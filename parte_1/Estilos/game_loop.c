
/* ===================================================================
File: game_loop.c
Version: 2.0
Date: 1-10-2018
Autores: Saul Almazan y Alvaro Becerra Jiminez
Description: Ejecuta el main y el juego hasta que pongamos el comando exit
Revision historica: 
13-01-2015 versión 1.0 (código inicial)
1-10-2018 versión 2.0 
      Se pide el nombre del jugador

=================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"
#include "game.h"
#define TAM 32

int main(int argc, char *argv[]) {
    char name_player[TAM];
    Game game;
    T_Command command = NO_CMD;
    Graphic_engine *gengine;
    if (argc < 2) {
        fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
        return 1;
    }
    /*pedimos el nombre del jugador*/
    printf("Escriba su nombre (si es compuesto hágalo así: Juan_Pablo): ");
    scanf("%s", name_player);
    if (game_create_from_file(&game, argv[1], name_player) == ERROR) {
        fprintf(stderr, "Error while initializing game.\n");
        return 1;
    }
    /*cremaos el motor grafico*/
    if ((gengine = graphic_engine_create()) == NULL) {
        fprintf(stderr, "Error while initializing graphic engine.\n");
        game_destroy(&game);
        return 1;
    }
    /*jugamos hasta que haya un error o un exit*/
    while ((command != EXIT) && !game_is_over(&game)) {
        graphic_engine_paint_game(gengine, &game);
        command = get_user_input();
        game_update(&game, command);
    }
    /*liberamos la memoria*/
    game_destroy(&game);
    graphic_engine_destroy(gengine);
    return 0;
}
