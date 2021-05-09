// Declaracion unciones y procedimientos Programa
Cola *seleccionar_cola(Cola *, Cola *, Cola *, Cola *, int);
int seleccionar_opcion_cola();
std::string numero_aleatorio();
char seleccionar_tipo(int);
void generar_cuerpos(Cola *, Cola *, Cola *, Cola *, int);
void mostrar_contenido_galaxias(Cola *, Cola *, Cola *, Cola *);
void simulacion(Cola *, Cola *, Cola *, Cola *);
void programa();

// Definiciones
Cola *seleccionar_cola(Cola *AN, Cola *CE, Cola *VL, Cola *LE, int opcion_cola)
{
    Cola *cola_aux;

    if (opcion_cola == 0)
    {
        cola_aux = AN;
    }
    else if (opcion_cola == 1)
    {
        cola_aux = CE;
    }
    else if (opcion_cola == 2)
    {
        cola_aux = VL;
    }
    else if (opcion_cola == 3)
    {
        cola_aux = LE;
    }
    else
    {
        cola_aux = nullptr;
        std::cout << "La cola seleccionada no existe" << std::endl;
    }

    return cola_aux;
}

int seleccionar_opcion_cola()
{
    int opcion_cola;
    std::cout << "Menu colas.\nAN = 0\nCE = 1\nVL = 2\nLE = 3" << std::endl;
    std::cout << "\nSeleccione una cola: ";
    std::cin >> opcion_cola;
    return opcion_cola;
}

std::string numero_aleatorio()
{
    int n = rand() % 1000;
    std::string numero = "";
    if (n < 10)
    {
        numero += "00";
    }
    else if (n < 100)
    {
        numero += "0";
    }
    numero += std::to_string(n);
    return numero;
}

char seleccionar_tipo(int tipo_cuerpo)
{
    if (tipo_cuerpo == 0)
    {
        return 'S';
    }
    else if (tipo_cuerpo == 1)
    {
        return 'P';
    }
    else if (tipo_cuerpo == 2)
    {
        return 'M';
    }
    return 'A';
}

void generar_cuerpos(Cola *AN, Cola *CE, Cola *VL, Cola *LE, int n)
{
    int i = 1, g, c;
    Cola *cola_aux;
    Nodo *nodo_aux;
    char tipo;
    std::string nombre_cuerpo;
    do
    {
        g = rand() % 4;
        c = rand() % 3;
        tipo = seleccionar_tipo(c);
        cola_aux = seleccionar_cola(AN, CE, VL, LE, g);

        nombre_cuerpo = cola_aux->nombre + numero_aleatorio() + tipo;

        if (buscar(cola_aux, nombre_cuerpo))
        {
            i--;
        }
        else
        {
            i++;
            nodo_aux = crear_nodo(tipo, (rand() % 20) + 1, (rand() % 1000) + 1, nombre_cuerpo);
            insertar(cola_aux, nodo_aux);
        }
    } while (i <= n);
}

void mostrar_contenido_galaxias(Cola *AN, Cola *CE, Cola *VL, Cola *LE)
{
    std::cout << std::endl;
    std::cout << AN->nombre << ": ";
    mostrar(AN);
    std::cout << CE->nombre << ": ";
    mostrar(CE);
    std::cout << VL->nombre << ": ";
    mostrar(VL);
    std::cout << LE->nombre << ": ";
    mostrar(LE);
    std::cout << std::endl;
}

void simulacion(Cola *AN, Cola *CE, Cola *VL, Cola *LE)
{
    int c, g, o;
    Cola *cola_aux;
    Nodo *nodo_aux;
    char tipo;
    bool existe;
    std::string nombre_cuerpo;

    mostrar_contenido_galaxias(AN, CE, VL, LE);

    for (int i = 0; i < 12; i++)
    {
        g = rand() % 4;
        c = rand() % 3;
        o = rand() % 3;

        tipo = seleccionar_tipo(c);
        cola_aux = seleccionar_cola(AN, CE, VL, LE, g);

        nombre_cuerpo = cola_aux->nombre + numero_aleatorio() + tipo;
        existe = buscar(cola_aux, nombre_cuerpo);
        nodo_aux = crear_nodo(tipo, (rand() % 20) + 1, (rand() % 1000) + 1, nombre_cuerpo);

        if (o == 0)
        {
            if (!existe)
            {
                insertar(cola_aux, nodo_aux);
                mostrar_contenido_galaxias(AN, CE, VL, LE);
                std::cout << "Evento: Llegada " << nodo_aux->nombre << " cola " << cola_aux->nombre << std::endl;
            }
            else
            {
                mostrar_contenido_galaxias(AN, CE, VL, LE);
                std::cout << "El cuerpo no se ha podido insertar porque ya existe." << std::endl;
            }
        }
        else if (o == 1)
        {
            if (vacia(cola_aux))
            {
                mostrar_contenido_galaxias(AN, CE, VL, LE);
                std::cout << "No se ha podido realizar el evento OK porque la cola esta vacia." << std::endl;
            }
            else
            {
                nodo_aux = extraer(cola_aux);
                mostrar_contenido_galaxias(AN, CE, VL, LE);
                std::cout << "Evento: Procesamiento OK " << nodo_aux->nombre << " cola " << cola_aux->nombre << std::endl;
            }
        }
        else if (o == 2)
        {
            if (vacia(cola_aux))
            {
                mostrar_contenido_galaxias(AN, CE, VL, LE);
                std::cout << "No se ha podido realizar el evento KO porque la cola esta vacia." << std::endl;
            }
            else
            {
                nodo_aux = extraer(cola_aux);
                nodo_aux->siguiente = nullptr;
                insertar(cola_aux, nodo_aux);
                mostrar_contenido_galaxias(AN, CE, VL, LE);
                std::cout << "Evento: Procesamiento KO " << nodo_aux->nombre << " cola " << cola_aux->nombre << std::endl;
            }
        }
        Sleep(5000);
    }
}

void programa()
{
    Cola *AN, *CE, *VL, *LE, *cola_aux;
    Nodo *nodo_aux;
    char opcion_menu, tipoNodo;
    int masa, distancia, opcion_cola, num_cuerpos;
    std::string nombre_nodo;
    AN = crear_cola("AN");
    CE = crear_cola("CE");
    VL = crear_cola("VL");
    LE = crear_cola("LE");
    do
    {
        std::cout << std::endl;
        std::cout << "A. Introducir manualmente un cuerpo en cualquier cola: {AN, CE, VL, LE}."
                  << std::endl;
        std::cout << "B. Extraer el primer cuerpo de la cola de galaxia que se indique: {AN, CE, VL, LE}."
                  << std::endl;
        std::cout << "C. Imprimir los cuerpos de la cola que se indique: {AN, CE, VL, LE}."
                  << std::endl;
        std::cout << "D. Consultar que cuerpos estan en la cabecera y al final de la cola que se indique: {AN, CE, VL, LE}"
                  << std::endl;
        std::cout << "E. Introducir los datos de n cuerpos que se generaran al azar, y se guardaran en las correspondientes colas de las galaxias correspondientes."
                  << std::endl;
        std::cout << "F. Iniciar la simulacion."
                  << std::endl;
        std::cout << "G. Salir de la aplicacion."
                  << std::endl;
        std::cout << "\nIntroduce una opcion: ";
        std::cin >> opcion_menu;
        std::cout << std::endl;

        switch (opcion_menu)
        {
        case 'A':
            opcion_cola = seleccionar_opcion_cola();
            cola_aux = seleccionar_cola(AN, CE, VL, LE, opcion_cola);
            std::cout << "Masa (0...20]: ";
            std::cin >> masa;

            std::cout << "Distancia (0...1000]: ";
            std::cin >> distancia;

            std::cout << "Tipo cuerpo {S, P, M}: ";
            std::cin >> tipoNodo;

            nombre_nodo = cola_aux->nombre + numero_aleatorio() + tipoNodo;

            if (buscar(cola_aux, nombre_nodo))
            {
                std::cout << "El cuerpo generado ya existe en la cola." << std::endl;
            }
            else
            {
                nodo_aux = crear_nodo(tipoNodo, masa, distancia, nombre_nodo);
                insertar(cola_aux, nodo_aux);
                std::cout << "\nElemento insertado correctamente." << std::endl;
            }
            break;
        case 'B':
            std::cout << "Menu colas.\nAN = 0\nCE = 1\nVL = 2\nLE = 3" << std::endl;
            std::cout << "\nSeleccione una cola: ";
            std::cin >> opcion_cola;
            cola_aux = seleccionar_cola(AN, CE, VL, LE, opcion_cola);
            nodo_aux = extraer(cola_aux);
            std::cout << "\n"
                      << (nodo_aux ? nodo_aux->nombre : "La cola esta vacia.") << std::endl;
            break;

        case 'C':
            opcion_cola = seleccionar_opcion_cola();
            cola_aux = seleccionar_cola(AN, CE, VL, LE, opcion_cola);
            mostrar(cola_aux);
            break;

        case 'D':
            opcion_cola = seleccionar_opcion_cola();
            cola_aux = seleccionar_cola(AN, CE, VL, LE, opcion_cola);
            std::cout << (vacia(cola_aux) ? "\nLa cola esta vacia." : "\nCabecera: " + primero(cola_aux)->nombre + " Final: " + ultimo(cola_aux)->nombre) << std::endl;
            break;

        case 'E':
            std::cout << "Indique el numero de cuerpos que quiera generar: ";
            std::cin >> num_cuerpos;
            generar_cuerpos(AN, CE, VL, LE, num_cuerpos);
            break;

        case 'F':
            simulacion(AN, CE, VL, LE);
            break;

        case 'G':
            break;

        default:
            break;
        }

    } while (opcion_menu != 'G');
}