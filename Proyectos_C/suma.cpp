#include <stdio.h>

int main() {

    int numero1;
    int numero2;
    int suma;

    printf("Introduce el primer numero: ");
    scanf("%d", &numero1);
    printf("Introduce el segundo numero: ");
    scanf("%d", &numero2);

    suma = numero1 + numero2;
    printf("La suma es: %d\n", suma);


    return 0;
}
