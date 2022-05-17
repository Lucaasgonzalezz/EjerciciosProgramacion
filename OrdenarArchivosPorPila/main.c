#include "head.h"

int main()
{
    tPila   pila,
            pAux;
    FILE *pf;
    int lectura,
        valor;
    cargarLoteDePrueba();
    abrirArchivo(&pf);
    crearPila(&pila);
    crearPila(&pAux);
    fread(&lectura,sizeof(lectura),1,pf);
    while(!feof(pf))
    {
        if((pilaVacia(&pila) == 1) || lectura <= valor)
        {
            ponerEnPila(&pila,&lectura,sizeof(int));
            while(pilaVacia(&pAux) == 0)
            {
                sacarDePila(&pAux,&valor,sizeof(int));
                ponerEnPila(&pila,&valor,sizeof(int));
            }
        }
        else
        {

            while(pilaVacia(&pila) == 0 && lectura >= valor)
            {
                sacarDePila(&pila,&valor,sizeof(int));
                ponerEnPila(&pAux,&valor,sizeof(int));
                verTope(&pila,&valor,sizeof(valor));
            }
            ponerEnPila(&pila,&lectura,sizeof(int));
            while(pilaVacia(&pAux) == 0)
            {
                sacarDePila(&pAux,&valor,sizeof(int));
                ponerEnPila(&pila,&valor,sizeof(int));
            }
        }
        fread(&lectura,sizeof(int),1,pf);
        verTope(&pila,&valor,sizeof(valor));
    }
    printf("\nArchivo sin Ordenar:\n");
    mostrarArchivo(&pf);
    fseek(pf,0l,SEEK_SET);
    while(pilaVacia(&pila) == 0)
    {
        sacarDePila(&pila,&valor,sizeof(valor));
        fwrite(&valor,sizeof(valor),1,pf);
    }
    printf("\n\nArchivo ordenado:\n");
    mostrarArchivo(&pf);
    fclose(pf);
    return 0;
}
