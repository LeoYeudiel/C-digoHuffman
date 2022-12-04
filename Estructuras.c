#include"Estructuras.h"
#include<stdio.h>
#include <stdlib.h>


void imprimeArregloEnteros(int a[], int n){
    int i;
    for(i=0; i<n; i++){
        printf("%d",a[i]);
    }

    printf("\n");
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

void arregloPares(Pares tablaFrecuencias){
    int i;

    for(i=0; i<256; i++){
        tablaFrecuencias[i].repeticiones = -1;
    }
}

void frecuencias(char* archivo, Pares tablaFrecuencias){
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
    }

}

void quickSort(Pares A, int p, int r){
	int j; //La variable será la parte intermediaria del arreglo
	if(p < r){
		//Asigna el pivote con tal de que los elementos más pequeños están a la izquierda y los mayores a la derecha
		j = pivot(A, p, r);
		quickSort(A, p, j-1);
		quickSort(A, j+1, r);
	}
}

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

void intercambiar(Pares A, int i, int j){
	Par temp = A[j];
	A[j] = A[i];
	A[i] = temp;
}

int elementosTabla(Pares tablaFrecuencias){
    int res=0;
    int i;

    for(i=0; i<256; i++){
        if(tablaFrecuencias[i].repeticiones>0){
            res++;
        }
    }

    return res;
}

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

    //printf("BIN\tRep\n");
    printf("NumDec\tASCII\tBIN\tRep\n");

    for(i=0; i<n; i++){
        
        if(tablaFrecuencias[i].repeticiones!=-1){
            valorTF = tablaFrecuencias[i].valor;
            num = valorTF;
            n_bits = sizeof(num)*8;
            

            printf("%d\t%c\t",valorTF,valorTF);
            imprimeBits(n_bits,num);
            printf("\t%lld\n",tablaFrecuencias[i].repeticiones);
        }

    }
}

void imprimeBits(int n_bits, uc numero){
    int i;

    for (i=n_bits-1; i>=0; i--)
	printf("%d",CONSULTARBIT(numero,i));
}

NODO nuevoNodo(Par datos){
    NODO aux = (NODO)malloc(sizeof(Nodo));
    if(aux == NULL){
        printf("No se ha creado el nodo\n");
        exit(0);
    }

    aux->izquierdo = aux->derecho = NULL;
    aux->info.repeticiones = datos.repeticiones;
    aux->info.valor = datos.valor;

    return aux;
}

ARBOL creaArbol(int capacidad){
    ARBOL aux = (ARBOL)malloc(sizeof(Arbol));
    if(aux == NULL){
        printf("No se ha creado el arbol\n");
        exit(0);
    }

    aux->tam = 0;
    aux->capacidad = capacidad;
    aux->nodos = (NODO*)malloc(aux->capacidad*sizeof(NODO));

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

    if(izq<a->tam && a->nodos[izq]->info.repeticiones < a->nodos[min]->info.repeticiones){
        min = izq;
    }

    if(derecha < a->tam && a->nodos[izq]->info.repeticiones < a->nodos[min]->info.repeticiones){
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
 
    for (i = (n - 1) / 2; i >= 0; --i)
        intercambioActualMin(a, i);
}

int esHoja(NODO raiz){
    return !(raiz->izquierdo) && !(raiz->derecho);
}

ARBOL construyeArbolRep(Par datos[], int n){
    ARBOL ar = creaArbol(256);
    int i;

    for(i=0; i<256; i++){
        ar->nodos[i] = nuevoNodo(datos[i]);
    }

    ar->tam = n;
    construye(ar);

    return ar;
}

NODO construyeArbolHuffman(Par datos[], int n){
    NODO izq;
    NODO der;
    NODO superior;

    ARBOL a = construyeArbolRep(datos,n);

    while(!esTam1(a)){
        izq = extraeMin(a);
        der = extraeMin(a);

        Par p;
        p.valor = n;
        p.repeticiones = izq->info.repeticiones + der->info.repeticiones;
        superior = nuevoNodo(p);

        superior->izquierdo = izq;
        superior->derecho = der;

        inserta(a,superior);
    }

    return extraeMin(a);
}

void imprimeCodigos(NODO raiz, int a[], int superior){
    if(raiz->izquierdo){
        a[superior] = 0;
        imprimeCodigos(raiz->derecho, a, superior+1);
    }

    if(raiz->derecho){
        a[superior] = 1;
        imprimeCodigos(raiz->derecho, a, superior+1);
    }

    if(esHoja(raiz)){
        printf("%c: ", raiz->info.valor);
        imprimeArregloEnteros(a,superior);
    }
}

void codigosHufman(Par datos[], int n){
    NODO raiz = construyeArbolHuffman(datos,n);
    int a[100], superior = 0;

    imprimeCodigos(raiz,a,superior);
}