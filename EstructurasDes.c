#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "EstructurasDes.h"

/*
  Función que saca el tamaño del archivo
	--------------------------------------
	Argumentos:
	char *arch: contiene la ruta del archivo a analizar 
	Variables utilizadas:
	FILE *archivo: tipo de dato para abrir el archivo y extraer la información
  *return* ll res: devuelve la posición del puntero del archivo (tamaño del archivo)
*/
ll tamArch(char* arch){
    //Abrimos el archivo en modo lectura
    FILE* archivo = fopen(arch,"r");

    if(archivo==NULL){
        printf("No se pudo abrir el archivo\n");
        return -1;
    }

    /*Recorre el puntero de lectura del archivo de inicio a fin
    Agrumentos:
    - archivo: archivo de análisis
    - inicio de la posición
    - SEEK_END constante para señalar el final del archivo
    */
    fseek(archivo,0L,SEEK_END);
    //Devuelve la posición en la que se encuentra el archivo, que será el tamaño del contenido del archivo
    ll res = ftell(archivo);
    //Cerramos el archivo
    fclose(archivo);

    return res;
}



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

uc * generaCad(char * dirCompresion){
    FILE *archComprimido;
    uc* lectura;
    ll tam = tamArch(dirCompresion);
    lectura = crearCarac(tam);
    archComprimido = fopen(dirCompresion,"rb");
    fread(lectura,tam,1,archComprimido);

    //printf("%lld",tam);


    fclose(archComprimido);
    return lectura;
}

void descompresion(char * dirCompresion, char* dirDescompresion, NODO arbol){
    char c = 0, *cadenaBytes, auxElem[1];
    int i, j, val[8] = {128, 64, 32, 16, 8, 4, 2, 1}, bytes, pos, esCeros, noCeros;
    FILE *archComprimido;
    FILE *archDescomprimido;
    NODO aux = arbol;
    uc *caracteres;
    long long int tamBytes;

    caracteres = generaCad(dirCompresion);
    tamBytes = tamArch(dirCompresion);

    auxElem[0] = caracteres[tamBytes - 2];
    noCeros = atoi(auxElem);
    auxElem[0] = caracteres[tamBytes - 1];
    esCeros = atoi(auxElem);

    cadenaBytes = crearBin((tamBytes - 2) * 8);
    
    for (i = 0; i < tamBytes - 2; i++){
      bytes = (int)caracteres[i];
      if(i == (tamBytes - 3) && esCeros == 1){
          for (j = 0; j < (8 - noCeros); j++){
            pos = (i * 8) + j;
            if((bytes - val[j + noCeros]) >= 0){
              bytes -= val[j + noCeros];
              cadenaBytes[pos] ='1';
            }else{
              cadenaBytes[pos] = '0';
            }
          }
      }else{
        for (j = 0; j < 8; j++){
            pos = (i * 8) + j;
            if((bytes - val[j]) >= 0){
              bytes -= val[j];
              cadenaBytes[pos] ='1';
            }else{
              cadenaBytes[pos] = '0';
            }
        }
      }
    }

    for (i = 0; i < ((tamBytes-2) * 8) - noCeros; i++){
        printf("%c", cadenaBytes[i]);
    }
    //archComprimido = fopen(dirCompresion,"r");
    archDescomprimido = fopen(dirDescompresion,"w");

    if(archDescomprimido == NULL){
    //if(archComprimido == NULL || archDescomprimido == NULL){
        printf("No se han podido abrir los archivo\n");
        return;
    }

    for (i = 0; i < ((tamBytes-2) * 8) - noCeros; i++){
        c = cadenaBytes[i];
        if(c=='0')
            aux = aux->izq;
        else if(c=='1')
            aux = aux->der;
        else{
            printf("Se ha leido un caracter no esperado\n");
            return;
        }

        if(aux->esHoja){
            fprintf(archDescomprimido,"%c",aux->simbolo);
            aux = arbol;
        }
    }

    fclose(archDescomprimido);
}

unsigned char * crearCarac(int n){
  unsigned char *nvo;
  nvo = (unsigned char *)malloc(sizeof(unsigned char) * n);
  if(nvo == NULL){
    printf("No hay espacio en memoria");
    exit(0);
  }
  return nvo;
}

char * crearBin(long long int n){
    char * nvo;
    nvo = (char *) malloc(sizeof(char)*n);
    if(nvo == NULL){ 
      printf ("No hay espacio en memoria");
      exit(0);
    }
    return nvo;
}