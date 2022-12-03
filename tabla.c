#include<stdio.h>
#include<stdlib.h>

void imprimetabla(int *A){
	int i;
	for(i=0;i<=255;i++){
	  if((i%5)==0){
	  	printf("\n");
	  }
	  printf("%d - - - [%d]\t\t",i,A[i]);
	}
}
void frecuencias(int *A){
	int n;
	FILE *pArchivo;
    pArchivo = fopen("hola.txt", "rb"); //se coloca el nombre de archivo y extensi�n
    if(pArchivo==NULL){
    	printf("\n ***** ERROR *****");
    }else{
    	printf("\n ***** Abierto *****");
    	while(!feof(pArchivo)){
    		fread(&n,1,1,pArchivo);
    		 A[n]++;
    	}
    fclose(pArchivo);
    }
}

int main(){
	int A[255]={};
	frecuencias(A);
	imprimetabla(A); //opcional
	return 0;
}
