#include <stdio.h>
#include <stdlib.h>
#include "auxiliares.h"

typedef long long int ll;
typedef unsigned char uc;

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

void arregloPares(Par* tablaFrecuencias){
    int i;

    for(i=0; i<256; i++){
        tablaFrecuencias[i].repeticiones = -1;
    }
}

void frecuencias(char* archivo, Par* tablaFrecuencias){
    FILE* arch;
    uc* lectura;
    ll tam = tamArch(archivo);
    ll i;
    int n;
    
    lectura = (unsigned char*) malloc(sizeof(ll) * tam);
    if(lectura==NULL){
        printf("No hay memoria disponible para el arreglo");
		exit(1);
    }

    arch = fopen(archivo,"rb");

    fread(lectura,tam,1,arch);

    for(i=0; i<tam; i++){
        n = lectura[i];
        
        if(tablaFrecuencias[n].repeticiones==-1){
            tablaFrecuencias[n].repeticiones = 1;
            tablaFrecuencias[n].valor = n;
        }
        else{
            tablaFrecuencias[n].repeticiones++;
        }
        //printf("%u\t",lectura[i]);
    }

}