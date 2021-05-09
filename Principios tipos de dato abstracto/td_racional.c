#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct racional {
    int numerador;
    int denominador;
};

typedef struct racional racional;

//Constructor
racional racional_constructor(const int numerador, const int denominador);

//Aritmética
bool racional_equivalencia(const racional racional_izquierda, const racional racional_derecha);
racional racional_simplificacion(const racional racional_entrada);
racional racional_orden(const racional racional_izquierda, const racional racional_derecha);
racional racional_suma(const racional racional_izquierda, const racional racional_derecha);
racional racional_resta(const racional racional_izquierda, const racional racional_derecha);
racional racional_multiplicacion(const racional racional_izquierda, const racional racional_derecha);
racional racional_division(const racional racional_izquierda, const racional racional_derecha);

//MCD
int mcd(int a, int b);

//Leer datos entrada teclado
void introducir_datos_teclado(int *a, int *b);

int main(void) {
    //Leer datos
    int a, b, c, d;
    printf("Introduzca los datos de la primera fraccion: ");
    introducir_datos_teclado(&a, &b);
    printf("Introduzca los datos de la segunda fraccion: ");
    introducir_datos_teclado(&c, &d);

    //Construcción
    racional r1, r2, sol_aritmetica;

    //Simplificación
    printf("Racional r1 sin simplificar = %d/%d\n", r1.numerador, r1.denominador);
    printf("Racional r2 sin simplificar = %d/%d\n", r2.numerador, r2.denominador);
    sol_aritmetica = racional_simplificacion(r1);
    printf("Racional r1 simplificado = %d/%d\n", sol_aritmetica.numerador, sol_aritmetica.denominador);
    sol_aritmetica = racional_simplificacion(r2);
    printf("Racional r2 simplificado = %d/%d\n", sol_aritmetica.numerador, sol_aritmetica.denominador);

    //Equivalencia
    printf("Son equivalentes? %s\n", racional_equivalencia(r1, r2) ? "si" : "no");

    //Orden
    sol_aritmetica = racional_orden(r1, r2);
    printf("La fraccion: %d/%d es mayor.\n", sol_aritmetica.numerador, sol_aritmetica.denominador);

    //Suma
    sol_aritmetica = racional_suma(r1, r2);
    printf("Suma: %d/%d\n", sol_aritmetica.numerador, sol_aritmetica.denominador);

    //Resta
    sol_aritmetica = racional_resta(r1, r2);
    printf("Resta: %d/%d\n", sol_aritmetica.numerador, sol_aritmetica.denominador);

    //Multiplicación
    sol_aritmetica = racional_multiplicacion(r1, r2);
    printf("Multiplicacion: %d/%d\n", sol_aritmetica.numerador, sol_aritmetica.denominador);

    //División
    sol_aritmetica = racional_division(r1, r2);
    printf("Division: %d/%d\n", sol_aritmetica.numerador, sol_aritmetica.denominador);

    return 0;
}

racional racional_constructor(const int numerador, const int denominador) {
    racional r = {numerador, denominador};
    return r;
}

bool racional_equivalencia(const racional racional_izquierda, const racional racional_derecha) {
    int a = racional_izquierda.numerador;
    int b = racional_izquierda.denominador;
    int c = racional_derecha.numerador;
    int d = racional_derecha.denominador;
    return (a * d == b * c) > 0 ? true : false;
}

racional racional_simplificacion(const racional racional_entrada) {
    int mcd = __mcd(racional_entrada.numerador, racional_entrada.denominador);
    return racional_constructor(racional_entrada.numerador / mcd, racional_entrada.denominador / mcd);
}

racional racional_orden(const racional racional_izquierda, const racional racional_derecha) {
    racional ri = racional_simplificacion(racional_izquierda);
    racional rd = racional_simplificacion(racional_derecha);
    int a = ri.numerador;
    int b = ri.denominador;
    int c = rd.numerador;
    int d = rd.denominador;
    return (a * d < b * c) ? racional_constructor(a, b) : racional_constructor(c, d);
}

racional racional_suma(const racional racional_izquierda, const racional racional_derecha) {
    int a = racional_izquierda.numerador;
    int b = racional_izquierda.denominador;
    int c = racional_derecha.numerador;
    int d = racional_derecha.denominador;
    return racional_constructor(a * d + b * c, b * d);
}

racional racional_resta(const racional racional_izquierda, const racional racional_derecha) {
    int a = racional_izquierda.numerador;
    int b = racional_izquierda.denominador;
    int c = racional_derecha.numerador;
    int d = racional_derecha.denominador;
    return racional_constructor(a * d - b * c, b * d);
}

racional racional_multiplicacion(const racional racional_izquierda, const racional racional_derecha) {
    int a = racional_izquierda.numerador;
    int b = racional_izquierda.denominador;
    int c = racional_derecha.numerador;
    int d = racional_derecha.denominador;
    return racional_constructor(a * c, b * d);
}

racional racional_division(const racional racional_izquierda, const racional racional_derecha) {
    int a = racional_izquierda.numerador;
    int b = racional_izquierda.denominador;
    int c = racional_derecha.numerador;
    int d = racional_derecha.denominador;
    return racional_constructor(a * d, b * c);
}

int __mcd(int a, int b) {
    int c;
    while (a != 0) {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

void introducir_datos_teclado(int *a, int *b) {
    scanf("%d %d", a, b);
}