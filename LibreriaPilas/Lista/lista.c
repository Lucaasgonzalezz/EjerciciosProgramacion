#include "lista.h"

void crearLista(tLista* lista )
{
    *lista = NULL;
}

bool listaVacia(const tLista* lista )
{
    return *lista == NULL;
}
bool listaLlena(const tLista* lista, size_t tamInfo)
{
    tNodo* aux = (tNodo*) malloc(sizeof(tNodo));
    void* info = malloc(tamInfo);
    if(!aux || !info)
    {
        free(aux);
        free(info);
        return true;
    }
    free(aux);
    free(info);
    return false;
}
void vaciarLista(tLista* lista )
{
    while(*lista)
    {
        tNodo* aux = *lista;
        *lista = aux->sig;
        free(aux->info);
        free(aux);
    }
}

bool insertarAlPrincipio(tLista* lista, const void* d, size_t tamInfo)
{
    tNodo* nuevo;
    if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL || (nuevo->info = malloc(tamInfo)) == NULL)
        return false;
    memcpy(nuevo->info, d, tamInfo);
    nuevo->sig = *lista;
    nuevo->tamInfo = tamInfo;
    *lista = nuevo;
    return true;
}
bool sacarPrimero(tLista* lista, void* d, size_t tamInfo)
{
    if(*lista == NULL)
        return false;
    tNodo* aux = *lista;
    *lista = aux->sig;
    memcpy(d, aux->info, tamInfo);
    free(aux->info);
    free(aux);
    return true;
}
bool insertarAlFinal(tLista* lista, const void* d, size_t tamInfo)
{
    tNodo* nuevo;
    while(*lista)
        lista = &(*lista)->sig;
    if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL || (nuevo->info = malloc(tamInfo)) == NULL)
        return false;
    memcpy(nuevo->info, d, tamInfo);
    nuevo->sig = NULL;
    nuevo->tamInfo = tamInfo;
    *lista = nuevo;
    return true;
}
bool sacarUltimo(tLista* lista, void* d, size_t tamInfo)
{
    if(*lista == NULL)
        return false;
    while((*lista)->sig)
        lista = &(*lista)->sig;
    memcpy(d, (*lista)->info, minimo(tamInfo, (*lista)->tamInfo));
    free((*lista)->info);
    free(*lista);
    *lista = NULL;
    return true;
}
bool verPrimero(const tLista* lista, void* d, size_t tamInfo)
{
    if(*lista == NULL)
        return false;
    memcpy(d, (*lista)->info, minimo(tamInfo, (*lista)->tamInfo));
    return true;
}
bool verUltimo(const tLista* lista, void* d, size_t tamInfo)
{
    if(*lista == NULL)
        return false;
    while((*lista)->sig)
        lista = &(*lista)->sig;
    memcpy(d, (*lista)->info, minimo(tamInfo, (*lista)->tamInfo));
    return true;
}

tNodo* crearNodo(const void* d, size_t tamInfo)
{
    tNodo* nuevo;
    if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL || (nuevo->info = malloc(tamInfo)) == NULL)
        return NULL;
    memcpy(nuevo->info, d, tamInfo);
    nuevo->sig = NULL;
    nuevo->tamInfo = tamInfo;
    return nuevo;
}

int insertarEnListaOrd(tLista* pl,const void* elem,size_t tamElem,Cmp cmp,Actualizar actualizar)
{

    while(*pl && cmp(elem,(*pl)->info)>0)
    {
        pl=&(*pl)->sig;
    }
    if(*pl && cmp(elem,(*pl)->info)==0)
    {
        if(actualizar)
        {
            actualizar(&(*pl)->info,elem);
        }
        return 0;
    }
    //si no hay dubpicado...
    tNodo* nue=crearNodo(elem,tamElem);
    if(!nue)
        return 0;
    nue->sig=*pl;
    *pl=nue;
    return 1;
}

bool eliminarDeListaOrd(tLista pl,void* elem,size_t tamElem,Cmp cmp)
{
    while(pl && cmp(elem,pl->info)>0) //mientras no sea el ultimo y el elemento sea mayor
    {
        pl=pl->sig;
    }
    if(pl && cmp(elem,pl->info)==0) //si es el elemento
    {
        tNodo* aux=pl;
        pl=pl->sig;
        free(aux->info);
        free(aux);
        return true;
    }
    return false;   //si no esta en la lista
}

void ordenarLista(tLista* lista, Cmp cmp)
{
    tLista lOrd = NULL;
    tLista* plOrd;
    tNodo* nodo;
    while(*lista)
    {
        nodo = *lista;
        *lista = nodo->sig;
        plOrd = &lOrd;
        while(*plOrd && cmp(nodo->info, (*plOrd)->info) > 0)
            plOrd = &(*plOrd)->sig;

        nodo->sig = *plOrd;
        *plOrd = nodo;
    }
    *lista = lOrd;
}

int mostrarLista(const tLista* lista, Mostrar mostrar, FILE* arch)
{
    int cant=0;

    while(*lista)
    {
        mostrar((*lista)->info, arch);
        lista = &(*lista)->sig;
        cant++;
    }
    return cant;
}




