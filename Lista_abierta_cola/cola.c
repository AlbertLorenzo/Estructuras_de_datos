#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct _Nodo
{
    int valor;
    struct _Nodo *siguiente;
};

struct _Cola
{
    struct _Nodo *primero, *ultimo;
};

typedef struct _Nodo *Nodo;
typedef struct _Cola *Cola;

Nodo crear_nodo(int valor)
{
    Nodo nodo_nuevo = (Nodo)malloc(sizeof(struct _Nodo));
    nodo_nuevo->valor = valor;
    nodo_nuevo->siguiente = NULL;
    return nodo_nuevo;
}

Cola crear_cola()
{
    Cola cola = (Cola)malloc(sizeof(struct _Cola));
    cola->primero = cola->ultimo = NULL;
    return cola;
}

void insertar(Cola cola, int valor)
{
    Nodo nodo_nuevo = crear_nodo(valor);
    if (!cola->ultimo)
    {
        cola->primero = cola->ultimo = nodo_nuevo;
        return;
    }
    cola->ultimo->siguiente = nodo_nuevo;
    cola->ultimo = nodo_nuevo;
}

int leer(Cola cola)
{
    Nodo nodo_aux = cola->primero;
    if (!nodo_aux)
        return 0;
    int valor_retorno = nodo_aux->valor;
    cola->primero = nodo_aux->siguiente;
    if (!cola->primero)
        cola->ultimo = NULL;
    free(nodo_aux);
    return valor_retorno;
}

bool vacia(Cola cola)
{
    return (cola->primero) ? false : true;
}

void destruir(Cola cola)
{
    Nodo nodo_aux;
    while (!vacia(cola))
    {
        nodo_aux = cola->primero;
        cola->primero = nodo_aux->siguiente;
        free(nodo_aux);
    }
    cola->ultimo = NULL;
}

Nodo primero(Cola cola)
{
    return cola->primero;
}

Nodo ultimo(Cola cola)
{
    return cola->ultimo;
}

void mostrar(Cola cola)
{
    if (vacia(cola)) {
        printf("\nLa cola esta vacia.\n");
        return;
    }

    Nodo nodo_aux = primero(cola);
    while (nodo_aux)
    {
        printf("%d\n", nodo_aux->valor);
        nodo_aux = nodo_aux->siguiente;
    }
}

bool buscar(Cola cola, int valor)
{
    if (vacia(cola))
    {
        printf("\nLa cola esta vacia.\n");
        return false;
    }

    if (valor == cola->primero->valor || valor == cola->ultimo->valor)
        return true;

    Nodo nodo_aux = primero(cola)->siguiente;
    while (nodo_aux)
    {
        if (valor == nodo_aux->valor) return true;
        nodo_aux = nodo_aux->siguiente;
    }
}

int main(void) {
    Cola cola = crear_cola();

    insertar(cola, 5);
    insertar(cola, 15);
    insertar(cola, 25);
    insertar(cola, 35);
    insertar(cola, 45);

    printf("%d\n", buscar(cola, 55));
}