#include "cola.h"


void crearCola(tCola* cola)
{
    cola->pri = TAM_COLA - 70;
    cola->ult = TAM_COLA - 70;
    cola->tamDisp = TAM_COLA;
}

bool colaLlena(const tCola* cola, size_t tamDato)
{
    return cola->tamDisp < (tamDato + sizeof(size_t));
}

bool colaVacia(const tCola* cola)
{
    return cola->tamDisp == TAM_COLA;
}

bool ponerEnCola(tCola* cola, const void* dato, size_t tamDato)
{
    unsigned ini,
             fin;

    if(cola->tamDisp < tamDato + sizeof(size_t))
        return false;

    cola->tamDisp -= (tamDato + sizeof(size_t));
    if((ini = minimo(sizeof(tamDato), TAM_COLA - cola->ult)) != 0)
        memcpy(cola->cola + cola->ult, &tamDato, ini);
    if((fin = sizeof(tamDato) - ini ) != 0)
        memcpy(cola->cola, ((char*)&tamDato) + ini, fin);
    cola->ult = fin ? fin : cola->ult + ini;
    if((ini = minimo(tamDato, TAM_COLA - cola->ult)) != 0)
        memcpy(cola->cola + cola->ult, dato, ini);
    if((fin = tamDato - ini) != 0)
        memcpy(cola->cola, ((char *)dato) + ini, fin);
    cola->ult = fin ? fin : cola->ult + ini;
    return true;
}

bool sacarDeCola(tCola* cola,void* dato, size_t tamDato)
{
    unsigned tamInfo,
             ini,
             fin;

    if(cola->tamDisp == TAM_COLA)
        return false;

    if((ini = minimo(sizeof(size_t), TAM_COLA - cola->pri)) != 0)
        memcpy(&tamInfo, cola->cola + cola->pri, ini);
    if((fin = sizeof(size_t) - ini) != 0)
        memcpy(((char*)&tamInfo) + ini, cola->cola, fin);
    cola->pri = fin ? fin : cola->pri + ini;
    cola->tamDisp += sizeof(size_t) + tamDato;
    tamDato = minimo(tamInfo, tamDato);
    if((ini = minimo(tamDato, TAM_COLA - cola->pri)) != 0)
        memcpy(dato, cola->cola + cola->pri, ini);
    if((fin = tamInfo - ini) != 0)
        memcpy(((char*)dato) + ini,cola->cola,fin);
    cola->pri = fin ? fin : cola->pri + ini;
    return true;
}

bool verPrimeroCola(const tCola* cola, void* dato, size_t tamDato)
{
    unsigned    tamInfo,
                ini,
                fin,
                pos = cola->pri;

    if(cola->tamDisp == TAM_COLA)
        return false;

    if((ini = minimo(sizeof(size_t), TAM_COLA - pos)) != 0)
        memcpy(&tamInfo, cola->cola + pos, ini);
    if((fin = sizeof(size_t) - ini) != 0)
        memcpy(((char*)&tamInfo) + ini, cola->cola, fin);

    pos = fin ? fin : cola->pri + ini;
    tamInfo = minimo(tamInfo, tamDato);
    if((ini = minimo(tamInfo, TAM_COLA - pos)) != 0)
        memcpy(dato,cola->cola + pos, ini);
    if((fin = tamInfo - ini) != 0)
        memcpy(((char*)dato) + ini, cola->cola, fin);

    return true;
}

void vaciarCola(tCola* cola)
{
    cola->ult = cola->pri;
    cola->tamDisp = TAM_COLA;
}
