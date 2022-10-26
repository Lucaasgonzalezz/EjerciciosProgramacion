#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define minimo(x,y) ((x)<(y)?(x):(y))

typedef int(*Cmp)(const void*,const void*);
typedef void(*Actualizar)(void*,const void*);
typedef void(*Mostrar)(const void*, FILE*);


typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* lista );
bool listaVacia(const tLista* lista );
bool listaLlena(const tLista* lista, size_t tamInfo);
void vaciarLista(tLista* lista );
bool insertarAlPrincipio(tLista* lista, const void* d, size_t tamInfo);
bool sacarPrimero(tLista* lista, void* d, size_t tamInfo);
bool insertarAlFinal(tLista* lista, const void* d, size_t tamInfo);
bool sacarUltimo(tLista* lista, void* d, size_t tamInfo);
bool verPrimero(const tLista* lista, void* d, size_t tamInfo);
bool verUltimo(const tLista* lista, void* d, size_t tamInfo);
bool eliminarDeListaOrd(tLista pl,void* elem,size_t tamElem,Cmp cmp);
int insertarEnListaOrd(tLista* pl,const void* elem,size_t tamElem,Cmp cmp,Actualizar actualizar);
void ordenarLista(tLista* pl,Cmp cmp);
int mostrarLista(const tLista* lista, Mostrar mostrar, FILE* arch);
tNodo* crearNodo(const void* elem, size_t tamElem);


#endif // LISTA_H_INCLUDED
