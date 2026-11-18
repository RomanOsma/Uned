#include <stdio.h>

int main()

{

  int operando1, operando2, resultado;

  char operacion, salir;

  salir='N';

  while(salir!='S')
  {

    printf("Introduce operando 1:");

    scanf("%d", &operando1);

    printf("Introduce operando 2:");

    scanf("%d", &operando2);

    printf("Introduce operacion a realizar (+,-,*,/,#):\n");

    scanf("%c", &operacion);
    scanf("%c", &operacion);

    if (operacion == '+' )

    {

      resultado=operando1+operando2;

      printf("El resultado de %d %c %d es: %d\n", operando1, operacion, operando2, resultado);

    }

    else

    {

      if (operacion == '-' )

      {

        resultado=operando1-operando2;

        printf("El resultado de %d %c %d es: %d\n", operando1, operacion, operando2, resultado);

      }

      else

      {

        if (operacion == '*' )

        {

          resultado=operando1*operando2;

          printf("El resultado de %d %c %d es: %d\n", operando1, operacion, operando2, resultado);

        }

        else

        {

          if (operacion == '/' )

          {

            resultado=operando1/operando2;

            printf("El resultado de %d %c %d es: %d\n", operando1, operacion, operando2, resultado);

          }

          else

          {

            if (operacion == '#')

            {

              printf("Tabla de Multiplicar del %d: \n", operando1);

              for (int i=1;i<=operando2;i++)

              {

                resultado=operando1*i;

                if (((resultado % 2) == 0) && (resultado > 30))

                {

                  printf("%d * %d = %d\n", operando1, i, resultado);

                }

              }

            }

            else

            {

              printf("Operacion desconocida: %c\n", operacion);

            }

          }

        }

      }

    }
    printf("\nQuieres salir: Pulse S para salir.\n");
    scanf("%c", &salir);
    scanf("%c", &salir);
  }
}

