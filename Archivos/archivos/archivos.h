#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "../../Fecha/fecha.h"
#define CANT_ALUMNOS 60

typedef struct
{
    char nombreApellido[51];
    tFecha fNac;
    int dni;
    float promedio;
    int notas[2];
} tAlumno;

void abrirArchivo(FILE **pf,char *nombreArchivo);
void cargarArchivo(tAlumno *alumno,FILE **pf);
void mostrarArchivo(char *nombreArchivo,FILE **pf);

#endif // ARCHIVOS_H_INCLUDED
