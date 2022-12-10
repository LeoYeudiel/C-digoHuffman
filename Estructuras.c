//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Diciembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Funciones/Operaciones de para la codificación de Huffman
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include"Estructuras.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>


void imprimePar(Par p){
    printf("%d %lld\n",p.valor, p.repeticiones);
}

void imprimeArregloEnteros(int a[], int n, FILE *arch){
    int i;
    for(i=0; i<n; i++){
        if(arch == NULL) printf("%d",a[i]);
        else fprintf(arch,"%d",a[i]);
    }

    fprintf(arch, "\n");
}

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

/*
  Proceso para inicializar todo nuestro diccionario con el valor de -1 
	--------------------------------------------------------------------
	Argumentos:
	Pares tablaFrecuencias: estructura que guarda información (carácter/elemento y el no. repeticiones del mismo elemento) 
	Variables utilizadas:
	int i: utilizada para el loop
*/
void arregloPares(Pares tablaFrecuencias){
    int i;

    for(i=0; i<256; i++){
        tablaFrecuencias[i].repeticiones = -1;
    }
}

/*
  Función para sacar la tabla de frecuencias, el tamaño de elementos a comprimir y la obtención del contenido del archivo
	--------------------------------------------------------------------
	Argumentos:
	char * archivo: contiene la ruta del archivo a comprimir
  Pares tablaFrecuencias: nuestro diccionario para guardar los elementos y la cantidad de repeticiones del mismo
  ll *tam: guarda el tamaño de bytes del archivo
	Variables utilizadas:
	FILE *arch: tipo de dato para abrir el archivo y extraer la información
  *return* uc* lectura: devuelve el contenido extraído del archivo
  ll i: utilizada para el loop
  int n: para identificar el byte que es.
*/
uc* frecuencias(char* archivo, Pares tablaFrecuencias, ll* tam){
    //Declaración de funciones
    FILE* arch;
    uc* lectura;
    ll i;
    int n;

    //Sacamos el tamaño del archivo
    *tam = tamArch(archivo);
    
    //Asignamos la memoria para poder guardar los elementos del archivo
    lectura = (unsigned char*) malloc(sizeof(ll) * (*tam));
    if(lectura==NULL){
        printf("No hay memoria disponible para el arreglo");
		exit(1);
    }

    //Abrimos el archivo en modo lectura binaria
    arch = fopen(archivo,"rb");

    /*Recoge toda la información del archivo
    Argumentos:
    - lectura: variable en la que se va a guardar el archivo
    - *tam: valor que contiene el tamaño del archivo, por lo tanto el contenido a leer
    - arch: archivo a leer
    */
    fread(lectura,(*tam),1,arch);

    //Recorre todo el contenido obtenido y va registrando las repeticiones en nuestro diccionario de elementos
    for(i=0; i<(*tam); i++){
        //Ve el byte que es
        n = lectura[i];
        
        //Si no hay registro del elemento, registra el valor e incializa la repetición como 1, en caso de que haya registro va incrementando el no. de repeticiones
        if(tablaFrecuencias[n].repeticiones==-1){
            tablaFrecuencias[n].repeticiones = 1;
            tablaFrecuencias[n].valor = n;
        }
        else{
            tablaFrecuencias[n].repeticiones++;
        }
    }

    //Cerramos el archivo
    fclose(arch);

    return lectura;
}

/*
	Algoritmo de ordenamiento "quickSort" (Función recursiva que se encarga de dividir el arreglo con ayuda del pivotes para ir ordenando)
	------------------------------------------
	Argumentos:
	Pares A, estructura para ordenar conforme a las repeticiones
	int p, posición inicial del arreglo
	int r, posición final del arreglo/tamaño del arreglo
	Variables utilizadas:
	int j, posición del pivote asignado
*/
void quickSort(Pares A, int p, int r){
	int j; //La variable será la parte intermediaria del arreglo
	if(p < r){
		//Asigna el pivote con tal de que los elementos más pequeños están a la izquierda y los mayores a la derecha
		j = pivot(A, p, r);
		quickSort(A, p, j-1);
		quickSort(A, j+1, r);
	}
}

/*
	Algoritmo de ordenamiento "quickSort" (Función que asigna el pivote e intercambia la posición de manera que en el lado izquierdo esten los números menores y en el lado derecho esten los número mayores al pivote)
	------------------------------------------
	Argumentos:
	Pares A, estructura para ordenar conforme a las repeticiones
	int p, posición inicial del arreglo
	int r, posición final del arreglo/tamaño del arreglo
	Variables utilizadas:
	ll piv, valor del pivote asignado en la posición incial
	int i, variable auxiliar asignada en la posición inicial
	*return* int j, variable auxiliar asignada en la posición final y será retornada como la posición que retoma el pivote
*/
int pivot(Pares A, int p, int r){
	//Declaramos el pivote desde el inicio
	ll piv = A[p].repeticiones;
    int i = p, j = r;
	//Mientras no se crucen los indices
	while(i < j){
		//Va recorriendo la posición inicial hacia la derecha cuando el pivote siga siendo mayor o igual al número a comparar, así mismo también verifica que los indices no colisionen
		while(A[i].repeticiones <= piv && i < j){
			i++;
		}
		//Va recorriendo el numero de final a la izquierda cuando el pivote es menor al número a comparar
		while(A[j].repeticiones > piv){
			j--;
		}
		//Verificamos si todavía no se cruzan los indices y se intercambian las posiciones en donde se hayan quedado los dos anteriores loops
		if(i < j){
			intercambiar(A, i, j);	
		}
	}
	//En cuyo caso de que se hayan cruzado, ponemos el pivote en el lugar que le corresponde
	intercambiar(A, p, j);
	//Regresamos la posición en donde quedo, que será el pivote
	return j;
}

/*
	Algoritmo de ordenamiento "quickSort" (Función que sólo realiza el intercambio de números)
	------------------------------------------
	Argumentos:
	Pares A, estructura conforme a las repeticiones a ordenar
	int i, posición 1 a intercambiar
	int j, posición 2 a intercambiar
	Variables utilizadas:
	int temp, variable auxiliar para poder intercambiar el valor sin que se pierda su valor
*/
void intercambiar(Pares A, int i, int j){
	Par temp = A[j];
	A[j] = A[i];
	A[i] = temp;
}

/*
  Verifica cuantos bytes fueron encontrados en el archivo
	-----------------------------------------------------------
	Argumentos:
	Pares A: estructura que referencia al diccionario de elementos extraídos del archivo
	Variables utilizadas:
	*return* int res: devuelve la variable que guarda la cantidad de bytes identificados en el archivo
  int i: utilizada para el loop
*/
int elementosTabla(Pares tablaFrecuencias){
    int res=0;
    int i;

    //Recorre el diccionario
    for(i=0; i<256; i++){
        //En caso de que el número de repeticiones sea mayor a 0 suma el contador
        if(tablaFrecuencias[i].repeticiones>0){
            res++;
        }
    }

    return res;
}

/*
  Pasa en la nueva la información encontrada en el archivo
  --------------------------------------------------------
  Argumentos:
  Pares tablaFrecuencias: estructura que trae la posibilidad de tener valores nulos y la encontrada en el archivo
  Pares nuevaTabla: estructura en donde sólo se guardará la información encontrada en el archivo
*/
void tablaConUtiles(Pares tablaFrecuencias, Pares nuevaTabla, int n){
    int aux=0;
    int i;

    for(i=0; i<256; i++){
        if(tablaFrecuencias[i].repeticiones>0){
            nuevaTabla[aux] = tablaFrecuencias[i];
            aux++;
        }
    }
}


void imprimeTablaFrecuencias(Pares tablaFrecuencias, int n){
    int i,valorTF,n_bits;
    uc num;

    printf("BIN\tRep\n");
    //printf("NumDec\tASCII\tBIN\tRep\n");

    for(i=0; i<n; i++){
        
            valorTF = tablaFrecuencias[i].valor;
            num = valorTF;
            n_bits = sizeof(num)*8;
            

            //printf("%d\t%c\t",valorTF,valorTF);
            imprimeBits(n_bits,num, NULL);
            printf("\t%lld\n",tablaFrecuencias[i].repeticiones);

    }
}

void imprimeBits(int n_bits, uc numero, FILE *arch){
    int i;

    for (i=n_bits-1; i>=0; i--)
    	if(arch == NULL) printf("%d",CONSULTARBIT(numero,i));
    	else fprintf(arch ,"%d",CONSULTARBIT(numero,i));
}

/*
	Creación de un nodo metiendo el contenido del elemento (Estructura Par)
	----------------------------
	Argumentos:
	Par datos: estructura que contiene el elemento y el no de repeticiones
	Variables utilizadas:
	*return* NODO aux: devolverá el nodo que contendrá la información de un elemento
*/
NODO nuevoNodo(Par datos){
    //Asignamos memoria
    NODO aux = (NODO)malloc(sizeof(Nodo));
    if(aux == NULL){
        printf("No se ha creado el nodo\n");
        exit(0);
    }
    //Inicializamos variables donde sus ramas serán NULL
    aux->izquierdo = aux->derecho = NULL;
    //Se mete la información de la estructura Par
    aux->info.repeticiones = datos.repeticiones;
    aux->info.valor = datos.valor;

    //imprimePar(datos);

    return aux;
}

/*
	Creación de estructura árbol
	----------------------------
	Argumentos:
	int capacidad: el número de elementos diferentes extraídos del archivo y así crear un número de nodos a utilizar para después realizar su barrido
	Variables utilizadas:
	*return* ARBOL aux: devolverá el una estructura ARBOL inicial, con el número de nodos a utilizar que será igual al número de elementos diferentes a analizar
*/
ARBOL creaArbol(int capacidad){
    //Creamos el ARBOL padre
    ARBOL aux = (ARBOL)malloc(sizeof(Arbol));
    if(aux == NULL){
        printf("No se ha creado el arbol\n");
        exit(0);
    }

    //Instanciamos valores iniciales
    aux->tam = 0;
    //Número de elementos a analizar
    aux->capacidad = capacidad;
    //Se crea los n nodos necesarios para poder analizar
    aux->nodos = (NODO*)malloc(aux->capacidad*sizeof(NODO));

    //printf("%d\t%d\n",aux->tam,capacidad);

    return aux;
}

void intercambioNodos(NODO* a, NODO* b){
    NODO aux = *a;
    *a = *b;
    *b = aux;
}

void intercambioActualMin(ARBOL a, int indice){
    int min = indice;
    int izq = 2*indice+1;
    int derecha = 2*indice+2;

    if( izq < a->tam && 
        a->nodos[izq]->info.repeticiones < a->nodos[min]->info.repeticiones){
        min = izq;
    }

    if(derecha < a->tam && a->nodos[derecha]->info.repeticiones < a->nodos[min]->info.repeticiones){
        min = derecha;
    }

    if(min!=indice){
        intercambioNodos(&a->nodos[min],&a->nodos[indice]);
        intercambioActualMin(a,min);
    }
}

int esTam1(ARBOL a){
    return (a->tam==1);
}

NODO extraeMin(ARBOL a){
    NODO aux = a->nodos[0];
    a->nodos[0] = a->nodos[a->tam-1];

    --a->tam;
    intercambioActualMin(a,0);

    return aux;
}

void inserta(ARBOL ar, NODO n){
    ++ar->tam;
    int i = ar->tam-1;

    while(i && n->info.repeticiones < ar->nodos[(i-1)/2]->info.repeticiones){
        ar->nodos[i] = ar->nodos[(i-1)/2];
        i=(i-1)/2;
    }

    ar->nodos[i] = n;
}

void construye(ARBOL a){
    int n = a->tam - 1;
    int i;
 
    for (i = (n - 1) / 2; i >= 0; --i){
        intercambioActualMin(a, i);
    }
        
}

int esHoja(NODO raiz){
    return !(raiz->izquierdo) && !(raiz->derecho);
}

/*
	Creación de estructura árbol
	----------------------------
	Argumentos:
	int capacidad: el número de elementos diferentes extraídos del archivo y así crear un número de nodos a utilizar para después realizar su barrido
	Variables utilizadas:
	*return* ARBOL aux: devolverá el una estructura ARBOL inicial, con el número de nodos a utilizar que será igual al número de elementos diferentes a analizar
*/
ARBOL construyeArbolRep(Pares datos, int n){
    //Creamos el ARBOL padre inicial que contendrá los n nodos a analizar
    ARBOL ar = creaArbol(n);
    int i;

    //Voy llenando de información al ARBOL obtenida de la estructura Par
    for(i=0; i<n; ++i){
        ar->nodos[i] = nuevoNodo(datos[i]);
    }
    
    ar->tam = n;
    construye(ar);

    return ar;
}

/*

*/
NODO construyeArbolHuffman(Pares datos, int n){
    NODO izq;
    NODO der;
    NODO superior;

    ARBOL a = construyeArbolRep(datos,n);

    while(!esTam1(a)){
        izq = extraeMin(a);
        der = extraeMin(a);

        Par p;
        p.valor = 36;
        p.repeticiones = izq->info.repeticiones + der->info.repeticiones;
        superior = nuevoNodo(p);

        superior->izquierdo = izq;
        superior->derecho = der;

        inserta(a,superior);
    }

    return extraeMin(a);
}

void imprimeCodigos(NODO raiz, int *a, int tope, Cadena *dic, int *max, FILE *nombreArch){
    if(tope>(*max))    *max = tope;

    if(raiz->izquierdo){
        a[tope] = 0;
        imprimeCodigos(raiz->izquierdo, a, tope+1,dic,max, nombreArch);
    }

    if(raiz->derecho){
        a[tope] = 1;
        imprimeCodigos(raiz->derecho, a, tope+1,dic,max, nombreArch);
    }

    if(esHoja(raiz)){
        fprintf(nombreArch,"%lld\t", raiz->info.repeticiones);
        imprimeBits(8,raiz->info.valor, nombreArch);
        fprintf(nombreArch,"\t");
        fprintf(nombreArch, "%d\t", raiz->info.valor);
        imprimeArregloEnteros(a,tope, nombreArch);
        arrToString(a,dic[raiz->info.valor].cad,tope);
    }
}

/*

  -----------------------------------------------------------
  Argumentos:
  Pares datos: estructura que contiene la información extraída del archivo
  int n: referencia el tamaño de elementos encontrados en el archivo
  Cadena *dic:
  Variables utilizadas:
  *return* int res: devuelve la variable que guarda la cantidad de bytes identificados en el archivo
  int i: utilizada para el loop
*/
void generaDiccionario(Pares datos, int n, Cadena *dic, int *max, char *nombreArch){

    NODO raiz = construyeArbolHuffman(datos,n);
    int a[100], tope = 0;
    FILE *arch = fopen(nombreArch, "w");
    imprimeCodigos(raiz,a,tope,dic,max, arch);
    fclose(arch);
}

void arrToString(int *arr, char* s, int n){
    int i=0;
    int indice = 0;

    for (i=0; i<n; i++){
        indice += sprintf(&s[indice], "%d", arr[i]);
    }

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

void generaCadHufman(char* cH, uc* lectura,Cadena *diccionario, ll tam){
    ll i;

    //printf("%ld",sizeof(cH)/sizeof(cH[0]));
    
    for(i=0; i<tam; i++){
        //printf("%s",diccionario[lectura[i]].cad);
        strcat(cH,diccionario[lectura[i]].cad);
    }
}

byte * crearEstructura(int n){
  byte * nvo;
  nvo = (byte *) malloc(sizeof(byte)*n);
  if(nvo == NULL){ 
     printf ("No hay espacio en memoria");
     exit(0);
  }
  return nvo;
}

int * crearDeci(int n){
  int * nvo;
  nvo = (int *) malloc(sizeof(int)*n);
  if(nvo == NULL){ 
     printf ("No hay espacio en memoria");
     exit(0);
  }
  return nvo;
}

int convertorBinToDec(char byte[8]){
    int val[8] = {128,64,32,16,8,4,2,1}, i, resul=0;
    for(i = 0; i < 8; i++){
        if(byte[i] == '1') resul += val[i];
    }
    return resul;
}

void archComp(char* bytes, char* ubicacion){
    
    byte *cadenas, recolectar;
    char nvaCadena[8] = "";
    ll cantBytes, i, cantCero;
    int *dec;

    FILE *arch = fopen(ubicacion,"w");
    if(arch == NULL){
      printf("No se pudo abrir el archivo de compresion!\n");   
      exit(1);             
    } 

    //Saca el número de bytes que hay en la cadena
    cantBytes = (strlen(bytes)/8)+1;
    
    cadenas = crearEstructura (cantBytes + 1);
    dec = crearDeci(cantBytes + 1);

    //Va insertando los caracteres
    for(i = 0; i < cantBytes; i++){
        strncpy(nvaCadena, bytes + (i*8), 8);
        strcpy(cadenas[i].bits, nvaCadena);
    }

    if(strlen(cadenas[cantBytes-1].bits) < 8){
        cantCero = 8 - strlen(cadenas[cantBytes - 1].bits);
        memset(nvaCadena, 0, 8);
        strcat(nvaCadena, cadenas[cantBytes - 1].bits);
        for(i = 8- cantCero ; i < 8; i++){
        strcat(nvaCadena, "0");
        }
        strcpy(cadenas[cantBytes - 1].bits, nvaCadena);

        sprintf(cadenas[cantBytes].bits, "%lld" ,cantCero);
    }
    
    //Va insertando los caracteres
    for(i = 0; i <= cantBytes; i++){
        if(i < cantBytes){
            dec[i] = convertorBinToDec(cadenas[i].bits);
        }else{
            dec[i] = cantCero;
        }

        fprintf(arch,"%c",dec[i]);
    }

    fclose(arch);
}

   
