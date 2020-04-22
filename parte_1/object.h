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
Object *crear_objeto();
void destruir_objeto(Object *);

/*funciones para obtener los campos de las funciones*/
char *get_nombre_ob (Object *);
int get_id_obj(Object *);
/*funciones para estableces los campos de el objeto*/
STATUS set_id_ob (Object *, int);
STATUS set_nombre_ob (Object *, char *);

/*Funcion para imprimir los campos del objeto en el fichero*/
STATUS imprimir_objeto (FILE *, Object *);

#endif
