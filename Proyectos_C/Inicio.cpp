// ============================================================
// Inicio
// Mostrar un mensaje por pantalla.
// ============================================================
// ------------------------------------------------------------
// COMENTARIO DE UNA SOLA LÍNEA
// Todo lo que aparece después de // no lo ejecuta el programa.
// ------------------------------------------------------------
/*
   COMENTARIO DE VARIAS LÍNEAS

   Podemos escribir varias líneas.
   El compilador ignora todo lo que esté entre:
   /*
   y
*/


#include <stdio.h>
// Incluimos la biblioteca stdio.h
// Necesaria para utilizar printf(), scanf(), etc.


int main() {

    printf("Hola Mundo\n");
    // printf() muestra información por pantalla.
    //
    // \n significa "salto de línea".
    //
    // Por tanto:
    //
    // printf("Hola Mundo\n");
    //
    // muestra:
    //
    // Hola Mundo


    return 0;
    // return 0 significa que el programa termina
    // correctamente.
}
