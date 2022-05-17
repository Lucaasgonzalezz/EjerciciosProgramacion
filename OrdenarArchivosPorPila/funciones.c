#include "head.h"


void cargarLoteDePrueba()
{
    FILE *pf;
    int notas[TAM]={2,8,24,61,3,6,7,9,17,1};
    pf = fopen("Numeros.dat","wb");
    if(!pf)
    {
        printf("No se pudo abrir el archivo");
    }

    fwrite(notas,sizeof(notas),1,pf);

    fclose(pf);
}

void abrirArchivo(FILE **pf)
{
    *pf = fopen("Numeros.dat","r+b");
    if(!pf)
        printf("No se pudo abrir el archivo");

}
void mostrarArchivo(FILE **pf)
{
    int dato;
    fseek(*pf,0l,SEEK_SET);
    fread(&dato,sizeof(dato),1,*pf);
    while(!feof(*pf))
    {
        printf("%d\t",dato);
        fread(&dato,sizeof(dato),1,*pf);
    }


}
void ordenarArchivo(FILE **pf,tPila pila)
{
    int valor;
    fseek(*pf,0l,SEEK_SET);
    while(!feof(*pf))
    {
        sacarDePila(&pila,&valor,sizeof(valor));
        fwrite(&valor,sizeof(valor),1,*pf);
    }
}
void crearPila(tPila *p)
{
    *p=NULL;
}

int pilaLlena(const tPila *p,unsigned cantBytes)
{
    tNodo *aux = (tNodo *)malloc(sizeof(tNodo));

    if(!aux)
    {
        return 1;
    }
    aux->info = malloc(cantBytes);
    if(!aux->info)
    {
        free(aux);
        return 1;
    }
    free(aux);
    free(aux->info);
    return 0;
}

int ponerEnPila(tPila *p,const void *d,unsigned cantBytes)
{
    tNodo *nue;

    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info,d,cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig=*p;
    *p=nue;

    return 1;
}

int verTope(const tPila *p,void *d,unsigned cantBytes)
{
    if(*p == NULL)
        return 0;
    memcpy(d,(*p)->info,cantBytes);
    return 1;
}

int pilaVacia(const tPila *p)
{
    if(*p == NULL)
        return 1;
    return 0;
}

int sacarDePila(tPila *p,void *d,unsigned cantBytes)
{
    tNodo *aux = *p;

    if(aux == NULL)
        return 0;
    *p = aux->sig;
    memcpy(d,aux->info,cantBytes);
    free(aux->info);
    free(aux);
    return 1;
}

void vaciarPila(tPila *p)
{
    while(*p)
    {
        tNodo *aux = *p;

        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
}
