/************************************
* NOMBRE: #Angel#
* PRIMER APELLIDO: #Roman#
* SEGUNDO APELLIDO: #Osma#
* DNI: #76044046#
* EMAIL: #romanosma@gmail.com#
************************************/

#include <stdio.h>

char ObtenerCaracter(int pos) {
    int resto;
    char caracter;

    resto = pos % 4;
    if(resto==0) {
      caracter ='@';
    }
    else if(resto==1) {
      caracter ='.';
    }
    else if(resto==2) {
      caracter ='o';
    }
    else {
      caracter ='.';
    }
    return caracter;
  }

int main(){

  int lado;
  printf("¿Lado del Rombo?");
  scanf("%d", &lado);

  if (lado>=1 && lado<=20) {

    printf("\n");
    /* Primer salto de linea para dibujar rombo*/


    /* TRIÁNGULO SUPERIOR */
    for(int i=1; i<=lado; i++) {

      for(int k=1; k<=lado-i; k++){

        /*Espacio en blanco para colocar el inicio rombo*/
        printf(" ");
      }
      /*Primer triangulo*/
      for(int j=0; j<i; j++){

        /*Obtener caracter en orden*/
        printf("%c", ObtenerCaracter(j));
      }
      /*Segundo triangulo*/
      for(int j=i-2; j>=0; j--){

        /*Obtener caracter en orden*/
        printf("%c", ObtenerCaracter(j));
      }
      /*Salto de linea*/
      printf("\n");
    }

    /* TRIÁNGULO INFERIOR */
    for(int i=lado-1; i>=1; i--) {

      for(int k=1; k<=lado-i; k++){

        /*Espacio en blanco para colocar el inicio rombo*/
        printf(" ");
      }
      /*Primer triangulo*/
      for(int j=0; j<i; j++){

        /*Obtener caracter en orden*/
        printf("%c", ObtenerCaracter(j));
      }
      /*Segundo triangulo*/
      for(int j=i-2; j>=0; j--){

        /*Obtener caracter en orden*/
        printf("%c", ObtenerCaracter(j));
      }
      /*Salto de linea*/
      printf("\n");
    }

  }
  return 0;

}
