/** @brief Implementacion del modulo encargado de
 *   cargar los espacios
 *
 * @file Object.c
 * @author Saul Almazan y Alvaro Becerra Jimenez
 * @version 1.0*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

#define TAM 32

struct _Object {
    Id id;
    char name[TAM];
};

Object *object_create() {
    Object *po = NULL;
    po = (Object*) calloc(1, sizeof (Object));
    po->id = NO_ID;
    return po;
}

void object_destroy(Object * po) {
    if (po) {
        free(po);
        po = NULL;
    }
}

Id object_get_id(Object *po) {
    if (!po) return NO_ID;
    return po->id;
}

char *object_get_name(Object *po) {
    if (!po) return NULL;
    return po->name;
}

STATUS object_set_id(Object * po, Id nuevo_id) {
    if (!po) return ERROR;
    po->id = nuevo_id;
    return OK;
}

STATUS object_set_name(Object *po, char *nuevo_nombre) {
    if (!po || !nuevo_nombre) return ERROR;
    strcpy(po->name, nuevo_nombre);
    return OK;
}

int print_object(FILE *f, Object *po) {
    if (!po || !f) return ERROR;
    return fprintf(f, " %ld %s\n", po->id, po->name);
}
