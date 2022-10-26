#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define minimo( X , Y ) ( ( X ) < ( Y ) ? ( X ) : ( Y ) )
#define TAM_COLA 300


typedef struct
{
    char cola[TAM_COLA];
    unsigned    pri,
                ult,
                tamDisp;
}tCola;


void crearCola(tCola* cola);
bool colaLlena(const tCola* cola, size_t tamDato);
bool colaVacia(const tCola* cola);
bool ponerEnCola(tCola* cola, const void* dato, size_t tamDato);
bool sacarDeCola(tCola* cola, void* dato, size_t tamDato);
bool verPrimeroCola(const tCola* cola, void* dato, size_t tamDato);
void vaciarCola(tCola* cola);


#endif // COLA_H_INCLUDED
