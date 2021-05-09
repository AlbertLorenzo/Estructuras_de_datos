#include <math.h>
#include <stdio.h>

// Estructuras
struct punto {
    // Atributos
    double componente_x;
    double componente_y;
    double componente_z;
    
    // 'Métodos'
    struct punto (*crear_punto_neutro)();
    struct punto (*crear_punto_definido)(double, double, double);
    double (*devuelve_x)(punto);
    double (*devuelve_y)(punto);
    double (*devuelve_z)(punto);
    double (*distancia_euclidea)(punto, punto);
};

// Definiciones de estructuras

typedef struct punto punto;

struct vector {
    // Atributos
    double componente_x;
    double componente_y;
    double componente_z;
};

int main(void) {
    punto p = crear_punto_neutro();
    
    return 0;
}

// Métodos punto

punto crear_punto_neutro() {
    punto p = {0, 0, 0};
    return p;
}

punto crear_punto_definido(double x, double y, double z) {
    punto p = {x, y, z};
    return p;
}

double devuelve_x(punto p) {
    return p.componente_x;
}

double devuelve_x(punto p) {
    return p.componente_y;
}

double devuelve_x(punto p) {
    return p.componente_z;
}

double distancia_euclidea(punto p, punto q) {
    double dist = pow((p.componente_x - q.componente_x), 2) + pow((p.componente_y - q.componente_y), 2) + pow((p.componente_z - q.componente_z), 2);
    return sqrt(dist);
}