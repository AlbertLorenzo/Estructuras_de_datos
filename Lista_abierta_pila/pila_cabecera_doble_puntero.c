#include <stdio.h>
#include <stdlib.h>

struct _Nodo {
    int valor;
    struct _Nodo *siguiente;
};

typedef struct _Nodo **Pila;
typedef struct _Nodo *Nodo;

Pila crear_pila();
void push(Pila, int);
int pop(Pila);

int main(void) {
    Pila pila = crear_pila();
    
    push(pila, 5);
    push(pila, 15);
    push(pila, 25);

    printf("%d\n", pop(pila));
    printf("%d\n", pop(pila));
    printf("%d\n", pop(pila));
}

Pila crear_pila() {
    Pila pila;
    Nodo cabecera = malloc(sizeof(struct _Nodo));
    cabecera = NULL;
    (*pila) = cabecera;
    return pila;
}

void push(Pila pila, int valor) {
    Nodo nuevo_nodo = malloc(sizeof(struct _Nodo));
    nuevo_nodo->valor = valor;
    nuevo_nodo->siguiente = (*pila);
    (*pila) = nuevo_nodo;
}

int pop(Pila pila) {
    if (!(*pila)) return 0;
    Nodo puntero_pila = (*pila);
    int valor = puntero_pila->valor;
    (*pila) = puntero_pila->siguiente;
    free(puntero_pila);
    return valor;
}