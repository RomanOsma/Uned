#include <stdio.h>

int main() {

  int numero;
  int suma = 0;

  for (int i = 1; i <= 5; i++) {

    printf("Introduce un numero: ");
    scanf("%d", &numero);

    suma = suma + numero;

  }

  printf("La suma total es: %d\n", suma);


  return 0;
}
