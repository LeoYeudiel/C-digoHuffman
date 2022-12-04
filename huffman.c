#include <stdio.h>
#include <stdlib.h>
#include "Estructuras.h"

int main(){
    char nombre[] = "archLec/hola.txt";
    Par tablaFrecuencias[256];
    int i,n;

    arregloPares(tablaFrecuencias);
    frecuencias(nombre,tablaFrecuencias);
    quickSort(tablaFrecuencias,0,255);

    n = elementosTabla(tablaFrecuencias);
    Par tFconUtiles[n];
    tablaConUtiles(tablaFrecuencias,tFconUtiles,n);
    //imprimeTablaFrecuencias(tFconUtiles,n);

    codigosHufman(tFconUtiles,n);
    

    return 0;
}