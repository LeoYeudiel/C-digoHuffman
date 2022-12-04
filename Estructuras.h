#define PESOBIT(bpos) 1<<bpos
#define CONSULTARBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)

typedef long long int ll;
typedef unsigned char uc;

typedef struct{
    uc valor;
    ll repeticiones;
}Par;

typedef Par* Pares;


struct nodoArbol{
    Par info;
    struct nodoArbol *izquierdo; 
    struct nodoArbol *derecho;
};

typedef struct nodoArbol Nodo;
typedef struct nodoArbol* NODO;


struct arbol{
    int tam;
    int capacidad;
    NODO* nodos;
};

typedef struct arbol Arbol;
typedef struct arbol* ARBOL;

void imprimeArregloEnteros(int a[], int n);
ll tamArch(char* arch);
void frecuencias(char* arch, Pares tablaFrecuencias);
void arregloPares(Pares tablaFrecuencias);
void quickSort(Pares A, int p, int r);
int pivot(Pares A, int p, int r);
void intercambiar(Pares A, int i, int j);
int elementosTabla(Pares tablaFrecuencias);
void tablaConUtiles(Pares tablaFrecuencias, Pares nuevaTabla, int n);
void imprimeTablaFrecuencias(Pares tablaFrecuencias, int n);
void imprimeBits(int n_bits, uc numero);

NODO nuevoNodo(Par datos);
ARBOL creaArbol(int capacidad);
void intercambioNodos(NODO* a, NODO* b);
void intercambioActualMin(ARBOL a, int indice);
int esTam1(ARBOL a);
NODO extraeMin(ARBOL a);
void inserta(ARBOL ar, NODO n);
void construye(ARBOL a);
int esHoja(NODO raiz);
ARBOL construyeArbolRep(Par datos[], int n); 
NODO construyeArbolHuffman(Par datos[], int n);
void imprimeCodigos(NODO raiz, int a[], int superior);
void codigosHufman(Par datos[], int n);