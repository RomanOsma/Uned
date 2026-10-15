/*******************************************************
 * NOMBRE: #Nombre#
 * PRIMER APELLIDO: #PrimerApellido#
 * SEGUNDO APELLIDO: #SegundoApellido#
 * DNI: #12345678X#
 * EMAIL: #usuario@alumno.uned.es#
 *******************************************************/

#include <stdio.h>

/* =========================================================================
 * CONSTANTES GLOBALES Y TIPOS ENUMERADOS
 * ========================================================================= */

const int MaxEdificios = 20;
const int MaxPlantas = 5;
const int MaxReservas = 100;
const int MaxCadenaNombre = 21;
const int MaxCadenaDir = 41;

/* Tipo enumerado para las categorias de edificio y precio (BNF C+-) */
typedef enum TipoCategoria {
    CatSuperior,
    CatMedia,
    CatBasica,
    CatNinguna
};

/* Tipo enumerado para los dias de la semana (BNF C+-) */
typedef enum TipoDia {
    Lunes,
    Martes,
    Miercoles,
    Jueves,
    Viernes,
    Sabado,
    Domingo
};

/* =========================================================================
 * ESTRUCTURAS DE DATOS (TADs Y REGISTROS)
 * ========================================================================= */

/* Definiciones de tipos cadena y vectores con typedef (BNF C+-) */
typedef char TipoCadenaNombre[MaxCadenaNombre];
typedef char TipoCadenaDir[MaxCadenaDir];

/* Registro para almacenar una Fecha */
typedef struct TipoFecha {
    int dia;
    int mes;
    int anno;
};

/* Registro para precios diarios por numero de habitaciones (1 a 4 hab.) */
typedef struct TipoPreciosCategoria {
    int precio1Hab;
    int precio2Hab;
    int precio3Hab;
    int precio4Hab;
};

/* Tabla global de precios para las tres categorias */
typedef struct TipoTablaPrecios {
    TipoPreciosCategoria superior;
    TipoPreciosCategoria media;
    TipoPreciosCategoria basica;
};

/* Registro de Reserva */
typedef struct TipoReserva {
    int idReserva;
    int idEdificio;
    int planta;
    char letraApartamento;
    int numHabitaciones;
    TipoFecha fechaEntrada;
    TipoFecha fechaSalida;
    int precioTotal;
    bool activa;
};

typedef TipoReserva TipoVectorReservas[MaxReservas];

/* Estructura para configurar una Planta */
typedef struct TipoPlanta {
    int numHabitaciones;
    int numApartamentos;
};

typedef TipoPlanta TipoVectorPlantas[MaxPlantas + 1];

/* Estructura de Edificio */
typedef struct TipoEdificio {
    int id;
    TipoCadenaNombre nombre;
    TipoCadenaDir direccion;
    TipoCategoria categoria;
    TipoVectorPlantas plantas;
    bool existe;
};

typedef TipoEdificio TipoVectorEdificios[MaxEdificios + 1];

/* Lista de Reservas del Sistema */
typedef struct TipoListaReservas {
    TipoVectorReservas elementos;
    int total;
};

/* Estructura para opciones de busqueda de apartamento */
typedef struct TipoOpcion {
    int idEdificio;
    int planta;
    char letra;
};

typedef TipoOpcion TipoVectorOpciones[50];

/* =========================================================================
 * SUBPROGRAMAS AUXILIARES DE LECTURA ROBUSTA DE DATOS EN C+-
 * ========================================================================= */

/* Lee un entero y limpia los caracteres sobrantes de la linea */
void LeerEntero(int &val) {
    char c;
    int leidos;

    leidos = scanf("%d", &val);
    if (leidos == 0) {
        val = 0;
    }

    c = ' ';
    while (c != '\n' && c != '\r') {
        scanf("%c", &c);
    }
}

/* Lee un caracter unico y descarta los caracteres sobrantes de la linea */
char LeerCaracter() {
    char c;
    char temp;

    scanf(" %c", &c);

    temp = c;
    while (temp != '\n' && temp != '\r') {
        scanf("%c", &temp);
    }

    return c;
}

/* Lee una cadena de texto respetando espacios y limpiando el buffer */
void LeerCadena(TipoCadenaDir s, int maxLen) {
    char c;
    int i;

    i = 0;
    c = ' ';

    while (c == '\n' || c == '\r' || c == ' ') {
        scanf("%c", &c);
    }

    while (c != '\n' && c != '\r' && i < maxLen - 1) {
        s[i] = c;
        i++;
        scanf("%c", &c);
    }
    s[i] = '\0';

    while (c != '\n' && c != '\r') {
        scanf("%c", &c);
    }
}

/* Lee una categoria textual y limpia el resto de la palabra/linea */
TipoCategoria LeerCategoriaTextual() {
    char c;
    char temp;
    TipoCategoria res;

    res = CatNinguna;
    scanf(" %c", &c);

    if (c == 'S' || c == 's') {
        res = CatSuperior;
    } else if (c == 'M' || c == 'm') {
        res = CatMedia;
    } else if (c == 'B' || c == 'b') {
        res = CatBasica;
    }

    temp = c;
    while (temp != '\n' && temp != '\r') {
        scanf("%c", &temp);
    }

    return res;
}

/* =========================================================================
 * SUBPROGRAMAS DE CALCULO DE FECHAS Y CALENDARIO
 * ========================================================================= */

/* Determina si un ano es bisiesto */
bool EsBisiesto(int anno) {
    return (anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0);
}

/* Devuelve el numero de dias que tiene un mes */
int DiasDelMes(int mes, int anno) {
    int dias;

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        dias = 30;
    } else if (mes == 2) {
        if (EsBisiesto(anno)) {
            dias = 29;
        } else {
            dias = 28;
        }
    } else {
        dias = 31;
    }

    return dias;
}

/* Cuenta anos bisiestos anteriores a un ano dado desde 1601 */
int ContarBisiestosAnteriores(int anno) {
    int limite;
    int bisiestosLimite;
    int bisiestosBase;

    limite = anno - 1;
    bisiestosLimite = (limite / 4) - (limite / 100) + (limite / 400);
    bisiestosBase = (1600 / 4) - (1600 / 100) + (1600 / 400);

    return bisiestosLimite - bisiestosBase;
}

/* Devuelve el dia de la semana (0 = Lunes ... 6 = Domingo) del 1 de un mes/ano */
int PrimerDiaDelMes(int mes, int anno) {
    int annosTranscurridos;
    int bisiestos;
    int diasTotales;

    annosTranscurridos = anno - 1601;
    bisiestos = ContarBisiestosAnteriores(anno);
    diasTotales = (annosTranscurridos * 365) + bisiestos;

    for (int m = 1; m < mes; m++) {
        diasTotales = diasTotales + DiasDelMes(m, anno);
    }

    return (diasTotales % 7);
}

/* Convierte fecha a numero de dias acumulados desde 1/1/1601 para comparar intervalos */
int DiasDesdeInicio(int dia, int mes, int anno) {
    int annosTranscurridos;
    int bisiestos;
    int totalDias;

    annosTranscurridos = anno - 1601;
    bisiestos = ContarBisiestosAnteriores(anno);
    totalDias = (annosTranscurridos * 365) + bisiestos;

    for (int m = 1; m < mes; m++) {
        totalDias = totalDias + DiasDelMes(m, anno);
    }

    totalDias = totalDias + (dia - 1);

    return totalDias;
}

/* Comprueba si dos intervalos de fecha se solapan [ent1, sal1) y [ent2, sal2) */
bool HaySolapamiento(TipoFecha ent1, TipoFecha sal1, TipoFecha ent2, TipoFecha sal2) {
    int inicio1;
    int fin1;
    int inicio2;
    int fin2;

    inicio1 = DiasDesdeInicio(ent1.dia, ent1.mes, ent1.anno);
    fin1 = DiasDesdeInicio(sal1.dia, sal1.mes, sal1.anno);
    inicio2 = DiasDesdeInicio(ent2.dia, ent2.mes, ent2.anno);
    fin2 = DiasDesdeInicio(sal2.dia, sal2.mes, sal2.anno);

    return (inicio1 < fin2) && (inicio2 < fin1);
}

/* Imprime el nombre del mes */
void ImprimirNombreMes(int mes) {
    if (mes == 1) {
        printf("Enero");
    } else if (mes == 2) {
        printf("Febrero");
    } else if (mes == 3) {
        printf("Marzo");
    } else if (mes == 4) {
        printf("Abril");
    } else if (mes == 5) {
        printf("Mayo");
    } else if (mes == 6) {
        printf("Junio");
    } else if (mes == 7) {
        printf("Julio");
    } else if (mes == 8) {
        printf("Agosto");
    } else if (mes == 9) {
        printf("Septiembre");
    } else if (mes == 10) {
        printf("Octubre");
    } else if (mes == 11) {
        printf("Noviembre");
    } else if (mes == 12) {
        printf("Diciembre");
    }
}

/* Imprime la categoria en texto */
void ImprimirCategoriaTextual(TipoCategoria cat) {
    if (cat == CatSuperior) {
        printf("Superior");
    } else if (cat == CatMedia) {
        printf("Media");
    } else if (cat == CatBasica) {
        printf("Basica");
    }
}

/* Obtiene numero de apartamentos segun numero de habitaciones */
int ObtenerNumApartamentos(int numHabitaciones) {
    if (numHabitaciones == 1) {
        return 8;
    } else if (numHabitaciones == 2) {
        return 4;
    } else if (numHabitaciones == 3) {
        return 3;
    } else if (numHabitaciones == 4) {
        return 2;
    }
    return 0;
}

/* Convierte indice 0..7 a letra 'A'..'H' */
char IndiceALetra(int idx) {
    return char('A' + idx);
}

/* =========================================================================
 * INICIALIZACION DE DATOS BASE (SOPORTE DE PRUEBAS)
 * ========================================================================= */

void InicializarPreciosBase(TipoTablaPrecios &precios) {
    /* Categoria Superior */
    precios.superior.precio1Hab = 200;
    precios.superior.precio2Hab = 400;
    precios.superior.precio3Hab = 600;
    precios.superior.precio4Hab = 800;

    /* Categoria Media */
    precios.media.precio1Hab = 150;
    precios.media.precio2Hab = 300;
    precios.media.precio3Hab = 450;
    precios.media.precio4Hab = 600;

    /* Categoria Basica */
    precios.basica.precio1Hab = 75;
    precios.basica.precio2Hab = 150;
    precios.basica.precio3Hab = 225;
    precios.basica.precio4Hab = 300;
}

void InicializarDatosEjemplo(TipoVectorEdificios edificios, TipoListaReservas &reservas) {
    /* Edificio 9: Caleruega (Categoria Basica) */
    edificios[9].id = 9;
    edificios[9].nombre[0] = 'C'; edificios[9].nombre[1] = 'a'; edificios[9].nombre[2] = 'l';
    edificios[9].nombre[3] = 'e'; edificios[9].nombre[4] = 'r'; edificios[9].nombre[5] = 'u';
    edificios[9].nombre[6] = 'e'; edificios[9].nombre[7] = 'g'; edificios[9].nombre[8] = 'a';
    edificios[9].nombre[9] = '\0';
    edificios[9].existe = true;
    edificios[9].categoria = CatBasica;
    edificios[9].plantas[1].numHabitaciones = 2; edificios[9].plantas[1].numApartamentos = 4;
    edificios[9].plantas[2].numHabitaciones = 1; edificios[9].plantas[2].numApartamentos = 8;
    edificios[9].plantas[3].numHabitaciones = 1; edificios[9].plantas[3].numApartamentos = 8;
    edificios[9].plantas[4].numHabitaciones = 2; edificios[9].plantas[4].numApartamentos = 4;
    edificios[9].plantas[5].numHabitaciones = 3; edificios[9].plantas[5].numApartamentos = 3;

    /* Edificio 1: Bravo Murillo (Categoria Basica) */
    edificios[1].id = 1;
    edificios[1].nombre[0] = 'B'; edificios[1].nombre[1] = 'r'; edificios[1].nombre[2] = 'a';
    edificios[1].nombre[3] = 'v'; edificios[1].nombre[4] = 'o'; edificios[1].nombre[5] = ' ';
    edificios[1].nombre[6] = 'M'; edificios[1].nombre[7] = 'u'; edificios[1].nombre[8] = 'r';
    edificios[1].nombre[9] = 'i'; edificios[1].nombre[10] = 'l'; edificios[1].nombre[11] = 'l';
    edificios[1].nombre[12] = 'o'; edificios[1].nombre[13] = '\0';
    edificios[1].existe = true;
    edificios[1].categoria = CatBasica;
    edificios[1].plantas[1].numHabitaciones = 3; edificios[1].plantas[1].numApartamentos = 3;
    edificios[1].plantas[2].numHabitaciones = 2; edificios[1].plantas[2].numApartamentos = 4;
    edificios[1].plantas[3].numHabitaciones = 1; edificios[1].plantas[3].numApartamentos = 8;
    edificios[1].plantas[4].numHabitaciones = 1; edificios[1].plantas[4].numApartamentos = 8;
    edificios[1].plantas[5].numHabitaciones = 4; edificios[1].plantas[5].numApartamentos = 2;

    /* Reservas preexistentes de prueba */
    reservas.total = 1;
    reservas.elementos[0].idReserva = 1;
    reservas.elementos[0].idEdificio = 9;
    reservas.elementos[0].planta = 5;
    reservas.elementos[0].letraApartamento = 'C';
    reservas.elementos[0].numHabitaciones = 3;
    reservas.elementos[0].fechaEntrada.dia = 1;
    reservas.elementos[0].fechaEntrada.mes = 10;
    reservas.elementos[0].fechaEntrada.anno = 2026;
    reservas.elementos[0].fechaSalida.dia = 15;
    reservas.elementos[0].fechaSalida.mes = 10;
    reservas.elementos[0].fechaSalida.anno = 2026;
    reservas.elementos[0].precioTotal = 3150;
    reservas.elementos[0].activa = true;
}

/* =========================================================================
 * FUNCIONALIDADES DEL MENU PRINCIPAL
 * ========================================================================= */

/* OPCION E: Editar Edificio */
void EditarEdificio(TipoVectorEdificios edificios, TipoListaReservas &reservas) {
    int idEdif;
    int habs;
    char respuesta;
    TipoEdificio temp;

    printf("\nEditar edificio:\n\n");
    printf("    Identificador (numero entre 1 y 20)? ");
    LeerEntero(idEdif);

    if (idEdif < 1 || idEdif > 20) {
        printf("Identificador de edificio incorrecto.\n");
    } else {
        temp.id = idEdif;
        printf("    Nombre (entre 1 y 20 caracteres)? ");
        LeerCadena(temp.nombre, MaxCadenaNombre);

        for (int p = 1; p <= MaxPlantas; p++) {
            printf("    Configuracion de planta %d? ", p);
            LeerEntero(habs);
            temp.plantas[p].numHabitaciones = habs;
            temp.plantas[p].numApartamentos = ObtenerNumApartamentos(habs);
        }

        printf("    Categoria apartamentos del edificio (Superior, Media, Basica)? ");
        temp.categoria = LeerCategoriaTextual();

        printf("    Direccion (entre 1 y 40 caracteres)? ");
        LeerCadena(temp.direccion, MaxCadenaDir);

        printf("\nLos datos introducidos son:\n");
        printf("    Edificio %d. %s - Categoria: ", temp.id, temp.nombre);
        ImprimirCategoriaTextual(temp.categoria);
        printf("\n");

        for (int p = 1; p <= MaxPlantas; p++) {
            printf("    Planta %d.  %d habitaciones por apartamento. %d apartamentos\n",
                   p, temp.plantas[p].numHabitaciones, temp.plantas[p].numApartamentos);
        }

        printf("\nIMPORTANTE: Esta opcion borra los datos anteriores.\n");
        printf("Son correctos los nuevos datos (S/N)? ");
        respuesta = LeerCaracter();

        if (respuesta == 'S' || respuesta == 's') {
            temp.existe = true;
            edificios[idEdif] = temp;

            for (int r = 0; r < reservas.total; r++) {
                if (reservas.elementos[r].idEdificio == idEdif) {
                    reservas.elementos[r].activa = false;
                }
            }
            printf("Edificio actualizado correctamente.\n");
        } else {
            printf("Operacion cancelada.\n");
        }
    }
}

/* OPCION P: Editar Precios */
void EditarPrecios(TipoTablaPrecios &precios) {
    TipoCategoria cat;
    int p1;
    int p2;
    int p3;
    int p4;
    int act1;
    int act2;
    int act3;
    int act4;
    char respuesta;
    bool valido;

    valido = true;

    printf("\nEditar precios:\n\n");
    printf("    Categoria a modificar (Superior, Media, Basica)? ");
    cat = LeerCategoriaTextual();

    if (cat == CatSuperior) {
        act1 = precios.superior.precio1Hab;
        act2 = precios.superior.precio2Hab;
        act3 = precios.superior.precio3Hab;
        act4 = precios.superior.precio4Hab;
    } else if (cat == CatMedia) {
        act1 = precios.media.precio1Hab;
        act2 = precios.media.precio2Hab;
        act3 = precios.media.precio3Hab;
        act4 = precios.media.precio4Hab;
    } else if (cat == CatBasica) {
        act1 = precios.basica.precio1Hab;
        act2 = precios.basica.precio2Hab;
        act3 = precios.basica.precio3Hab;
        act4 = precios.basica.precio4Hab;
    } else {
        printf("Categoria no valida.\n");
        valido = false;
    }

    if (valido) {
        printf("    El precio actual de la categoria es: %d euros para 1 hab.\n", act1);
        printf("    El precio actual de la categoria es: %d euros para 2 hab.\n", act2);
        printf("    El precio actual de la categoria es: %d euros para 3 hab.\n", act3);
        printf("    El precio actual de la categoria es: %d euros para 4 hab.\n", act4);

        printf("Introduzca los nuevos precios:\n");
        printf("    "); ImprimirCategoriaTextual(cat); printf(" 1 hab. : "); LeerEntero(p1);
        printf("    "); ImprimirCategoriaTextual(cat); printf(" 2 hab. : "); LeerEntero(p2);
        printf("    "); ImprimirCategoriaTextual(cat); printf(" 3 hab. : "); LeerEntero(p3);
        printf("    "); ImprimirCategoriaTextual(cat); printf(" 4 hab. : "); LeerEntero(p4);

        /* Comprobar coherencia */
        if (cat == CatSuperior) {
            if (p1 <= precios.media.precio1Hab || p2 <= precios.media.precio2Hab ||
                p3 <= precios.media.precio3Hab || p4 <= precios.media.precio4Hab) {
                printf("\nERROR: Los precios de categoria Superior deben ser mayores que los de Media.\n");
                valido = false;
            }
        } else if (cat == CatMedia) {
            if (p1 >= precios.superior.precio1Hab || p2 >= precios.superior.precio2Hab ||
                p3 >= precios.superior.precio3Hab || p4 >= precios.superior.precio4Hab ||
                p1 <= precios.basica.precio1Hab || p2 <= precios.basica.precio2Hab ||
                p3 <= precios.basica.precio3Hab || p4 <= precios.basica.precio4Hab) {
                printf("\nERROR: Los precios de categoria Media deben estar entre Superior y Basica.\n");
                valido = false;
            }
        } else if (cat == CatBasica) {
            if (p1 >= precios.media.precio1Hab || p2 >= precios.media.precio2Hab ||
                p3 >= precios.media.precio3Hab || p4 >= precios.media.precio4Hab) {
                printf("\nERROR: Los precios de categoria Basica deben ser menores que los de Media.\n");
                valido = false;
            }
        }

        if (valido) {
            printf("\nLos nuevos valores de precios para la categoria ");
            ImprimirCategoriaTextual(cat);
            printf(":\n");
            printf("    Apartamento 1 habitacion: %d euros/dia\n", p1);
            printf("    Apartamento 2 habitaciones: %d euros/dia\n", p2);
            printf("    Apartamento 3 habitaciones: %d euros/dia\n", p3);
            printf("    Apartamento 4 habitaciones: %d euros/dia\n", p4);

            printf("\nSon correctos los nuevos datos (S/N)? ");
            respuesta = LeerCaracter();

            if (respuesta == 'S' || respuesta == 's') {
                if (cat == CatSuperior) {
                    precios.superior.precio1Hab = p1;
                    precios.superior.precio2Hab = p2;
                    precios.superior.precio3Hab = p3;
                    precios.superior.precio4Hab = p4;
                } else if (cat == CatMedia) {
                    precios.media.precio1Hab = p1;
                    precios.media.precio2Hab = p2;
                    precios.media.precio3Hab = p3;
                    precios.media.precio4Hab = p4;
                } else if (cat == CatBasica) {
                    precios.basica.precio1Hab = p1;
                    precios.basica.precio2Hab = p2;
                    precios.basica.precio3Hab = p3;
                    precios.basica.precio4Hab = p4;
                }
                printf("Precios actualizados correctamente.\n");
            } else {
                printf("Operacion cancelada.\n");
            }
        }
    }
}

/* Obtiene el precio por dia */
int ObtenerPrecioDiario(TipoTablaPrecios precios, TipoCategoria cat, int habs) {
    int precio;
    precio = 0;

    if (cat == CatSuperior) {
        if (habs == 1) { precio = precios.superior.precio1Hab; }
        else if (habs == 2) { precio = precios.superior.precio2Hab; }
        else if (habs == 3) { precio = precios.superior.precio3Hab; }
        else if (habs == 4) { precio = precios.superior.precio4Hab; }
    } else if (cat == CatMedia) {
        if (habs == 1) { precio = precios.media.precio1Hab; }
        else if (habs == 2) { precio = precios.media.precio2Hab; }
        else if (habs == 3) { precio = precios.media.precio3Hab; }
        else if (habs == 4) { precio = precios.media.precio4Hab; }
    } else if (cat == CatBasica) {
        if (habs == 1) { precio = precios.basica.precio1Hab; }
        else if (habs == 2) { precio = precios.basica.precio2Hab; }
        else if (habs == 3) { precio = precios.basica.precio3Hab; }
        else if (habs == 4) { precio = precios.basica.precio4Hab; }
    }

    return precio;
}

/* OPCION R: Reservar Apartamento */
void ReservarApartamento(TipoVectorEdificios edificios, TipoTablaPrecios precios, TipoListaReservas &reservas) {
    TipoCategoria catBuscada;
    int habsBuscadas;
    TipoFecha fEntrada;
    TipoFecha fSalida;
    char respuesta;
    int numDias;
    int precioDiario;
    int precioTotal;
    TipoVectorOpciones opciones;
    int totalOpciones;
    int eleccion;
    int idxOpt;
    int posRes;
    int aptsPlanta;
    char letraApt;
    bool ocupado;

    totalOpciones = 0;
    eleccion = 0;

    printf("\nReservar apartamento:\n\n");
    printf("    Elija la categoria a reservar (Superior/Media/Basica): ");
    catBuscada = LeerCategoriaTextual();

    printf("    Elija el tipo de apartamento (1hab./2hab./3hab./4hab.): ");
    LeerEntero(habsBuscadas);

    printf("    Datos reserva: Dia entrada? "); LeerEntero(fEntrada.dia);
    printf("    Datos reserva: Mes entrada? "); LeerEntero(fEntrada.mes);
    printf("    Datos reserva: Ano entrada? "); LeerEntero(fEntrada.anno);

    printf("    Datos reserva: Dia salida? "); LeerEntero(fSalida.dia);
    printf("    Datos reserva: Mes salida? "); LeerEntero(fSalida.mes);
    printf("    Datos reserva: Ano salida? "); LeerEntero(fSalida.anno);

    printf("\nDatos de la Reserva buscada:\n");
    printf("    Apartamento de %d habitaciones de categoria ", habsBuscadas);
    ImprimirCategoriaTextual(catBuscada);
    printf(" del %d/%d/%d al %d/%d/%d\n\n",
           fEntrada.dia, fEntrada.mes, fEntrada.anno,
           fSalida.dia, fSalida.mes, fSalida.anno);

    printf("Son correctos los datos de la reserva (S/N)? ");
    respuesta = LeerCaracter();

    if (respuesta == 'S' || respuesta == 's') {
        numDias = DiasDesdeInicio(fSalida.dia, fSalida.mes, fSalida.anno) -
                  DiasDesdeInicio(fEntrada.dia, fEntrada.mes, fEntrada.anno);

        if (numDias <= 0) {
            printf("Fechas de reserva no validas.\n");
        } else {
            precioDiario = ObtenerPrecioDiario(precios, catBuscada, habsBuscadas);
            precioTotal = numDias * precioDiario;

            totalOpciones = 0;
            for (int e = 1; e <= MaxEdificios; e++) {
                if (edificios[e].existe && edificios[e].categoria == catBuscada) {
                    for (int p = 1; p <= MaxPlantas; p++) {
                        if (edificios[e].plantas[p].numHabitaciones == habsBuscadas) {
                            aptsPlanta = edificios[e].plantas[p].numApartamentos;
                            for (int a = 0; a < aptsPlanta; a++) {
                                letraApt = IndiceALetra(a);
                                ocupado = false;

                                for (int r = 0; r < reservas.total; r++) {
                                    if (reservas.elementos[r].activa &&
                                        reservas.elementos[r].idEdificio == e &&
                                        reservas.elementos[r].planta == p &&
                                        reservas.elementos[r].letraApartamento == letraApt) {

                                        if (HaySolapamiento(fEntrada, fSalida,
                                                             reservas.elementos[r].fechaEntrada,
                                                             reservas.elementos[r].fechaSalida)) {
                                            ocupado = true;
                                        }
                                    }
                                }

                                if (!ocupado) {
                                    opciones[totalOpciones].idEdificio = e;
                                    opciones[totalOpciones].planta = p;
                                    opciones[totalOpciones].letra = letraApt;
                                    totalOpciones++;
                                }
                            }
                        }
                    }
                }
            }

            if (totalOpciones == 0) {
                printf("\nNo hay disponibilidad de alojamiento para las fechas y caracteristicas indicadas.\n");
            } else {
                printf("\nLos apartamentos disponibles son:\n");
                for (int o = 0; o < totalOpciones; o++) {
                    printf("    Opcion %d- Apartamento %c - Planta %d - Edificio %s\n",
                           o + 1, opciones[o].letra, opciones[o].planta,
                           edificios[opciones[o].idEdificio].nombre);
                }

                printf("Y el precio total es:\n");
                printf("    %d dias a %d euros/dia - %d euros\n\n", numDias, precioDiario, precioTotal);

                printf("Seleccione una opcion entre las disponibles o 0 si desea volver a iniciar la reserva: ");
                LeerEntero(eleccion);

                if (eleccion >= 1 && eleccion <= totalOpciones) {
                    idxOpt = eleccion - 1;
                    printf("\nReserva seleccionada:\n");
                    printf("    Edif. %s. Planta %d - Apartamento %c - %d habitaciones\n",
                           edificios[opciones[idxOpt].idEdificio].nombre,
                           opciones[idxOpt].planta, opciones[idxOpt].letra, habsBuscadas);
                    printf("    Fecha entrada: %d/%d/%d\n", fEntrada.dia, fEntrada.mes, fEntrada.anno);
                    printf("    Fecha salida: %d/%d/%d\n", fSalida.dia, fSalida.mes, fSalida.anno);
                    printf("    Precio Reserva: %d euros\n\n", precioTotal);

                    printf("Confirms la reserva (S/N)? ");
                    respuesta = LeerCaracter();

                    if (respuesta == 'S' || respuesta == 's') {
                        posRes = reservas.total;
                        reservas.elementos[posRes].idReserva = posRes + 1;
                        reservas.elementos[posRes].idEdificio = opciones[idxOpt].idEdificio;
                        reservas.elementos[posRes].planta = opciones[idxOpt].planta;
                        reservas.elementos[posRes].letraApartamento = opciones[idxOpt].letra;
                        reservas.elementos[posRes].numHabitaciones = habsBuscadas;
                        reservas.elementos[posRes].fechaEntrada = fEntrada;
                        reservas.elementos[posRes].fechaSalida = fSalida;
                        reservas.elementos[posRes].precioTotal = precioTotal;
                        reservas.elementos[posRes].activa = true;

                        reservas.total++;
                        printf("    Reserva confirmada.\n");
                    } else {
                        printf("Reserva cancelada.\n");
                    }
                } else {
                    printf("Reserva no realizada.\n");
                }
            }
        }
    } else {
        printf("Busqueda cancelada.\n");
    }
}

/* OPCION L: Listar reservas de edificio */
void ListarReservasEdificio(TipoVectorEdificios edificios, TipoListaReservas reservas) {
    int idEdif;
    int mes;
    int anno;
    int habs;
    bool hayReservasEnPlanta;

    printf("\nListar reservas de edificio:\n\n");
    printf("    Identificador del edificio? "); LeerEntero(idEdif);
    printf("    Mes Reservas? "); LeerEntero(mes);
    printf("    Ano Reservas? "); LeerEntero(anno);

    if (idEdif < 1 || idEdif > 20 || !edificios[idEdif].existe) {
        printf("Edificio no registrado.\n");
    } else {
        printf("\nEl edificio %s - categoria ", edificios[idEdif].nombre);
        ImprimirCategoriaTextual(edificios[idEdif].categoria);
        printf(" tiene las siguientes reservas para el mes %d del ano %d:\n\n", mes, anno);

        for (int p = 1; p <= MaxPlantas; p++) {
            habs = edificios[idEdif].plantas[p].numHabitaciones;
            printf("Planta %d. Apartamentos %d hab.\n", p, habs);

            hayReservasEnPlanta = false;
            for (int r = 0; r < reservas.total; r++) {
                if (reservas.elementos[r].activa &&
                    reservas.elementos[r].idEdificio == idEdif &&
                    reservas.elementos[r].planta == p &&
                    reservas.elementos[r].fechaEntrada.mes == mes &&
                    reservas.elementos[r].fechaEntrada.anno == anno) {

                    hayReservasEnPlanta = true;
                    printf("    Apartamento %c - Entrada %d/%d/%d al %d/%d/%d\n",
                           reservas.elementos[r].letraApartamento,
                           reservas.elementos[r].fechaEntrada.dia,
                           reservas.elementos[r].fechaEntrada.mes,
                           reservas.elementos[r].fechaEntrada.anno,
                           reservas.elementos[r].fechaSalida.dia,
                           reservas.elementos[r].fechaSalida.mes,
                           reservas.elementos[r].fechaSalida.anno);
                }
            }

            if (!hayReservasEnPlanta) {
                printf("    Sin reservas\n");
            }
            printf("\n");
        }
    }
}

/* OPCION M: Listar calendario mensual de planta */
void ListarCalendarioPlanta(TipoVectorEdificios edificios, TipoListaReservas reservas) {
    int idEdif;
    int planta;
    int mes;
    int anno;
    int habs;
    int numApts;
    int diaInicio;
    int totalDias;
    int col;
    int ocupados;
    int inicio;
    int fin;
    int hoy;
    char respuesta;
    char letra;

    do {
        printf("\nListar calendario mensual de planta:\n");
        printf("    Identificador del edificio? "); LeerEntero(idEdif);
        printf("    Planta numero? "); LeerEntero(planta);
        printf("    Seleccion Mes? "); LeerEntero(mes);
        printf("    Seleccion Ano? "); LeerEntero(anno);

        if (idEdif < 1 || idEdif > 20 || !edificios[idEdif].existe || planta < 1 || planta > 5) {
            printf("Edificio o planta no valida.\n");
        } else {
            habs = edificios[idEdif].plantas[planta].numHabitaciones;
            numApts = edificios[idEdif].plantas[planta].numApartamentos;

            printf("\n\n          Ocupacion Planta: %d -  Edificio %s\n", planta, edificios[idEdif].nombre);
            printf("             Apartamentos de %d habitacion\n\n", habs);

            printf("          "); ImprimirNombreMes(mes); printf("         %4d\n\n", anno);
            printf("          L  M  X  J  V  S  D\n");
            printf("          ---------------------\n");

            diaInicio = PrimerDiaDelMes(mes, anno);
            totalDias = DiasDelMes(mes, anno);
            col = 0;

            printf("          ");
            for (int i = 0; i < diaInicio; i++) {
                printf("   ");
                col++;
            }

            for (int d = 1; d <= totalDias; d++) {
                ocupados = 0;
                for (int a = 0; a < numApts; a++) {
                    letra = IndiceALetra(a);
                    for (int r = 0; r < reservas.total; r++) {
                        if (reservas.elementos[r].activa &&
                            reservas.elementos[r].idEdificio == idEdif &&
                            reservas.elementos[r].planta == planta &&
                            reservas.elementos[r].letraApartamento == letra) {

                            inicio = DiasDesdeInicio(reservas.elementos[r].fechaEntrada.dia,
                                                     reservas.elementos[r].fechaEntrada.mes,
                                                     reservas.elementos[r].fechaEntrada.anno);
                            fin = DiasDesdeInicio(reservas.elementos[r].fechaSalida.dia,
                                                  reservas.elementos[r].fechaSalida.mes,
                                                  reservas.elementos[r].fechaSalida.anno);
                            hoy = DiasDesdeInicio(d, mes, anno);

                            if (hoy >= inicio && hoy < fin) {
                                ocupados++;
                            }
                        }
                    }
                }

                printf("%02d ", ocupados);
                col++;

                if (col == 7) {
                    printf("\n          ");
                    col = 0;
                }
            }
            printf("\n\n");
        }

        printf("Mostrar otro mes (S/N)? ");
        respuesta = LeerCaracter();

    } while (respuesta == 'S' || respuesta == 's');
}

/* =========================================================================
 * MENU PRINCIPAL
 * ========================================================================= */

void MostrarMenu() {
    printf("\nGestanUNED: Gestion de alojamientos\n\n");
    printf("    Editar edificio                         (Pulsar E)\n");
    printf("    Editar precios                          (Pulsar P)\n");
    printf("    Reservar apartamento                    (Pulsar R)\n");
    printf("    Listar reservas de edificio             (Pulsar L)\n");
    printf("    Listar calendario mensual de planta     (Pulsar M)\n");
    printf("    Salir                                   (Pulsar S)\n\n");
    printf("Teclear una opcion valida (E|P|R|L|M|S)? ");
}

int main() {
    TipoVectorEdificios edificios;
    TipoTablaPrecios precios;
    TipoListaReservas reservas;
    char opcion;
    bool salir;

    salir = false;

    for (int i = 1; i <= MaxEdificios; i++) {
        edificios[i].existe = false;
    }
    reservas.total = 0;

    InicializarPreciosBase(precios);
    InicializarDatosEjemplo(edificios, reservas);

    while (!salir) {
        MostrarMenu();
        opcion = LeerCaracter();

        switch (opcion) {
            case 'E':
            case 'e':
                EditarEdificio(edificios, reservas);
                break;

            case 'P':
            case 'p':
                EditarPrecios(precios);
                break;

            case 'R':
            case 'r':
                ReservarApartamento(edificios, precios, reservas);
                break;

            case 'L':
            case 'l':
                ListarReservasEdificio(edificios, reservas);
                break;

            case 'M':
            case 'm':
                ListarCalendarioPlanta(edificios, reservas);
                break;

            case 'S':
            case 's':
                salir = true;
                printf("\nGracias por utilizar GestanUNED.\n");
                break;

            default:
                printf("\nOpcion no valida. Intentelo de nuevo.\n");
        }
    }

    return 0;
}
