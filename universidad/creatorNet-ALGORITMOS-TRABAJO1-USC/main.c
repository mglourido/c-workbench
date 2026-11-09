#include "creatornet.h"
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

void MenuOpcionesPrincipal(TGRAFO CreatorNet) {
  char opcion = ' ';
  while (opcion != 's') {
    printf("\n\na. Anhadir creador/a\n");
    printf("e. Eliminar creador/a\n");
    printf("c. Crear colaboracion\n");
    printf("b. Eliminar colaboracion\n");
    printf("i. Mostrar creadores/as y colaboraciones\n");
    printf("l. Consultar colaboraciones de un/a creador/a\n");
    printf("T. Mostrar estadisticas\n");
    printf("P. Red de colaboracion de coste minimo.\n");
    printf("F. Camino minimo por coste\n");
    printf("D. Camino minimo por duracion\n");
    printf("s. Salir\n");

    printf("Opcion: ");
    if (scanf(" %c", &opcion) != 1) {
      break;
    }

    switch (opcion) {
    case 'a':
    case 'A':
      anhadirVertice(&CreatorNet);
      break;
    case 'e':
    case 'E':
      eliminarVertice(&CreatorNet);
      break;
    case 'c':
    case 'C':
      anhadirArco(&CreatorNet);
      break;
    case 'b':
    case 'B':
      eliminarArco(&CreatorNet);
      break;
    case 'i':
    case 'I':
      imprimirGrafo(CreatorNet);
      break;
    case 'l':
    case 'L':
      imprimirArcosVertice(CreatorNet);
      break;
    case 'T':
    case 't':
      mostrarEstadisticas(CreatorNet);
      break;
    case 'P':
    case 'p':
      redColaboracionCosteMinimo(CreatorNet);
      break;
    case 'F':
    case 'f':
      caminosCosteMinimoCreadores(CreatorNet);
      break;
    case 'D':
    case 'd':
      caminosDuracionMinimaCreadores(CreatorNet);
      break;
    case 's':
    case 'S':
      opcion = 's';
      break;
    default:
      printf("Opción equivocada\n");
    }
  }
}
int main(int argc, char **argv) {
  // Grafo de números enteros
  TGRAFO CreatorNet;
  /*
   * TODO:
   * MENU DE OPCIONES CON SWITCH
   */

  // Inicializo el grafo
  inicializar(&CreatorNet, argc, argv);

  // Menu de opciones
  MenuOpcionesPrincipal(CreatorNet);

  // guardar grafo en disco
  const int GUARDADO = guardarGrafo(CreatorNet, argc, argv);

  /**
   * AL SALIR, LIBERAMOS LA MEMORIA DEL TAD
   */
  destruirGrafo(&CreatorNet);

  return GUARDADO ? EXIT_SUCCESS : EXIT_FAILURE;
}
