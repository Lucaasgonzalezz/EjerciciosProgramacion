#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 10

typedef struct sNodo
{
    void    *info;
    unsigned    tamInfo;
    void    *sig;
}tNodo;
typedef tNodo *tPila;


void cargarLoteDePrueba();
void abrirArchivo(FILE **pf);
void crearPila(tPila *p);
int pilaLlena(const tPila *p,unsigned cantBytes);
int ponerEnPila(tPila *p,const void *d,unsigned cantBytes);
int sacarDePila(tPila *p,void *d,unsigned cantBytes);
int verTope(const tPila *p,void *d,unsigned cantBytes);
int pilaVacia(const tPila *p);
void vaciarPila(tPila *p);



#endif // HEAD_H_INCLUDED
