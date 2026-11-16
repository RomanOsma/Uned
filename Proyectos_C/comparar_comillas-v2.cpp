#include <stdio.h>
#include <string.h>

const int MaxCadena = 30;
typedef char TipoCadena[MaxCadena];

int main() {
    char letra;
    TipoCadena palabra;
    int resultado;
    int primeraPos;

    primeraPos = 0;

    /* 1. Lectura y comparacion de un caracter con comillas simples */
    printf("Escribe una letra (pulsa s o S para aceptar): ");
    scanf(" %c", &letra);

    if (letra == 's' || letra == 'S') {
        printf("Has pulsado la letra S.\n\n");
    } else {
        printf("No has pulsado S, sino %c.\n\n", letra);
    }

    /* 2. Lectura y comparacion de una cadena con comillas dobles */
    printf("Escribe una palabra (prueba con hola): ");
    scanf("%s", palabra);

    resultado = strcmp(palabra, "hola");

    if (resultado == 0) {
        printf("La cadena coincide exactamente con hola.\n");
    } else {
        printf("La palabra %s es distinta de hola.\n", palabra);
    }

    /* 3. Comparar una letra suelta dentro de la cadena con comillas simples */
    if (palabra[primeraPos] == 'h') {
        printf("Eso si, tu palabra empieza por el caracter h.\n");
    } else {
        printf("Tu palabra empieza por el caracter %c.\n", palabra[primeraPos]);
    }

    return 0;
}
