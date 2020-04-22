
 
  /* ===================================================================
File: screen.c
Version: 1.0
Date: 11-01-2017
Autores: Profesores PPROG
Description: Contiene todas las funciones que definen una pantalla
Revision historica: 
11-01-2017 versión 1.0 
=================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"

#pragma GCC diagnostic ignored "-Wpedantic"

#define ROWS 23
#define COLUMNS 80
#define TOTAL_DATA (ROWS * COLUMNS) + 1

#define BG_CHAR '~'
#define FG_CHAR ' '
#define PROMPT " prompt:> "

#define ACCESS(d, x, y) (d + ((y) * COLUMNS) + (x))

/*Estructura de Area que contiene la altura, el ancho...*/
struct _Area {
    int x, y, width, height; /*Coordenada x, coordenada y, ancho y altura*/
    char *cursor; /*Cursor*/
};

char *__data;

/****************************/
/*     Private functions    */
/****************************/
int screen_area_cursor_is_out_of_bounds(Area* area);
void screen_area_scroll_up(Area* area);
void screen_utils_replaces_special_chars(char* str);

/****************************/
/* Functions implementation */

/****************************/

/******************************************************************
*Funcion: screen_init
*Date: ??
*Autores: Codigo Inicial
*Description: Función que inicia una pantalla
*Input: nada
*Output: nada
********************************************************************/

void screen_init() {
    screen_destroy(); /* Dispose if previously initialized */
    __data = (char *) malloc(sizeof (char) * TOTAL_DATA);

    if (__data) {
        memset(__data, (int) BG_CHAR, TOTAL_DATA); /*Fill the background*/
        *(__data + TOTAL_DATA - 1) = '\0'; /*NULL-terminated string*/
    }
}

/******************************************************************
*Funcion: screen_destroy
*Date: ??
*Autores: Codigo Inicial
*Description: Función que destruye una pantalla
*Input: nada
*Output: nada
********************************************************************/

void screen_destroy() {
    if (__data)
        free(__data);
}

/******************************************************************
*Funcion: screen_paint
*Date: ??
*Autores: Codigo Inicial
*Description: Función que pinta una pantalla
*Input: nada
*Output: nada
********************************************************************/

void screen_paint() {
    char *src = NULL;
    char dest[COLUMNS + 1];
    int i = 0;

    memset(dest, 0, COLUMNS + 1);

    if (__data) {
        /* puts(__data); */ /*Dump data directly to the terminal*/
        /*It works fine if the terminal window has the right size*/

        puts("\033[2J"); /*Clear the terminal*/
        for (src = __data; src < (__data + TOTAL_DATA - 1); src += COLUMNS) {
            memcpy(dest, src, COLUMNS);
            /* printf("%s\n", dest); */
            for (i = 0; i < COLUMNS; i++) {
                if (dest[i] == BG_CHAR) {
                    printf("\033[0;34;44m%c\033[0m", dest[i]); /* fg:blue(34);bg:blue(44) */
                } else {
                    printf("\033[0;30;47m%c\033[0m", dest[i]); /* fg:black(30);bg:white(47)*/
                }
            }
            printf("\n");
        }
    }
}

void screen_gets(char *str) {
    fprintf(stdout, PROMPT);
    if (fgets(str, COLUMNS, stdin))
        *(str + strlen(str) - 1) = 0; /* Replaces newline character with '\0' */
}

/******************************************************************
*Funcion: screen_area_init
*Date: ??
*Autores: Codigo Inicial
*Description: Función que crea un area
*Input: x, y, width y height
*Output: area
********************************************************************/

Area* screen_area_init(int x, int y, int width, int height) {
    int i = 0;
    Area* area = NULL;

    if ((area = (Area*) malloc(sizeof (struct _Area)))) {
        *area = (struct _Area){x, y, width, height, ACCESS(__data, x, y)};

        for (i = 0; i < area->height; i++)
            memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
    }

    return area;
}

/******************************************************************
*Funcion: screen_area_destroy
*Date: ??
*Autores: Codigo Inicial
*Description: Función que crea un area
*Input: area
*Output: nada
********************************************************************/

void screen_area_destroy(Area* area) {
    if (area)
        free(area);
}

/******************************************************************
*Funcion: screen_area_clear
*Date: ??
*Autores: Codigo Inicial
*Description: Función que limpia un area
*Input: area
*Output: nada
********************************************************************/

void screen_area_clear(Area* area) {
    int i = 0;

    if (area) {
        screen_area_reset_cursor(area);

        for (i = 0; i < area->height; i++)
            memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
    }
}

/******************************************************************
*Funcion: screen_area_reset_cursor
*Date: ??
*Autores: Codigo Inicial
*Description: Función que resetea el cursor de un area
*Input: area
*Output: nada
********************************************************************/

void screen_area_reset_cursor(Area* area) {
    if (area)
        area->cursor = ACCESS(__data, area->x, area->y);
}

/******************************************************************
*Funcion: screen_area_puts
*Date: ??
*Autores: Codigo Inicial
*Description:
*Input: area char *str 
*Output: nada
********************************************************************/

void screen_area_puts(Area* area, char *str) {
    int len = 0;
    char *ptr = NULL;

    if (screen_area_cursor_is_out_of_bounds(area))
        screen_area_scroll_up(area);

    screen_utils_replaces_special_chars(str);

    for (ptr = str; ptr < (str + strlen(str)); ptr += area->width) {
        memset(area->cursor, FG_CHAR, area->width);
        len = (strlen(ptr) < area->width) ? strlen(ptr) : area->width;
        memcpy(area->cursor, ptr, len);
        area->cursor += COLUMNS;
    }
}

/******************************************************************
*Funcion: screen_area_cursor_is_out_of_bounds
*Date: ??
*Autores: Codigo Inicial
*Description: 
*Input: area
*Output: nada
********************************************************************/

int screen_area_cursor_is_out_of_bounds(Area* area) {
    return area->cursor > ACCESS(__data,
            area->x + area->width,
            area->y + area->height - 1);
}

/******************************************************************
*Funcion: screen_area_scroll_up
*Date: ??
*Autores: Codigo Inicial
*Description: 
*Input: area
*Output: nada
********************************************************************/

void screen_area_scroll_up(Area* area) {
    for (area->cursor = ACCESS(__data, area->x, area->y);
            area->cursor < ACCESS(__data, area->x + area->width, area->y + area->height - 2);
            area->cursor += COLUMNS) {
        memcpy(area->cursor, area->cursor + COLUMNS, area->width);
    }
}

/******************************************************************
*Funcion: screen_utils_replaces_special_chars
*Date: ??
*Autores: Codigo Inicial
*Description: Reemplaza caracteres especiales
*Input: cadena de caracters
*Output: nada
********************************************************************/

void screen_utils_replaces_special_chars(char* str) {
    char *pch = NULL;

    /* Replaces acutes and tilde with '??' */
    while ((pch = strpbrk(str, "ÁÉÍÓÚÑáéíóúñ")))
        memcpy(pch, "??", 2);
}
