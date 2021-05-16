#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estructuras
struct nodo_arbol;
struct Arbol;
struct nodo_cola;
struct Cola;

// Arbol
struct Arbol *crear_arbol();
struct nodo_arbol *crear_nodo_arbol(int);
struct nodo_arbol *raiz_arbol(struct Arbol *);
bool vacio_arbol(struct Arbol *);
void insertar_arbol(struct Arbol *, int);
bool buscar_arbol(struct Arbol *, int);
int altura_arbol(struct nodo_arbol *);
void recorrido_anchura(struct Arbol *);
void imprimir_nivel(struct nodo_arbol *, int);
struct nodo_arbol *borrar_nodo_arbol(struct nodo_arbol *, int clave);
int grado_arbol_recurs(struct nodo_arbol *nodo);
int grado_arbol_iter(struct nodo_arbol *nodo);
void recorrido_inorden(struct nodo_arbol *);
void recorrido_preorden(struct nodo_arbol *);
void recorrido_postorden(struct nodo_arbol *);
struct nodo_arbol *nodo_arbol_minimo_izq(struct nodo_arbol *);

// Cola
struct nodo_cola *crear_nodo_cola(struct nodo_arbol *);
struct Cola *crear_cola();
void insertar(struct Cola *, struct nodo_arbol *);
struct nodo_arbol *leer(struct Cola *);
bool vacia_cola(struct Cola *);
void limpiar_cola(struct Cola *);
void destruir_cola(struct Cola *);

int main(void)
{
    struct Arbol *arbol = crear_arbol();
    insertar_arbol(arbol, 50);
    insertar_arbol(arbol, 30);
    insertar_arbol(arbol, 20);
    insertar_arbol(arbol, 40);
    insertar_arbol(arbol, 70);
    insertar_arbol(arbol, 60);
    insertar_arbol(arbol, 80);
    recorrido_anchura(raiz_arbol(arbol));
    printf("\n");
    borrar_nodo_arbol(raiz_arbol(arbol), 20);
    printf("\n");
    recorrido_anc(raiz_arbol(arbol));
}

struct nodo_arbol
{
    int clave;
    struct nodo_arbol *izquierda, *derecha;
};

struct Arbol
{
    struct nodo_arbol *raiz;
};

struct nodo_cola
{
    struct nodo_arbol *nodo_arbol;
    struct nodo_cola *siguiente;
};

struct Cola
{
    struct nodo_cola *primero, *ultimo;
};

struct Arbol *crear_arbol()
{
    struct Arbol *arbol = (struct Arbol *)malloc(sizeof(struct Arbol));
    arbol->raiz = NULL;
    return arbol;
}

struct nodo_arbol *crear_nodo_arbol(int clave)
{
    struct nodo_arbol *nodo = (struct nodo_arbol *)malloc(sizeof(struct nodo_arbol));
    nodo->clave = clave;
    nodo->izquierda = nodo->derecha = NULL;
    return nodo;
}

struct nodo_arbol *raiz_arbol(struct Arbol *arbol)
{
    return arbol->raiz;
}

bool vacio_arbol(struct Arbol *arbol)
{
    struct nodo_arbol *raiz = raiz_arbol(arbol);
    return raiz->clave || raiz->clave == 1 ? false : true;
}

void insertar_arbol(struct Arbol *arbol, int clave)
{
    struct nodo_arbol *nodo_nuevo, *nodo_actual, *nodo_previo;

    nodo_nuevo = crear_nodo_arbol(clave);

    if (!raiz_arbol(arbol))
    {
        arbol->raiz = nodo_nuevo;
        return;
    }

    nodo_actual = raiz_arbol(arbol);
    nodo_previo = NULL;

    while (nodo_actual && nodo_actual->clave != clave)
    {
        nodo_previo = nodo_actual;
        nodo_actual = (clave < nodo_actual->clave) ? nodo_actual->izquierda : nodo_actual->derecha;
    }

    if (!nodo_previo)
    {
        nodo_previo = nodo_nuevo;
    }
    else if (clave < nodo_previo->clave)
    {
        nodo_previo->izquierda = nodo_nuevo;
    }
    else
    {
        nodo_previo->derecha = nodo_nuevo;
    }
}

bool buscar_arbol(struct Arbol *arbol, int clave)
{
    struct nodo_arbol *nodo_actual = raiz_arbol(arbol);
    while (nodo_actual)
    {
        if (nodo_actual->clave == clave)
        {
            return true;
        }
        nodo_actual = (clave < nodo_actual->clave) ? nodo_actual->izquierda : nodo_actual->derecha;
    }
    return false;
}

int altura_arbol(struct nodo_arbol *nodo)
{
    if (!nodo)
    {
        return 0;
    }
    else
    {
        int altura_sub_arbol_izq = altura_arbol(nodo->izquierda);
        int altura_sub_arbol_der = altura_arbol(nodo->derecha);

        return (altura_sub_arbol_der < altura_sub_arbol_izq) ? altura_sub_arbol_izq + 1 : altura_sub_arbol_der + 1;
    }
}

void recorrido_anchura(struct Arbol *arbol)
{
    struct Cola *cola = crear_cola();
    struct nodo_arbol *nodo_actual = raiz_arbol(arbol);
    while (nodo_actual)
    {
        printf("%d ", nodo_actual->clave);

        if (nodo_actual->izquierda)
        {
            insertar(cola, nodo_actual->izquierda);
        }

        if (nodo_actual->derecha)
        {
            insertar(cola, nodo_actual->derecha);
        }

        nodo_actual = leer(cola);
    }
    destruir_cola(cola);
}

void recorrido_inorden(struct nodo_arbol *raiz)
{
    if (raiz)
    {
        recorrido_inorden(raiz->izquierda);
        printf("%d ", raiz->clave);
        recorrido_inorden(raiz->derecha);
    }
}

void recorrido_preorden(struct nodo_arbol *raiz)
{
    if (raiz)
    {
        printf("%d ", raiz->clave);
        recorrido_preorden(raiz->izquierda);
        recorrido_preorden(raiz->derecha);
    }
}

void recorrido_postorden(struct nodo_arbol *raiz)
{
    if (raiz)
    {
        recorrido_postorden(raiz->izquierda);
        recorrido_postorden(raiz->derecha);
        printf("%d ", raiz->clave);
    }
}

struct nodo_arbol *borrar_nodo_arbol(struct nodo_arbol *raiz, int clave)
{
    struct nodo_arbol *nodo_actual = raiz_arbol(arbol), *nodo_previo = NULL, *nodo_aux;

    while (nodo_actual && nodo_actual->clave != clave)
    {
        nodo_previo = nodo_actual;
        nodo_actual = (clave < nodo_actual->clave) ? nodo_actual->izquierda : nodo_actual->derecha;
    }

    if (!nodo_actual)
    {
        printf("El nodo no existe.");
        return;
    }

    // El nodo no tiene hijos
    if (!nodo_actual->izquierda && !nodo_actual->derecha)
    {
        if (nodo_previo)
        {
            if (nodo_previo->derecha == nodo_actual)
            {
                nodo_previo->derecha = NULL;
            }
            else
            {
                nodo_previo->izquierda = NULL;
            }
        }
        else
        {
            arbol->raiz = NULL;
        }
        free(nodo_actual);
        return;
    }

    // El nodo tiene un hijo
    if (!nodo_actual->izquierda || !nodo_actual->derecha)
    {
        nodo_aux = (nodo_actual->izquierda) ? nodo_actual->izquierda : nodo_actual->derecha;
        if (nodo_previo)
        {
            if (nodo_previo->derecha == nodo_actual)
            {
                nodo_previo->derecha = nodo_aux;
            }
            else
            {
                nodo_previo->izquierda = nodo_aux;
            }
        }
        else
        {
            arbol->raiz = nodo_aux;
        }
        free(nodo_actual);
        return;
    }

    // El nodo tiene dos hijos
    if (nodo_actual->izquierda && nodo_actual->derecha)
    {
        struct nodo_arbol *nodo_previo_aux = NULL, *nodo_temporal;
        nodo_temporal = nodo_actual->derecha;
        while (nodo_temporal->izquierda)
        {
            nodo_previo_aux = nodo_temporal;
            nodo_temporal = nodo_temporal->izquierda;
        }

        if (nodo_previo_aux)
        {
            nodo_previo_aux->izquierda = nodo_temporal->derecha;
        }
        else
        {
            nodo_actual->derecha = nodo_temporal->derecha;
        }

        nodo_actual->clave = nodo_temporal->clave;
        free(nodo_temporal);
    }
}

int grado_arbol_recurs(struct nodo_arbol *nodo)
{
    if (!nodo)
    {
        return 0;
    }
    int resultado_grado = 0;
    if (nodo->izquierda && nodo->derecha)
    {
        resultado_grado++;
    }

    resultado_grado += (grado_arbol_recurs(nodo->izquierda) + grado_arbol_recurs(nodo->derecha));

    return resultado_grado;
}

int grado_arbol_iter(struct nodo_arbol *nodo)
{
    if (!nodo)
    {
        return 0;
    }

    struct Cola *cola = crear_cola();
    insertar(cola, nodo);
    int resultado = 0;

    while (!vacia_cola(cola))
    {
        struct nodo_arbol *nodo_aux = leer(cola);

        if (nodo_aux->izquierda && nodo_aux->derecha)
        {
            resultado++;
        }

        if (nodo_aux->izquierda)
        {
            insertar(cola, nodo_aux->izquierda);
        }

        if (nodo_aux->derecha)
        {
            insertar(cola, nodo_aux->izquierda);
        }
    }
}

struct nodo_arbol *nodo_arbol_minimo_izq(struct nodo_arbol *nodo)
{
    struct nodo_arbol *nodo_actual = nodo;

    while (nodo_actual && nodo_actual->izquierda)
    {
        nodo_actual = nodo_actual->izquierda;
    }
    return nodo_actual;
}

// Cola

struct nodo_cola *crear_nodo_cola(struct nodo_arbol *nodo)
{
    struct nodo_cola *nodo_nuevo = (struct nodo_cola *)malloc(sizeof(struct nodo_cola));
    nodo_nuevo->nodo_arbol = nodo;
    nodo_nuevo->siguiente = NULL;
    return nodo_nuevo;
}

struct Cola *crear_cola()
{
    struct Cola *cola = (struct Cola *)malloc(sizeof(struct Cola));
    cola->primero = cola->ultimo = NULL;
    return cola;
}

void insertar(struct Cola *cola, struct nodo_arbol *nodo)
{
    struct nodo_cola *nodo_nuevo = crear_nodo_cola(nodo);
    if (!cola->ultimo)
    {
        cola->primero = cola->ultimo = nodo_nuevo;
        return;
    }
    cola->ultimo->siguiente = nodo_nuevo;
    cola->ultimo = nodo_nuevo;
}

struct nodo_arbol *leer(struct Cola *cola)
{
    struct nodo_cola *nodo_aux = cola->primero;
    if (!nodo_aux)
        return 0;
    cola->primero = nodo_aux->siguiente;
    if (!cola->primero)
        cola->ultimo = NULL;
    return nodo_aux->nodo_arbol;
}

void limpiar_cola(struct Cola *cola)
{
    struct nodo_cola *nodo_aux = cola->primero;
    while (nodo_aux)
    {
        cola->primero = nodo_aux->siguiente;
        free(nodo_aux);
    }
    cola->ultimo = NULL;
}

bool vacia_cola(struct Cola *cola)
{
    return !cola->primero ? true : false;
}

void destruir_cola(struct Cola *cola)
{
    limpiar_cola(cola);
    free(cola->primero);
    free(cola->ultimo);
    free(cola);
}
