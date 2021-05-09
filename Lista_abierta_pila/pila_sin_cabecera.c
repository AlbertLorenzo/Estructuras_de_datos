#include <stdio.h>
#include <stdlib.h>

typedef struct _Nodo {
    //Atributos
    int valor;
    struct _Nodo *siguiente;
} nodo;

//Definición para la pila y nodo
typedef nodo *Nodo;
typedef nodo *Pila;

//Funciones pila
int pop(Pila *pila);
void push(Pila *pila, int valor);

int main(void) {
    Pila pila = NULL;

    push(&pila, 5);
    push(&pila, 10);
    push(&pila, 15);
    push(&pila, 20);

    printf("%d, ", pop(&pila));
    printf("%d, ", pop(&pila));
    printf("%d\n", pop(&pila));

    return 0;
}

int pop(Pila *pila) {
    Nodo nodo_pila;
    int v;
    nodo_pila = *pila;
    if (!nodo_pila) return 0;
    *pila = nodo_pila->siguiente;
    v = nodo_pila->valor;
    free(nodo_pila);
    return v;
}

void push(Pila *pila, int valor) {
    Nodo nodo_nuevo = malloc(sizeof(nodo));
    nodo_nuevo->valor = valor;
    nodo_nuevo->siguiente = *pila;
    *pila = nodo_nuevo;
}
