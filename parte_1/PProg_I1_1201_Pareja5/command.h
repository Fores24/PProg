
/* ===================================================================
File: player.c
Version: 2.0
Date: 1-10-2018
Autores: Saul Almazan y Alvaro Becerra Jiminez
Description: Prototipos y enumeración de comandos
Revision historica: 
19-12-2014 versión 1.0 (Código inicial)
1-10-2018 versión 2.0
       Nuevos comandos "Oca_Following", "Oca_Previous", "Coger" y "Soltar"
=================================================================== */
#ifndef COMMAND_H
#define COMMAND_H

/*Enumeración con todos los comando*/
typedef enum enum_Command {
    NO_CMD = -1,
    UNKNOWN,
    EXIT,
    FOLLOWING,
    PREVIOUS,
    OCA_FOLLOWING,
    OCA_PREVIOUS,
    COGER,
    SOLTAR
} T_Command;

/*Función para obtener un comando*/
T_Command get_user_input();

#endif
