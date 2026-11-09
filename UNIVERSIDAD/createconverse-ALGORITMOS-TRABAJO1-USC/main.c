#include "abb.h"
#include "creatorverse.h"
#include <stdio.h>
#include <string.h>
void mostrarMenu(TABB *A) {
  char opcionMenu = ' ';

  while (opcionMenu != 'S' && opcionMenu != 's') {
    opcionMenu = ' '; // limpiar para evitar que se quede con el valor anterior
                      // y no entre en el bucle
    printf("\nMenu:\n");
    printf("A/a. Añadir creador\n");
    printf("B/b. Buscar creador\n");
    printf("C/c. Completar siguiente reto\n");
    printf("D/d. Buscar reto mas dificil\n");
    printf("L/l. Listar creadores\n");
    printf("E/e. Eliminar creador\n");
    printf("M/m. Modificar creador\n");
    printf("N/n. Añadir nuevos retos\n");
    printf("T/t. Buscar creador/es con mas retos\n");
    printf("S/s. Salir\n");
    printf("Seleccione una opcion: ");
    scanf(" %c", &opcionMenu);

    switch (opcionMenu) {
    case 'A':
    case 'a':
      anhadirCreador(A);
      break;
    case 'L':
    case 'l':
      listarCreadores(*A);
      break;
    case 'E':
    case 'e':
      eliminarCreador(A);
      break;
    case 'N':
    case 'n':
      nuevosRetos(A);
      break;
    case 'C':
    case 'c':
      completarReto(A);
      break;
    case 'S':
    case 's':
      printf("Saliendo...\n");
      break;
    case 'B':
    case 'b':
      buscarCreador(*A);
      break;
    case 'D':
    case 'd':
      buscarRetoMasDificil(*A);
      break;
    case 'T':
    case 't':
      buscarCreadoresConMasRetos(*A);
      break;
    case 'M':
    case 'm':
      modificarCreador(A);
      break;
    default:
      printf("Opcion no valida.\n");
    }
  }
}

int main(int argc, char **argv) {
  // argc , argv son los argumentos de la linea de comandos, argc
  // es el numero de argumentos y argv es un array de strings
  // con los argumentos (ej: ./programa -f archivo.txt)
  // asi puedo cargar un archivo de creadores al iniciar el programa

  //*Funcionamiento: argc == 1 si solo esta el nombre del ejecutable
  //*con: ejecutable -f test.txt , son 3
  //*strcmp(argv[1], "-f") comrpueba si el argumento usado no es -f
  if (argc != 1 && (argc != 3 || strcmp(argv[1], "-f") != 0)) {
    fprintf(stderr, "Uso: %s [-f archivo]\n", argv[0]);
    return 1; // error de argumentos, cerrar programa
  }

  TABB arbolCreadores;
  if (argc == 1) {
    crearAbb(&arbolCreadores);
  } else {
    inicializarCreadores(&arbolCreadores, argv[2]);
  }

  mostrarMenu(&arbolCreadores);

  char archivoSalida[1024]; // guarda la ruta del archivo exactamente
                            // introdcucida por el usuario, sin cambios
  const char *nombreArchivo;
  if (argc == 3) {
    nombreArchivo = argv[2];
  } else {
    printf("Nombre del archivo para guardar los creadores: ");
    if (scanf(" %1023[^\n]", archivoSalida) != 1) {
      fprintf(stderr, "No se pudo leer el nombre del archivo\n");
      destruirAbb(&arbolCreadores);
      return 1;
    }
    nombreArchivo = archivoSalida;
  }

  guardarCreadores(arbolCreadores, nombreArchivo);
  destruirAbb(&arbolCreadores);
  return 0;
}
