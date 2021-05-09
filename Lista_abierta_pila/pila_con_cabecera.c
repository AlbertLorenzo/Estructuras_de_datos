#include <stdio.h>
#include <stdlib.h>

//Estructuras para nodo y pila
struct _Nodo {
    int valor;
    struct _Nodo *siguiente;
};

struct _Pila {
    struct _Nodo *cabecera;
};

//Definición para la pila y nodo
typedef struct _Nodo *Nodo;
typedef struct _Pila *Pila;

//Funciones pila
void push(Pila, int);
int pop(Pila);
Pila crear_pila();
void limpiar_pila(Pila*);
void destruir_pila(Pila*);

int main(void) {
    Pila pila = crear_pila();

    push(pila, 5);
    push(pila, 15);
    push(pila, 25);

    printf("%d, ", pop(pila));
    printf("%d, ", pop(pila));
    printf("%d\n", pop(pila));

    return 0;
}

Pila crear_pila() {
    Pila pila;
    Nodo cabecera = malloc(sizeof(struct _Nodo));
    cabecera = NULL;
    pila->cabecera = cabecera;
    return pila;
}

void destruir_pila(Pila *pila) {
    free(pila);
}

void push(Pila pila, int valor) {
    Nodo nuevo_nodo = malloc(sizeof(struct _Nodo));
    nuevo_nodo->valor = valor;
    nuevo_nodo->siguiente = pila->cabecera; 
    pila->cabecera = nuevo_nodo;
}

int pop(Pila pila) {
    if (!pila->cabecera) return 0;
    Nodo puntero_pila = pila->cabecera;
    int valor = puntero_pila->valor;
    pila->cabecera = puntero_pila->siguiente;
    free(puntero_pila);
    return valor;
}
