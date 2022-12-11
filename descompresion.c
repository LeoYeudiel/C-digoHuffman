#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "EstructurasDes.h"

int main(){
    char diccionario[] = "salidas/frecuencias.txt";
    char dirCompresion[] = "salidas/compresion.dat";
    char dirDescompresion[] = "salidas/descompresion.mp3";
    char* cadComp;
    uc *caracteres;
    long long int tamBytes;

    NODO arbol = creaNodo();
    construyeArbol(diccionario,arbol);
    descompresion(dirCompresion, dirDescompresion, arbol);
}