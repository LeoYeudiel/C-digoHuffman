#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "EstructurasDes.h"

NODO creaNodo(){
    NODO aux = (NODO)malloc(sizeof(Nodo));
    if(aux == NULL){
        printf("No se ha creado el nodo\n");
        exit(0);
    }
    return aux;
}

void construyeArbol(char* dirDiccionario, NODO raiz){
    FILE* arch;
    int i, longitud =0;
    int valor;
    ll repeticiones;
    char valorDiccionario[100];
    char valorBinario[8];
    NODO n=NULL;

    arch = fopen(dirDiccionario,"rb");
    if(arch == NULL){
        printf("No se ha podido abrir el diccionario\n");
        return;
    }

    while(!feof(arch)){
        valor = 0;

        fscanf(arch, "%lld\t%s\t%d\t%s\n", &repeticiones,valorBinario,&valor,valorDiccionario);
        n = raiz;
        longitud = strlen(valorDiccionario);

        for(i=0; i<longitud; i++){
            if(valorDiccionario[i] == '0'){
                if(n->izq==NULL){
                    n->izq = creaNodo();
                }
                n = n->izq;
            }
            else if(valorDiccionario[i] == '1'){
                if(n->der==NULL){
                    n->der = creaNodo();
                }
                n=n->der;
            }
        }

        n->esHoja =1;
        n->simbolo=valor;
    }

}

ll tamArch(char* arch){
    FILE* archivo = fopen(arch,"r");

    if(archivo==NULL){
        printf("No se pudo abrir el archivo\n");
        return -1;
    }

    fseek(archivo,0L,SEEK_END);
    ll res = ftell(archivo);
    fclose(archivo);

    return res;
}


char *cadCompresion eliminarBitBasura(char* dirCompresion){
    char* res;
    FILE* arch;
    ll tam = tamArch(dirCompresion);

    
}