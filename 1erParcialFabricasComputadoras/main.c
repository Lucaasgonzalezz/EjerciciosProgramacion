/*****************************************************************************************************************
** Apellido/s, Nombre/s:                                      													**
** DNI:                                                       													**
******************************************************************************************************************
** Corrección																								   	**
** **********																								   	**
**                      																					   	**
******************************************************************************************************************
** Nota:																									   	**
*****************************************************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define TDA_LISTA_IMPL_DINAMICA
#include "../TDALista/TDALista.h"
#include "../Comun/Comun.h"
#include "../Cadena/Cadena.h"
#include "../Archivo/Archivo.h"
#include "../Solucion1erParcialFabricasComputadoras/Solucion1erParcialFabricasComputadoras.h"

#define PROD_COR "Productos-cor.dat"
#define PROD_CHU_TXT "Productos-chu.txt"
#define CLI_COR "Clientes-cor.dat"
#define CLI_CHU "Clientes-chu.dat"
#define PROD_FUS "Productos-fus.dat"
#define CLI_FUS "Clientes-fus.dat"
#define PROD_CHU_DAT "Productos-chu.dat"

//#define SOLUCION_DOC
#define SOLUCION_ALU

int procesarArchivos_ALU(
    const char* nombreArchivoProductosCor, const char* nombreArchivoProductosChu,
    const char* nombreArchivoClientesCor, const char* nombreArchivoClientesChu,
    const char* nombreArchivoProductosFus, const char* nombreArchivoClientesFus);
void crearLista_ALU(Lista* lista);
bool insertarEnListaOrd_ALU(Lista* lista,const void* dato,size_t tamDato,int(*cmp)(const void*,const void*));
bool cargarListaProducto_ALU(Lista* lista,char* nombreArchivo);
bool cargarListaCliente_ALU(Lista* lista,char* nombreArchivo);
void mostrarLista_ALU(Lista* lista,void(*mostrar)(const void*));
void mostrarProductos_ALU(const void*);
void mostrarClientes_ALU(const void*);
int compararCodigo_ALU(const void*,const void*);
bool convertirTxtABinProd(const char*);
int compararCodigoInt_ALU(const void* d1,const void* d2);
void mostrarClientes_ALU(const void* d1);
void trozarCadenaLV(char* cadena,Producto* prod);
void borrarDuplicados(Lista* lista,int(*cmp)(const void*,const void*),void(*accion)(void*,void*));
void verPrimeroLista(Lista* lista,const void* dato,size_t tamDato);
void compararPrecio(void* d1,void* d2);

int main()
{
    int resp = generarArchivos();

    if(resp != TODO_OK)
    {
        printf("Error al generar los archivos");
        return resp;
    }

    puts("Archivos Pre Fusion:\n");

    puts(PROD_COR);
    puts("=========================================");
    mostrarArchivoProductosBin(PROD_COR);

    puts("\n");

 /*   puts(PROD_CHU_TXT);
    puts("=========================================");
    mostrarArchivoProductosTxt(PROD_CHU_TXT);

    puts("\n");

    puts(CLI_COR);
    puts("=========================================");
    mostrarArchivoClientes(CLI_COR);

    puts("\n");

    puts(CLI_CHU);
    puts("=========================================");
    mostrarArchivoClientes(CLI_CHU);*/


    #ifdef SOLUCION_DOC
        resp = procesarArchivos(PROD_COR, PROD_CHU_TXT, CLI_COR, CLI_CHU, PROD_FUS, CLI_FUS);
    #else
        resp = procesarArchivos_ALU(PROD_COR, PROD_CHU_TXT, CLI_COR, CLI_CHU, PROD_FUS, CLI_FUS);
    #endif

    if(resp != TODO_OK)
    {
        printf("Error al procesar los archivos");
        return resp;
    }

    puts("\n\nArchivos Post Fusion:\n");

    puts(PROD_FUS);
    puts("=========================================");
    mostrarArchivoProductosBin(PROD_FUS);

    puts("\n");

    puts(CLI_FUS);
    puts("=========================================");
    mostrarArchivoClientes(CLI_FUS);

    return 0;
}

int procesarArchivos_ALU(
    const char* nombreArchivoProductosCor, const char* nombreArchivoProductosChu,
    const char* nombreArchivoClientesCor, const char* nombreArchivoClientesChu,
    const char* nombreArchivoProductosFus, const char* nombreArchivoClientesFus)
{
    Lista lista;
    crearLista_ALU(&lista);
    cargarListaProducto_ALU(&lista,PROD_COR);
    convertirTxtABinProd(PROD_CHU_TXT);
    cargarListaProducto_ALU(&lista,PROD_CHU_DAT);
    mostrarLista_ALU(&lista,mostrarProductos_ALU);
    borrarDuplicados(&lista,compararCodigo_ALU,compararPrecio);
    mostrarLista_ALU(&lista,mostrarProductos_ALU);
    //cargarListaCliente_ALU(&lista,CLI_COR);
    //cargarListaCliente_ALU(&lista,CLI_CHU);

}


void crearLista_ALU(Lista* lista)
{
    *lista = NULL;
}

bool insertarEnListaOrd_ALU(Lista* lista,const void* dato,size_t tamDato,int(*cmp)(const void*,const void*))
{
    while(*lista && cmp(dato,(*lista)->elem) > 0)
        lista = &(*lista)->sig;

    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if(!nuevo)
        return false;
    nuevo->elem = malloc(tamDato);
    if(!nuevo->elem)
    {
        free(nuevo);
        return false;
    }
    memcpy(nuevo->elem,dato,tamDato);
    nuevo->tamElem = tamDato;
    nuevo->sig = *lista;
    *lista = nuevo;
    return true;
}

bool convertirTxtABinProd(const char* nombreArchivo)
{
    FILE* arch;
    arch = fopen(nombreArchivo,"rt");
    if(arch == NULL)
    {
        puts("no se pudo abrir archivo rt");
        return false;
    }
    FILE* archBin;
    archBin = fopen("Productos-chu.dat","wb");
    if(archBin == NULL)
    {
        puts("no se pudo abrir archivo wb");
        fclose(arch);
        return false;
    }
    char linea[150];
    Producto prod;
    while(fgets(linea,150,arch))
    {
        trozarCadenaLV(linea,&prod);
        fwrite(&prod,sizeof(Producto),1,archBin);
    }
    fclose(arch);
    fclose(archBin);
    return true;
}

bool cargarListaProducto_ALU(Lista* lista,char* nombreArchivo)
{
    FILE* pf;
    pf = fopen(nombreArchivo,"rb");
    if(pf==NULL)
    {
        puts("no se pudo abrir archivo");
        return false;
    }
    Producto prod;
    fread(&prod,sizeof(Producto),1,pf);
    while(!feof(pf))
    {
        insertarEnListaOrd_ALU(lista,&prod,sizeof(Producto),compararCodigo_ALU);
        fread(&prod,sizeof(Producto),1,pf);
    }

    fclose(pf);
}

bool cargarListaCliente_ALU(Lista* lista,char* nombreArchivo)
{
    FILE* pf;
    pf = fopen(nombreArchivo,"rb");
    if(pf==NULL)
    {
        puts("no se pudo abrir archivo");
        return false;
    }
    Cliente cli;
    fread(&cli,sizeof(Cliente),1,pf);
    while(!feof(pf))
    {
        insertarEnListaOrd_ALU(lista,&cli,sizeof(Cliente),compararCodigoInt_ALU);
        fread(&cli,sizeof(Cliente),1,pf);
    }
    mostrarLista_ALU(lista,mostrarClientes_ALU);
    fclose(pf);
}

void mostrarLista_ALU(Lista* lista,void(*mostrar)(const void*))
{
    puts("Mostrar lista");
    while(*lista)
    {
        mostrar((*lista)->elem);
        lista =&(*lista)->sig;
    }
}

void mostrarProductos_ALU(const void* d1)
{
    Producto prod = *(Producto*)d1;
    printf("%s\t%s\t%f\t%d\n",prod.codigo,prod.descripcion,prod.precio,prod.stock);
}

void mostrarClientes_ALU(const void* d1)
{
    Cliente clie = *(Cliente*)d1;
    printf("%d\t%s\n",clie.codigo,clie.apellidoYNombre);
}

int compararCodigo_ALU(const void* d1,const void* d2)
{
    Producto p1 = *(Producto*)d1;
    Producto p2 = *(Producto*)d2;
    return strcmp(p1.codigo,p2.codigo);
}

int compararCodigoInt_ALU(const void* d1,const void* d2)
{
    Cliente cli1 = *(Cliente*)d1;
    Cliente cli2 = *(Cliente*)d2;

    return cli1.codigo - cli2.codigo;
}

void trozarCadenaLV(char* cadena,Producto* prod)
{
    char* aux;
    aux = strchr(cadena,'\n');
    *aux = '\0';
    aux = strrchr(cadena,'|');

    sscanf(aux+1,"%d",&prod->stock);
    *aux = '\0';
    aux = strrchr(cadena,'|');
    sscanf(aux+1,"%f",&prod->precio);
    *aux = '\0';
    aux = strchr(cadena,'|');
    strcpy(prod->descripcion,aux+1);
    *aux = '\0';
    strcpy(prod->codigo,cadena);
}




void borrarDuplicados(Lista* lista,int(*cmp)(const void*,const void*),void(*accion)(void*,void*))
{
    Lista listaNueva;
    crearLista_ALU(&listaNueva);
    while(*lista)
    {
        insertarEnListaOrd_ALU(&listaNueva,(*lista)->elem,(*lista)->tamElem,compararCodigo_ALU);
        lista = &(*lista)->sig;
        if(*lista && cmp((listaNueva)->elem,(*lista)->elem) == 0)
        {
            accion((*lista)->elem,(*lista)->sig->elem);
            *lista = (*lista)->sig;
        }
        else
            lista = &(*lista)->sig;
    }
    puts("lista sin duplicados");
    mostrarLista_ALU(&listaNueva,mostrarProductos_ALU);
    *lista = listaNueva;
}

void compararPrecio(void* d1,void* d2)
{
    Producto* prod1 = (Producto*)d1;
    Producto* prod2 = (Producto*)d2;
    if(prod1->precio > prod2->precio)
    {
        prod1->stock += prod2->stock;
    }
    else
    {
        prod1->stock += prod1->stock;
        prod1->precio = prod2->precio;
    }
}
