#include "pila.h"

void crearPila(Pila *pila)
{
    pila->tope = TAM_PILA;
}

bool apilar(Pila* pila,const void* dato, size_t tamDato)
{
    if(pila->tope < tamDato + sizeof(size_t))
        return false;

    pila->tope -= tamDato;
    memcpy(pila->pila + pila->tope, dato, tamDato);
    pila->tope -= sizeof(size_t);
    memcpy(pila->pila + pila->tope, &tamDato, sizeof(size_t));
    return true;
}

bool desapilar(Pila* pila, void* dato, size_t tamDato)
{
    if(pila->tope == TAM_PILA)
        return false;
    memcpy(&tamDato, pila->pila + pila->tope, sizeof(size_t));
    pila->tope += sizeof(size_t);
    memcpy(dato, pila->pila + pila->tope, tamDato);
    pila->tope += tamDato;
    return true;
}

bool verTope(const Pila* pila, void* dato, size_t tamDato)
{
    unsigned tamInfo;

    if(pila->tope == TAM_PILA)
        return false;

    memcpy(&tamInfo, pila->pila + pila->tope, sizeof(size_t));
    memcpy(dato, pila->pila + pila->tope + sizeof(size_t), minimo(tamDato, tamInfo));
    return true;
}

bool pilaVacia(const Pila* pila)
{
    return pila->tope == TAM_PILA;
}

bool pilaLlena(const Pila* pila, size_t tamDato)
{
    return pila->tope < (tamDato + sizeof(size_t));
}

void vaciarPila(Pila* pila)
{
    pila->tope = TAM_PILA;
}
