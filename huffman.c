//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Diciembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Algoritmo: Codificación voraz de Huffman
//Compilación: "gcc huffman.c estructuras.c tiempo.x  -o huffman" (tiempo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)
//Ejecución: "./huffman nombre_archivo" (Linux y MAC OS)
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
#include "Estructuras.h"

//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main(int argc, char * argv[]){

    //******************************************************************	
    //Variables del main
    //******************************************************************
    double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
    //char nombre[] = "archLec/objetivo.png";
    char compresion[] = "salidas/compresion.dat"; //Variable del nombre del archivo para poder guardar el archivo comprimido
    char docFrecuencias[] = "salidas/frecuencias.txt";
    ll tamArchivo;
    uc* lectura;
    Par tablaFrecuencias[256];
    Pares tablaUtiles;
    Cadena diccionarioHuffman[256];
    char *cadenaHufman;
    int i,n;
    int longMaxima=0;

    //******************************************************************	
    //Recepción y decodificación de argumentos
    //******************************************************************	
    //Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=nombre)
    if (argc!=2) 
    {
      printf("\nIndique el directorio del algoritmo - Ejemplo: [user@equipo]$ %s archLec/hola.txt\n",argv[0]);
      exit(1);
    } 


    //******************************************************************	
		//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
		//******************************************************************	
		uswtime(&utime0, &stime0, &wtime0);

    //Inicializamos nuestro diccionario (repeticiones)
    arregloPares(tablaFrecuencias);
    //Obtiene el tamaño, el contenido y la tabla de frecuencias del archivo
    lectura = frecuencias(argv[1],tablaFrecuencias,&tamArchivo);
    //Ordenamos conforme al número de repeticiones
    quickSort(tablaFrecuencias,0,255);

    //Obtenemos el tamaño de bytes identificados en el archivo
    n = elementosTabla(tablaFrecuencias);
    //Creamos una nueva estructura que contendrá la información jugosa
    tablaUtiles = (Pares)malloc(sizeof(Par)*n);
    //Pasamos sólo los elementos verificados a nuestra nueva estructura
    tablaConUtiles(tablaFrecuencias,tablaUtiles,n);
    
    //imprimeTablaFrecuencias(tablaFrecuencias,256);
    //imprimeTablaFrecuencias(tablaUtiles,n);

    generaDiccionario(tablaUtiles,n,diccionarioHuffman,&longMaxima, docFrecuencias);
    printf("\n");
    cadenaHufman = (char*)malloc(sizeof(char)*longMaxima*tamArchivo);
    //generaCadHufman(cadenaHufman,lectura,diccionarioHuffman,tamArchivo);
    concatena(cadenaHufman,longMaxima*tamArchivo,lectura,diccionarioHuffman,tamArchivo);

    /*
    for(int i=0; i<256; i++){
        printf("%d\t%s\n",i,diccionarioHuffman[i].cad);
    }*/
    
    archComp(cadenaHufman,compresion);

    //******************************************************************	
		//Evaluar los tiempos de ejecución 
		//******************************************************************
		uswtime(&utime1, &stime1, &wtime1);
		
		//Cálculo del tiempo de ejecución del programa
		printf("\n");
		printf("Para el archivo = %s\n", argv[1]);
		printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
		printf("real (Tiempo total exponencial)  %.10e s\n",  wtime1 - wtime0);
		printf("\n");

    return 0;
}
