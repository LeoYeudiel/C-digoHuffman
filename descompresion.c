#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "EstructurasDes.h"

int main(){
    char diccionario[] = "salidas/frecuencias.txt";
    char dirCompresion[] = "salidas/compresion.dat";
    char* cadComp;

    NODO arbol = creaNodo();
    construyeArbol(diccionario,arbol);
    cadComp = eliminarBitBasura(dirCompresion);

}