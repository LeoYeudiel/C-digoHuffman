#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef struct{
    char cad[100];
}Cadena;

char *concatenacion(char *destino, size_t tam, char * cadenas[], size_t cantCad) {
  assert(tam > 0);
  tam--;
  char *p = destino;
  while (cantCad-- > 0) {
    size_t len = strlen(*cadenas);
    printf("%s\n",*cadenas);
    printf("El tam es de %ld\n", len);
    if (len >= tam) {
      len = tam;
    }
    tam -= len;
    memcpy(p, *cadenas, len);
    cadenas++;
    p += len;
  }
  *p = '\0';
  return destino;
}

char* concatena(char *destino, size_t tam, Cadena* cadenas, size_t cantCad){
    assert(tam>0);
    
    tam--;
    char *p = destino;
    int i=0;

    while(cantCad-- > 0){
        //printf("%s\n",cadenas[i].cad);
        size_t len = strlen(cadenas[i].cad);
        //printf("%ld\n",len);
        if(len>=tam){
            len = tam;
        }
        tam-=len;
        memcpy(p,cadenas[i].cad,len);
        cadenas++;
        p+=len;
    }

    *p = '\0';

    return destino;
}

void main(){
    char dest[1000];
    char *strs[]  = { "Red", "Green", "Blue" };

    char des2[1000];
    Cadena cad1;
    strcpy(cad1.cad,"Red");

    Cadena cad2;
    strcpy(cad2.cad,"Green");

    Cadena cad3;
    strcpy(cad3.cad,"Blue");

    Cadena cadenas[3] = {cad1,cad2,cad3};

    printf("'%s'\n",concatenacion(dest, sizeof dest, strs, sizeof strs/sizeof strs[0]));

    printf("\n\nImplementacion propia\n\n");
    concatena(des2,sizeof des2, cadenas, sizeof cadenas/sizeof cadenas[0]);
    printf("%s\n",des2);
}