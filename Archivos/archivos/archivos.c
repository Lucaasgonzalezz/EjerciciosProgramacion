#include "archivos.h"
#include "../../Fecha/fecha.h"

void abrirArchivo(FILE **pf,char *nombreArchivo)
{

    *pf = fopen(nombreArchivo,"r+b");
    if(*pf==NULL)
    {
      *pf = fopen(nombreArchivo,"w+b");
    }

}


void cargarArchivo(tAlumno *alumno,FILE **pf)
{
    printf("\nIngrese Nombre y Apellido:");
    scanf("%s",&alumno->nombreApellido);
    fflush(stdin);
    ingresarFecha(&alumno->fNac);
    printf("\nIngrese DNI:");
    fflush(stdin);
    scanf("%d",&alumno->dni);
    printf("\nIngrese Promedio:");
    scanf("%f",&alumno->promedio);
    printf("\nIngrese nota 1:");
    scanf("%d",&alumno->notas[0]);
    printf("\nIngrese nota 2:");
    scanf("%d",&alumno->notas[1]);
    fwrite(alumno,sizeof(tAlumno),1,*pf);

}

void mostrarArchivo(char *nombreArchivo,FILE **fp)
{
    tAlumno alumno;
    fread(&alumno,sizeof(tAlumno),1,*fp);
    while(!feof(*fp))
    {
        printf("\nNombre y Apellido : %s",alumno.nombreApellido);
        printf("\nDni: %d",alumno.dni);
        printf("\nFecha de nacimiento: ");
        mostrarFechaDMA(alumno.fNac);
        printf("\nPromedio: %f",alumno.promedio);
        printf("\nNota 1: %d",alumno.notas[0]);
        printf("\nNota 2: %d",alumno.notas[1]);
        fread(&alumno,sizeof(tAlumno),1,*fp);
    }

}
