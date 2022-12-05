#include <stdio.h>
#include <stdlib.h>
#include "Estructuras.h"

int main(){
    char nombre[] = "archLec/hola.txt";
    //char nombre[] = "archLec/objetivo.png";
    char compresion[] = "salidas/compresion.dat";
    ll tamArchivo;
    uc* lectura;
    Par tablaFrecuencias[256];
    Pares tablaUtiles;
    Cadena diccionarioHuffman[256];
    char *cadenaHufman;
    int i,n;
    int longMaxima=0;

    arregloPares(tablaFrecuencias);
    lectura = frecuencias(nombre,tablaFrecuencias,&tamArchivo);
    quickSort(tablaFrecuencias,0,255);

    n = elementosTabla(tablaFrecuencias);
    tablaUtiles = (Pares)malloc(sizeof(Par)*n);
    tablaConUtiles(tablaFrecuencias,tablaUtiles,n);
    
    //imprimeTablaFrecuencias(tablaFrecuencias,256);
    //imprimeTablaFrecuencias(tablaUtiles,n);

    generaDiccionario(tablaUtiles,n,diccionarioHuffman,&longMaxima);
    cadenaHufman = (char*)malloc(sizeof(char)*longMaxima*tamArchivo);
    generaCadHufman(cadenaHufman,lectura,diccionarioHuffman,tamArchivo);
    //printf("%s\n",cadenaHufman);

    /*
    for(int i=0; i<256; i++){
        printf("%d\t%s\n",i,diccionarioHuffman[i].cad);
    }*/
    
    archComp(cadenaHufman,compresion);

    return 0;
}