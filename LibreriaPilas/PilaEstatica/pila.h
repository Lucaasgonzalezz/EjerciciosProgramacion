#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define minimo( X , Y)  ((X) < (Y) ? (X) : (Y))

#define TAM_PILA 1000

typedef struct
{
    char pila[TAM_PILA];
    unsigned tope;
}Pila;

void crearPila(Pila *pila);
bool apilar(Pila* pila,const void* dato, size_t tamDato);
bool desapilar(Pila* pila, void* dato, size_t tamDato);
bool verTope(const Pila* pila,void* dato, size_t tamDato);
bool pilaLlena(const Pila *pila, size_t tamDato);
bool pilaVacia(const Pila *pila);
void vaciarPila(Pila *pila);



#endif // PILA_H_INCLUDED
