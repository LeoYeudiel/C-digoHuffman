#include <stdio.h>
#include <stdlib.h>
#include "Estructuras.h"

int main(){
    char nombre[] = "archLec/hola.txt";
    //char nombre[] = "archLec/objetivo.png";
    Par tablaFrecuencias[256];
    Pares tablaUtiles;
    int i,n;

    arregloPares(tablaFrecuencias);
    frecuencias(nombre,tablaFrecuencias);
    quickSort(tablaFrecuencias,0,255);

    n = elementosTabla(tablaFrecuencias);
    tablaUtiles = (Pares)malloc(sizeof(Par)*n);
    tablaConUtiles(tablaFrecuencias,tablaUtiles,n);
    
    //imprimeTablaFrecuencias(tablaFrecuencias,256);
    //imprimeTablaFrecuencias(tablaUtiles,n);

    codigosHufman(tablaUtiles,n);
    

    return 0;
}