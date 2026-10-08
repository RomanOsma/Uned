/*********************************************************************
 * NOMBRE: #Tu Nombre Aquí#
 * PRIMER APELLIDO: #Tu Primer Apellido#
 * SEGUNDO APELLIDO: #Tu Segundo Apellido#
 * DNI: #12345678A#
 * EMAIL: #tu_correo@alumno.uned.es#
 *********************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// En C+-, primero debes definir el tipo para las cadenas de texto

typedef char t_cadena[25];
typedef char t_email[50];

int main() {

  t_cadena nombre="Angel2";
  t_cadena apellido1="Roman2";
  t_cadena apellido2="Osma2";
  int dni=76044045;
  t_email email="romanosma@gmail2.com";

//Ejemplo Pedir datos por teclado.

/**
  printf("Nombre: ");
  scanf("%s", nombre);

  printf("Primer apellido: ");
  scanf("%s", apellido1);

  printf("Segundo apellido: ");
  scanf("%s", apellido2);

  printf("DNI: ");
  // Es obligatorio el uso de '&' para leer tipos enteros (int)
  scanf("%d", &dni);

  printf("Email: ");
  scanf("%s", email);
**/

  printf("\n--- DATOS INTRODUCIDOS ---\n");

  printf("Nombre: %s\n", nombre);
  printf("Primer apellido: %s\n", apellido1);
  printf("Segundo apellido: %s\n", apellido2);
  printf("DNI: %d\n", dni);
  printf("Email: %s\n", email);

  return 0;
}
