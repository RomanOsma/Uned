/************************************
* NOMBRE: #Angel#
* PRIMER APELLIDO: #Roman#
* SEGUNDO APELLIDO: #Osma#
* DNI: #76044046#
* EMAIL: #romanosma@gmail.com#
************************************/

#include <stdio.h>

/* Tipo enumerado */
typedef enum TipoDia {
    Lunes,
    Martes,
    Miercoles,
    Jueves,
    Viernes,
    Sabado,
    Domingo
};

/* Bisiesto*/
bool EsBisiesto(int anno) {
    return (anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0);
}

/* Número de días que tiene el mes*/
int DiasDelMes(int mes, int anno) {
    int dias;

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        dias = 30;
    }
    else if (mes == 2) {
        if (EsBisiesto(anno)) {
            dias = 29;
        } else {
            dias = 28;
        }
    }
    else {
        dias = 31;
    }

    return dias;
}

/* Numero de años bisiestos desde 1601 */
int ContarBisiestosAnteriores(int anno) {
    int limite;
    int bisiestosLimite;
    int bisiestosBase;

    limite = anno - 1;
    bisiestosLimite = (limite / 4) - (limite / 100) + (limite / 400);
    bisiestosBase = (1600 / 4) - (1600 / 100) + (1600 / 400);

    return bisiestosLimite - bisiestosBase;
}

/* Devuelve el día de la semana del día 1 del mes/año */
int PrimerDiaDelMes(int mes, int anno) {
    int annosTranscurridos;
    int bisiestos;
    long diasTotales;

    annosTranscurridos = anno - 1601;
    bisiestos = ContarBisiestosAnteriores(anno);
    diasTotales = (long(annosTranscurridos) * 365) + bisiestos;

    for (int m = 1; m < mes; m++) {
        diasTotales = diasTotales + DiasDelMes(m, anno);
    }

    return int(diasTotales % 7);
}

/* Nombre del mes en mayúsculas */
void ImprimirNombreMes(int mes) {
    if (mes == 1) {
        printf("ENERO");
    } else if (mes == 2) {
        printf("FEBRERO");
    } else if (mes == 3) {
        printf("MARZO");
    } else if (mes == 4) {
        printf("ABRIL");
    } else if (mes == 5) {
        printf("MAYO");
    } else if (mes == 6) {
        printf("JUNIO");
    } else if (mes == 7) {
        printf("JULIO");
    } else if (mes == 8) {
        printf("AGOSTO");
    } else if (mes == 9) {
        printf("SEPTIEMBRE");
    } else if (mes == 10) {
        printf("OCTUBRE");
    } else if (mes == 11) {
        printf("NOVIEMBRE");
    } else if (mes == 12) {
        printf("DICIEMBRE");
    }
}

/* Cabecera y calendario */
void ImprimirCalendario(int mes, int anno) {
    int diaInicio;
    int totalDias;
    int diaActual;
    int longitudNombre;
    int espaciosNombre;

    diaInicio = PrimerDiaDelMes(mes, anno);
    totalDias = DiasDelMes(mes, anno);
    diaActual = 1 - diaInicio;
    longitudNombre = 0;

    /* Cabecera mes y año */
    ImprimirNombreMes(mes);

    if (mes == 5) {
        longitudNombre = 4; /* MAYO */
    } else if (mes == 1 || mes == 3 || mes == 4 || mes == 6 || mes == 7) {
        longitudNombre = 5; /* ENERO, MARZO, ABRIL, JUNIO, JULIO */
    } else if (mes == 8) {
        longitudNombre = 6; /* AGOSTO */
    } else if (mes == 2 || mes == 10) {
        longitudNombre = 7; /* FEBRERO, OCTUBRE */
    } else if (mes == 11 || mes == 12) {
        longitudNombre = 9; /* NOVIEMBRE, DICIEMBRE */
    } else if (mes == 9) {
        longitudNombre = 10; /* SEPTIEMBRE */
    }
    espaciosNombre = 23 - longitudNombre;
    for (int e = 0; e < espaciosNombre; e++) {
        printf(" ");
    }
    printf("%4d\n", anno);

    /* Cabecera días de la semana */
    printf("===========================\n");
    printf("LU  MA  MI  JU  VI | SA  DO\n");
    printf("===========================\n");

    /* 3. Rejilla de días */
    while (diaActual <= totalDias) {
        for (int col = 0; col < 7; col++) {
            if (diaActual >= 1 && diaActual <= totalDias) {
                printf("%2d", diaActual);
            } else {
                printf(" .");
            }

            if (col == 4) {
                printf(" | ");
            } else if (col == 6) {
                printf("\n");
            } else {
                printf("  ");
            }

            diaActual++;
        }
    }
}

int main() {
    int mes;
    int anno;

    printf("¿Mes (1..12)?");
    scanf("%d", &mes);
    printf("¿Año (1601..3000)?");
    scanf("%d", &anno);

    if (mes >= 1 && mes <= 12 && anno >= 1601 && anno <= 3000) {
        printf("\n");
        ImprimirCalendario(mes, anno);
    }

    return 0;
}
