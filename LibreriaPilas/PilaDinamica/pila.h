#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* Pila;

void crearPila(Pila* pila);
bool apilar(Pila* pila,const void* dato,unsigned tamElem);
bool desapilar(Pila* pila,void* dato,unsigned tamElem);
bool verTope(const Pila* pila,void* dato,unsigned tamElem);
bool pilaLlena(const Pila* pila,unsigned tamElem);
bool pilaVacia(const Pila* pila);
void vaciarPila(Pila* pila);




#endif // PILA_H_INCLUDED
