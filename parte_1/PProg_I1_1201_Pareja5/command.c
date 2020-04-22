
/* ===================================================================
File: player.c
Version: 2.0
Date: 1-10-2018
Autores: Saul Almazan y Alvaro Becerra Jiminez
Description: Interpreta los comandos
Revision historica: 
19-12-2014 versión 1.0 (Código inicial)
1-10-2018 versión 2.0
       Nuevos comandos "Oca_Following", "Oca_Previous", "Coger" y "Soltar"
=================================================================== */

#include <stdio.h>
#include <strings.h>
#include "command.h"

#define CMD_LENGHT 30
#define N_CMD 9

char*cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Following", "Previous", "Oca_Following", "Oca_Previous", "Coger", "Soltar"}; /*Lista de comandos largos*/
char *short_cmd_to_str[N_CMD] = {"", "", "e", "f", "p", "o", "q", "c", "s"}; /*Lista de comandos cortos*/

/******************************************************************
 *Funcion: screen_area_init
 *Date: ??
 *Autores: Codigo Inicial
 *Description: Función que interpreta los comandos introducidos por el jugador
 *Input: nada
 *Output: comando
 ********************************************************************/

T_Command get_user_input() {

    T_Command cmd = NO_CMD;
    char input[CMD_LENGHT] = "";
    int i = UNKNOWN - NO_CMD + 1;

    if (scanf("%s", input) > 0) {
        cmd = UNKNOWN;
        while (cmd == UNKNOWN && i < N_CMD) {
            if (!strcasecmp(input, short_cmd_to_str[i]) || !strcasecmp(input, cmd_to_str[i])) {
                cmd = i + NO_CMD;
            } else {
                i++;
            }
        }
    }
    return cmd;
}
