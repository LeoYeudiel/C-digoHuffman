#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
	unsigned char buffer[18];
	char *nombArch = "dream river(MP3_128K).mp3";
	FILE *archivo;
	size_t bytes;
	
	archivo = fopen(nombArch, "r");
	if(archivo == NULL){
		printf("Hubo error al abrir el archivo");
		exit(0);
	}
	
	while(!feof(archivo)){
		bytes = fread(buffer, sizeof(char), sizeof(buffer), archivo);
		printf(" Bytes = %lu\n");
		fwrite(buffer, sizeof(char), bytes, stdout);
	}
	
	fclose(archivo);
}