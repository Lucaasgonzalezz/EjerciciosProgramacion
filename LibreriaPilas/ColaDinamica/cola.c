#include "cola.h"


void crearCola(tCola* cola)
{
    cola->pri = NULL;
    cola->ult = NULL;
}

bool colaLlena(const tCola* cola, size_t tamDato)
{
    tNodo *aux = (tNodo*)malloc(sizeof(tNodo));
    void *info = malloc(tamDato);
    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}

bool colaVacia(const tCola* cola)
{
    return cola->pri == NULL;
}

bool ponerEnCola(tCola* cola , const void* dato, size_t tamDato)
{
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(nuevo == NULL || (nuevo->info = malloc(tamDato)) == NULL)
    {
        free(nuevo);
        return false;
    }

    memcpy(nuevo->info, dato, tamDato);
    nuevo->tamInfo = tamDato;
    nuevo->sig = NULL;
    if(cola->ult)
        cola->ult->sig = nuevo;
    else
        cola->pri = nuevo;
    cola->ult = nuevo;
    return true;
}

bool verPrimeroCola(const tCola* cola, void* dato, size_t tamDato)
{
    if(cola->pri == NULL)
        return false;
    memcpy(dato, cola->pri->info, minimo(tamDato, cola->pri->tamInfo));
    return true;
}

bool sacarDeCola(tCola* cola, void* dato, size_t tamDato)
{
    tNodo* aux = cola->pri;
    if(cola->pri == NULL)
        return false;

    cola->pri = aux->sig;
    memcpy(dato, aux->info, minimo(tamDato, aux->tamInfo));
    free(aux->info);
    free(aux);
    if(cola->pri == NULL)
        cola->ult = NULL;
    return true;
}

void vaciarCola(tCola* cola)
{
    while(cola->pri)
    {
        tNodo* aux = cola->pri;
        cola->pri = aux->sig;
        free(aux->info);
        free(aux);
    }
    cola->ult = NULL;
}
