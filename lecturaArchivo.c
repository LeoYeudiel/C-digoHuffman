#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

unsigned char *crearArreglo(int);

void main(){
  //Nombre de los archivos
  char *nombArch = "hola.txt";
  char *resul = "resultado.txt";
  FILE *archivo, *nvoArchivo;
  struct stat st;
  unsigned char *buffer, n;
  int i = 0;

  //rb es binario lectura
  archivo = fopen(nombArch, "rb");
  //wb es sobre escribe binario
  nvoArchivo = fopen(resul, "wb");
  if(archivo == NULL || nvoArchivo == NULL){
		printf("Hubo error al abrir el archivo");
		exit(0);
	}

  //Es el tamaño en bytes del archivo
  stat(nombArch, &st);
  off_t size = st.st_size;

  //Creamos una variable para guardar todos los bytes
  buffer = crearArreglo(size);

  //Vamos sacando y metiendo el byte para la copia del archivo
  while((buffer[i] = fgetc(archivo)) != EOF && i < size){
    printf("%d\n", buffer[i]);
    fputc(buffer[i], nvoArchivo);
    i++;
  }
  
  fclose(archivo);
  fclose(nvoArchivo);
}

unsigned char * crearArreglo(int n){
	unsigned char *array;
	
	array = (unsigned char *) malloc(sizeof(unsigned char) * n);
	
	if(array == NULL){
		printf("No hay memoria disponible para el arreglo");
		exit(1);
	}
	
	return array;
}