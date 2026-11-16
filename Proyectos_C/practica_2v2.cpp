/************************************
* NOMBRE: #Angel#
* PRIMER APELLIDO: #Roman#
* SEGUNDO APELLIDO: #Osma#
* DNI: #76044046#
* EMAIL: #romanosma@gmail.com#
************************************/

#include <stdio.h>

/* Funcion modular para obtener el caracter segun el patron de la capa */
char ObtenerCaracter(int pos) {
    int resto;
    char caracter;

    resto = pos % 4;
    if (resto == 0) {
        caracter = '@';
    } else if (resto == 1) {
        caracter = '.';
    } else if (resto == 2) {
        caracter = 'o';
    } else {
        caracter = '.';
    }
    return caracter;
}

int main() {
    int lado;
    int capa;

    printf("¿Lado del Rombo?");
    scanf("%d", &lado);

    if (lado >= 1 && lado <= 20) {
        printf("\n");

        /* 1. TRIANGULO SUPERIOR (incluye la fila central) */
        for (int i = 1; i <= lado; i++) {
            /* Espacios en blanco iniciales */
            for (int k = 1; k <= lado - i; k++) {
                printf(" ");
            }

            /* Bucle unico para todos los caracteres de la fila */
            for (int j = 0; j < 2 * i - 1; j++) {
                if (j < i) {
                    capa = j;                 /* Subida: 0, 1, 2... */
                } else {
                    capa = 2 * i - 2 - j;     /* Bajada simetrica */
                }
                printf("%c", ObtenerCaracter(j));
            }
            printf("\n");
        }

        /* 2. TRIANGULO INFERIOR */
        for (int i = lado - 1; i >= 1; i--) {
            /* Espacios en blanco iniciales */
            for (int k = 1; k <= lado - i; k++) {
                printf(" ");
            }

            /* Bucle unico para todos los caracteres de la fila */
            for (int j = 0; j < 2 * i - 1; j++) {
                if (j < i) {
                    capa = j;                 /* Subida: 0, 1, 2... */
                } else {
                    capa = 2 * i - 2 - j;     /* Bajada simetrica */
                }
                printf("%c", ObtenerCaracter(capa));
            }
            printf("\n");
        }
    }

    return 0;
}
