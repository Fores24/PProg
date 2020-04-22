/** @brief Implementacion del modulo encargado de
 *   cargar los espacios
 *
 * @file Object.h
 * @author Saul Almazan y Alvaro Becerra Jimenez
 * @version 1.0*/

#ifndef OBJECT_H
#define OBJECT_H

typedef struct _Object Object;
#include "types.h"

/*funciones basicas de la creacion y liberar el objeto */
Object *object_create();
void object_destroy(Object *);

/*funciones para obtener los campos de las funciones*/
char *object_get_name(Object *);
Id object_get_id(Object *);
/*funciones para estableces los campos de el objeto*/
STATUS object_set_id(Object *, Id);
STATUS object_set_name(Object *, char *);

/*Funcion para imprimir los campos del objeto en el fichero*/
int print_object(FILE *, Object *);

#endif
