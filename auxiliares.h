typedef long long int ll;
typedef unsigned char uc;

typedef struct{
    uc valor;
    ll repeticiones;
}Par;

ll tamArch(char* arch);
void frecuencias(char* arch, Par* tablaFrecuencias);
void arregloPares(Par* tablaFrecuencias);
