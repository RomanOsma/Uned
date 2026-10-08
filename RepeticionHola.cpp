#include <stdio.h>


int main() {

    int rep;

    printf("¿Cuantas veces quieres repetir Hola? ");
    scanf("%d", &rep);

    for (int k = 1; k <= rep; k++) {

        printf("Hola\n");

    }

    return 0;
}
