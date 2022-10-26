#include "pila.h"


void crearPila(Pila* pila)
{
    *pila = NULL;
}

bool apilar(Pila* pila, const void* dato, unsigned tamDato)
{
    tNodo* nuevo;

    if((nuevo = (tNodo*)malloc(sizeof(tNodo))) == NULL || (nuevo->info = malloc(tamDato)) == NULL)
    {
        free(nuevo);
        return false;
    }
    memcpy(nuevo->info, dato, tamDato);
    nuevo->tamInfo = tamDato;
    nuevo->sig = *pila;
    *pila = nuevo;
    return true;
}


bool desapilar(Pila* pila, void* dato,unsigned tamElem)
{
    tNodo* aux = *pila;

    if(aux == NULL)
        return false;
    *pila = aux->sig;
    memcpy(dato,aux->info,tamElem);
    free(aux->info);
    free(aux);
    return true;
}

bool verTope(const Pila* pila,void* dato,unsigned tamElem)
{
     if(*pila == NULL)
        return false;
    memcpy(dato,(*pila)->info,tamElem);
    return true;
}

bool pilaLlena(const Pila* pila,unsigned tamElem)
{
    Pila* aux;
    void* info = malloc(sizeof(tamElem));
    if(aux == NULL || info == NULL)
    {
        free(aux);
        free(info);
        return true;
    }
    free(aux);
    free(info);
    return false;
}

bool pilaVacia(const Pila* pila)
{
    return *pila == NULL;
}

void vaciarPila(Pila* pila)
{
    while(*pila)
    {
        tNodo* aux = *pila;
        *pila = aux->sig;
        free(aux->info);
        free(aux);
    }
}
