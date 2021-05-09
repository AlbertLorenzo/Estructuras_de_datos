#include <stdlib.h>
#include <stdio.h>

#define ASCENDENTE 1
#define DESCENDENTE 0

typedef struct _nodo
{
    int valor;
    struct _nodo *siguiente;
    struct _nodo *anterior;
} tipo_nodo;

typedef tipo_nodo *Nodo;
typedef tipo_nodo *Lista;

void borrar(Lista *l, int v);
void Borrar(Lista *l, int v);

void borrar_lista(Lista *);
void mostrar_lista(Lista l, int orden);

int main()
{
    Lista lista = NULL;
    Nodo p;

    borrar(&lista, 20);
    borrar(&lista, 10);
    borrar(&lista, 40);
    borrar(&lista, 30);

    mostrar_lista(lista, ASCENDENTE);
    mostrar_lista(lista, DESCENDENTE);

    Borrar(&lista, 10);
    Borrar(&lista, 15);
    Borrar(&lista, 45);
    Borrar(&lista, 30);

    mostrar_lista(lista, ASCENDENTE);
    mostrar_lista(lista, DESCENDENTE);

    borrar_lista(&lista);

    system("PAUSE");
    return 0;
}

void borrar(Lista *lista, int v)
{
    Nodo nuevo, actual;

    nuevo = (Nodo)malloc(sizeof(tipo_nodo));
    nuevo->valor = v;

    actual = *lista;
    if (actual)
        while (actual->anterior)
            actual = actual->anterior;

    if (!actual || actual->valor > v)
    {
        nuevo->siguiente = actual;
        nuevo->anterior = NULL;
        if (actual)
        {
            actual->anterior = nuevo;
        }
        if (!*lista)
        {
            *lista = nuevo;
        }
    }
    else
    {
        while (actual->siguiente && actual->siguiente->valor <= v)
        {
            actual = actual->siguiente;
        }

        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
        nuevo->anterior = actual;

        if (nuevo->siguiente)
        {
            nuevo->siguiente->anterior = nuevo;
        }
    }
}

void Borrar(Lista *lista, int v)
{
    Nodo nodo;

    nodo = *lista;

    while (nodo && nodo->valor < v)
    {
        nodo = nodo->siguiente;
    }

    while (nodo && nodo->valor > v)
    {
        nodo = nodo->anterior;
    }

    if (!nodo || nodo->valor != v)
    {
        return;
    }

    if (nodo == *lista)
    {
        if (nodo->anterior)
        {
            *lista = nodo->anterior;
        }
        else
        {
            *lista = nodo->siguiente;
        }
    }

    if (nodo->anterior)
    {
        nodo->anterior->siguiente = nodo->siguiente;
    }

    if (nodo->siguiente)
    {
        nodo->siguiente->anterior = nodo->anterior;
    }

    free(nodo);
}

void borrar_lista(Lista *lista)
{
    Nodo nodo, actual;

    actual = *lista;
    while (actual->anterior)
        actual = actual->anterior;

    while (actual)
    {
        nodo = actual;
        actual = actual->siguiente;
        free(nodo);
    }
    *lista = NULL;
}

void mostrar_lista(Lista lista, int orden)
{
    Nodo nodo = lista;

    if (!lista)
    {
        printf("Lista vacia");
    }

    nodo = lista;
    if (orden == ASCENDENTE)
    {
        while (nodo->anterior){
            nodo = nodo->anterior;
        }
        printf("Orden ascendente: ");
        while (nodo)
        {
            printf("%d -> ", nodo->valor);
            nodo = nodo->siguiente;
        }
    }
    else
    {
        while (nodo->siguiente)
            nodo = nodo->siguiente;
        printf("Orden descendente: ");
        while (nodo)
        {
            printf("%d -> ", nodo->valor);
            nodo = nodo->anterior;
        }
    }

    printf("\n");
}
