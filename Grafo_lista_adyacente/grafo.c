#include <stdio.h>
#include <stdlib.h>

struct nodo_lista
{
    int destino;
    struct nodo_lista *siguiente;
};

struct lista_adyacente
{
    struct nodo_lista *cabeza;
};

struct grafo
{
    int vertice;
    struct lista_adyacente *vector;
};

struct nodo_lista *crear_nodo_lista(int destino)
{
    struct nodo_lista *nuevo_nodo = (struct nodo_lista *)malloc(sizeof(struct nodo_lista));
    nuevo_nodo->destino = destino;
    nuevo_nodo->siguiente = NULL;
    return nuevo_nodo;
}

struct grafo *crear_grafo(const int v)
{
    struct grafo *grafo = (struct grafo *)malloc(sizeof(struct grafo));
    grafo->vertice = v;
    grafo->vector = (struct lista_adyacente *)malloc(v * sizeof(struct lista_adyacente));

    for (int i = 0; i < v; ++i)
    {
        grafo->vector[i].cabeza = NULL;
    }

    return grafo;
}

void insertar_arista(struct grafo *grafo, int origen, int destino)
{
    struct nodo_lista *nuevo_nodo = crear_nodo_lista(destino);
    nuevo_nodo->siguiente = grafo->vector[origen].cabeza;
    grafo->vector[origen].cabeza = nuevo_nodo;

    nuevo_nodo = crear_nodo_lista(origen);
    nuevo_nodo->siguiente = grafo->vector[destino].cabeza;
    grafo->vector[destino].cabeza = nuevo_nodo;
}

void mostrar_grafo(struct grafo *grafo)
{
    for (int v = 0; v < grafo->vertice; ++v)
    {
        struct nodo_lista *nodo_aux = grafo->vector[v].cabeza;
        printf("\nLista numero %d: ", v);
        while (nodo_aux)
        {
            printf("-> %d", nodo_aux->destino);
            nodo_aux = nodo_aux->siguiente;
        }
        printf("\n");
    }
}

int main(void) {
    // Casuística
    return 0;
}