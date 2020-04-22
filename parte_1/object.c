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

struct _Object{
  int id;
  char name[TAM];
};

Object *crear_objeto(){
  Object *po = NULL;
  po = (Object*) calloc(1, sizeof(Object));
  return po;
}

void destruir_objeto(Object * po){
  if (po){
    free(po);
    po =  NULL;
  }
 }

int get_id_ob(Object *po){
   if (!po) return -1;
   return po->id;
 }

char  *get_nombre_ob (Object *po){
   if (!po) return NULL;
   return po->name;
 }

 STATUS set_id_ob (Object * po, int nuevoid){
   if (!po) return ERROR;
   po->id = nuevoid;
   return OK;
 }

 STATUS set_nombre_ob (Object *po, char *nuevonombre){
   if (!po || nuevonombre) return ERROR;
   strcpy(po->name, nuevonombre);
   return OK;
 }

 STATUS imprimir_objeto (FILE *f, Object *po){
   if (!po || !f) return ERROR;
   fprintf(f," %d %s\n", po->id, po->name);
   return OK;
 }
