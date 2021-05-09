// Declaracion TAD
struct Nodo;
struct Cola;

// Declaracion funciones y procedimientos TAD
Cola *crear_cola(std::string);
Nodo *crear_nodo(char, int, int, std::string);
void insertar(Cola *, Nodo *);
bool vacia(Cola *);
Nodo *extraer(Cola *);
void destruir(Cola *);
void limpiar(Cola *);
Nodo *primero(Cola *);
Nodo *ultimo(Cola *);
void mostrar(Cola *);
bool buscar(Cola *, std::string);
Nodo *eliminar_ultimo(Cola *cola);

// Definiciones
struct Nodo
{
    std::string nombre;
    char tipo;
    int masa, distancia;
    struct Nodo *siguiente;
};

struct Cola
{
    std::string nombre;
    struct Nodo *primero, *ultimo;
};

Cola *crear_cola(std::string nombre)
{
    Cola *cola = new Cola{nombre, nullptr, nullptr};
    return cola;
}

Nodo *crear_nodo(char tipo_cuerpo, int masa, int distancia, std::string nombre)
{
    Nodo *nodo_nuevo = new Nodo{nombre, tipo_cuerpo, masa, distancia, nullptr};
    return nodo_nuevo;
}

void insertar(Cola *cola, Nodo *nodo_nuevo)
{
    if (!cola->primero)
    {
        cola->primero = cola->ultimo = nodo_nuevo;
        return;
    }
    cola->ultimo->siguiente = nodo_nuevo;
    cola->ultimo = nodo_nuevo;
}

bool vacia(Cola *cola)
{
    return (cola->primero) ? false : true;
}

Nodo *extraer(Cola *cola)
{
    Nodo *nodo_primero = cola->primero;
    cola->primero = nodo_primero->siguiente;
    if (!cola->primero)
    {
        cola->ultimo = nullptr;
    }
    return nodo_primero;
}

void destruir(Cola *cola)
{
    delete cola;
}

void limpiar(Cola *cola)
{
    Nodo *nodo_primero = cola->primero;
    while (nodo_primero)
    {
        cola->primero = nodo_primero->siguiente;
        delete nodo_primero;
    }
    cola->ultimo = nullptr;
}

Nodo *primero(Cola *cola)
{
    return cola->primero;
}

Nodo *ultimo(Cola *cola)
{
    return cola->ultimo;
}

void mostrar(Cola *cola)
{
    Nodo *nodo_primero = primero(cola);
    while (nodo_primero)
    {
        std::cout << nodo_primero->nombre << " ";
        nodo_primero = nodo_primero->siguiente;
    }
    std::cout << std::endl;
}

bool buscar(Cola *cola, std::string nombre_nodo)
{
    Nodo *nodo_primero = cola->primero;
    while (nodo_primero)
    {
        if (nombre_nodo == nodo_primero->nombre)
        {
            return true;
        }
        nodo_primero = nodo_primero->siguiente;
    }
    return false;
}

Nodo *eliminar_ultimo(Cola *cola)
{
    Nodo *nodo_aux = primero(cola);

    if (!nodo_aux->siguiente)
    {
        cola->primero = cola->ultimo = nullptr;
        return nodo_aux;
    }

    Nodo *nodo_ultimo = ultimo(cola);
    while (nodo_aux->siguiente->siguiente)
    {
        nodo_aux = nodo_aux->siguiente;
    }
    cola->ultimo = nodo_aux;
    nodo_aux->siguiente = nullptr;

    return nodo_ultimo;
}