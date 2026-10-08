#include <stdio.h>

int main() {

    int numero;
    int positivos = 0;

    for (int i = 1; i <= 5; i++) {

        printf("Introduce un numero: ");
        scanf("%d", &numero);

        if (numero > 0) {

            positivos++;

        }
    }

    printf("Numeros positivos: %d\n", positivos);


    return 0;
}
