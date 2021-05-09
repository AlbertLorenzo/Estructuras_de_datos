#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Nodo
{
    int valor;
    struct Nodo *siguiente;
};

struct Conjunto
{
    int cardinalidad;
    struct Nodo *primero;
};

typedef struct Nodo Nodo;
typedef struct Conjunto Conjunto;

Conjunto *crear_conjunto(void)
{
    Conjunto *conjunto = (Conjunto *)malloc(sizeof(Conjunto));
    conjunto->primero = (Nodo *)malloc(sizeof(Nodo));
    conjunto->primero->siguiente = NULL;
    conjunto->cardinalidad = 0;
    return conjunto;
}

bool vacio(Conjunto *conjunto)
{
    return conjunto->cardinalidad == 0 ? true : false;
}

int cardinalidad(Conjunto *conjunto)
{
    return conjunto->cardinalidad;
}

void insertar(Conjunto *conjunto, int num)
{
    Nodo *nodo_aux, *co_aux;
    co_aux = conjunto->primero;

    while ((co_aux->siguiente) && (co_aux->siguiente->valor < num))
    {
        co_aux = co_aux->siguiente;
    }

    if (co_aux->siguiente == NULL)
    {
        nodo_aux = (Nodo *)malloc(sizeof(Nodo));
        nodo_aux->valor = num;
        nodo_aux->siguiente = co_aux->siguiente;
        co_aux->siguiente = nodo_aux;
        (conjunto->cardinalidad)++;
    }
    else
    {
        if (co_aux->siguiente->valor == num)
        {
            printf("\nNo se puede insertar %d el elemento puesto que ya existe... \n", num);
        }
        else
        {
            nodo_aux = (Nodo *)malloc(sizeof(Nodo));
            nodo_aux->valor = num;
            nodo_aux->siguiente = co_aux->siguiente;
            co_aux->siguiente = nodo_aux;
            (conjunto->cardinalidad)++;
        }
    }
}

void mostrar(Conjunto *conjunto)
{
    Nodo *nodo_aux = conjunto->primero->siguiente;
    while (nodo_aux)
    {
        printf("%d ", nodo_aux->valor);
        nodo_aux = nodo_aux->siguiente;
    }
}

bool existe(Conjunto *conjunto, int num)
{
    Nodo *nodo_aux = (Nodo *)malloc(sizeof(Nodo));
    nodo_aux = conjunto->primero->siguiente;

    while ((nodo_aux) && (nodo_aux->valor < num))
    {
        nodo_aux = nodo_aux->siguiente;
    }

    if (!nodo_aux)
    {
        return false;
    }
    else
    {
        return nodo_aux->valor == num ? true : false;
    }
    free(nodo_aux);
    return false;
}

bool eliminar(Conjunto *conjunto, int num)
{
    Nodo *nodo_aux, *co_aux;
    co_aux = (Nodo *)malloc(sizeof(Nodo));
    co_aux = conjunto->primero;

    while (co_aux->siguiente && co_aux->siguiente->valor < num)
    {
        co_aux = co_aux->siguiente;
    }

    if (!co_aux)
    {
        return false;
    }
    else
    {
        if (co_aux->siguiente->valor == num)
        {
            nodo_aux = co_aux->siguiente;
            co_aux->siguiente = co_aux->siguiente->siguiente;
            free(nodo_aux);
            (conjunto->cardinalidad)--;
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool iguales(Conjunto *conjunto_1, Conjunto *conjunto_2)
{
    Nodo *nodo_aux_1, *nodo_aux2;

    if (cardinalidad(conjunto_1) == cardinalidad(conjunto_1))
    {
        nodo_aux_1 = conjunto_1->primero;
        nodo_aux2 = conjunto_2->primero;

        while (nodo_aux_1->siguiente && nodo_aux_1->siguiente->valor == nodo_aux2->siguiente->valor)
        {
            nodo_aux_1 = nodo_aux_1->siguiente;
            nodo_aux2 = nodo_aux2->siguiente;
        }

        return !nodo_aux_1->siguiente ? true : false;
    }
    else
    {
        return false;
    }
}

Conjunto *interseccion(Conjunto *conjunto_1, Conjunto *conjunto_2)
{
    Conjunto *conjunto_aux = crear_conjunto();
    Nodo *nodo_aux;

    if (cardinalidad(conjunto_1) < cardinalidad(conjunto_2))
    {
        nodo_aux = conjunto_1->primero->siguiente;
        while (nodo_aux)
        {
            if (existe(conjunto_2, nodo_aux->valor))
            {
                insertar(conjunto_aux, nodo_aux->valor);
            }
            nodo_aux = nodo_aux->siguiente;
        }
    }
    else
    {
        nodo_aux = conjunto_2->primero->siguiente;
        while (nodo_aux)
        {
            if (existe(conjunto_1, nodo_aux->valor))
            {
                insertar(conjunto_aux, nodo_aux->valor);
            }
            nodo_aux = nodo_aux->siguiente;
        }
    }
    return conjunto_aux;
}

Conjunto *union_conjuntos(Conjunto *conjunto_1, Conjunto *conjunto_2)
{
    Conjunto *conjunto_aux = crear_conjunto();
    Nodo *nodo_aux;

    nodo_aux = conjunto_1->primero->siguiente;

    while (nodo_aux)
    {
        insertar(conjunto_aux, nodo_aux->valor);
        nodo_aux = nodo_aux->siguiente;
    }

    nodo_aux = conjunto_2->primero->siguiente;

    while (nodo_aux)
    {
        if (!existe(conjunto_aux, nodo_aux->valor))
        {
            insertar(conjunto_aux, nodo_aux->valor);
        }
        nodo_aux = nodo_aux->siguiente;
    }
    return conjunto_aux;
}

bool subconjunto(Conjunto *conjunto_1, Conjunto *conjunto_2)
{
    return iguales(interseccion(conjunto_1, conjunto_2), conjunto_1);
}

Conjunto *diferencia(Conjunto *conjunto_1, Conjunto *conjunto_2)
{
    Conjunto *conjunto_aux = crear_conjunto();
    Nodo *nodo_aux;
    nodo_aux = conjunto_1->primero->siguiente;

    while (nodo_aux)
    {
        if (!existe(conjunto_2, nodo_aux->valor))
        {
            insertar(conjunto_aux, nodo_aux->valor);
        }
        nodo_aux = nodo_aux->siguiente;
    }
    return conjunto_aux;
}

int main(void)
{
    Conjunto *conjunto1 = crear_conjunto();
    Conjunto *conjunto2 = crear_conjunto();

    insertar(conjunto1, 5);
    insertar(conjunto1, 2);
    insertar(conjunto1, 9);
    insertar(conjunto1, 1);

    insertar(conjunto2, 5);
    insertar(conjunto2, 2);
    insertar(conjunto2, 3);
    insertar(conjunto1, 1);

    Conjunto *aux = diferencia(conjunto1, conjunto2);

    mostrar(aux);

    return 0;
}