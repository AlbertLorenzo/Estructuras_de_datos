#include <stdio.h>

typedef struct _nodo
{
    int valor;
    struct _nodo *siguiente;
} tipo_nodo;

typedef tipo_nodo *pNodo;
typedef tipo_nodo *Lista;

// Funciones con listas:
void insertar(Lista *l, int v);
void borrar(Lista *l, int v);
void borrar_lista(Lista *);
void mostrar_lista(Lista l);

int main()
{
    Lista lista = NULL;
    pNodo p;

    insertar(&lista, 10);
    insertar(&lista, 40);
    insertar(&lista, 30);
    insertar(&lista, 20);
    insertar(&lista, 50);

    mostrar_lista(lista);

    borrar(&lista, 30);
    borrar(&lista, 50);

    mostrar_lista(lista);

    borrar_lista(&lista);
    return 0;
}

void insertar(Lista *lista, int v)
{
    pNodo nodo;

    nodo = (pNodo)malloc(sizeof(tipo_nodo));
    nodo->valor = v;

    if (*lista == NULL)
        *lista = nodo;
    else
        nodo->siguiente = (*lista)->siguiente;
    (*lista)->siguiente = nodo;
}

void borrar(Lista *lista, int v)
{
    pNodo nodo;

    nodo = *lista;

    do
    {
        if ((*lista)->siguiente->valor != v)
            *lista = (*lista)->siguiente;
    } while ((*lista)->siguiente->valor != v && *lista != nodo);
    if ((*lista)->siguiente->valor == v)
    {
        if (*lista == (*lista)->siguiente)
        {
            free(*lista);
            *lista = NULL;
        }
        else
        {
            nodo = (*lista)->siguiente;
            (*lista)->siguiente = nodo->siguiente;
            free(nodo);
        }
    }
}

void borrar_lista(Lista *lista)
{
    pNodo nodo;

    while ((*lista)->siguiente != *lista)
    {
        nodo = (*lista)->siguiente;
        (*lista)->siguiente = nodo->siguiente;
        free(nodo);
    }

    free(*lista);
    *lista = NULL;
}

void mostrar_lista(Lista lista)
{
    pNodo nodo = lista;

    do
    {
        printf("%d -> ", nodo->valor);
        nodo = nodo->siguiente;
    } while (nodo != lista);
    printf("\n");
}