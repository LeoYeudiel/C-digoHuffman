#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "EstructurasDes.h"

int main(){
    char diccionario[] = "salidas/frecuencias.txt";
    char dirCompresion[] = "salidas/temp.txt";
    char dirDescompresion[] = "salidas/descompresion.txt";
    char* cadComp;

    NODO arbol = creaNodo();
    construyeArbol(diccionario,arbol);


    printf("%s\n",generaCad(dirDescompresion));
    descompresion(dirCompresion,dirDescompresion,arbol);

}