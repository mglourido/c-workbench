#include "creatorverse.h"
#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUNCIONES PRIVADAS: su prototipo no esta en creatorverse.h
// Listado de los prototipos de las funciones privadas

// Elimina el cambio de linea final si uso gets() o fgets()
void _strip_line(char *linea);

// Separa cada reto de un creador y lo inserta en la cola de creadores
void _splitByComma(char *field, TCOLA *cola);

// Imprime un reto de un creador
void _imprimirCreador(TIPOELEMENTOABB creador);

// Solicita el alias y recupera el creador si existe
int _solicitarCreador(TABB A, TIPOELEMENTOABB *creador);

// guarda datos de creadores en archivo indicado
void _guardarCreadoresRec(TABB A, FILE *fp);

// recorren el ABB y las colas para buscar e imprimir la dificultad maxima
void _obtenerDificultadMaxima(TABB A, int *maxima);
void _imprimirRetosConDificultad(TABB A, int maxima);

// funciones para recorrer/trasladar retos entre colas conservando su orden
void _trasladarPrimerReto(TCOLA *origen, TCOLA *destino);
void _trasladarCola(TCOLA *origen, TCOLA *destino);

// Cuentan los retos y localizan/muestran todos los perfiles con el maximo.
int _contarRetos(TCOLA retos);
void _obtenerMaximoRetos(TABB A, int *maximo);
void _imprimirCreadoresConRetos(TABB A, int maximo);

// Lectura de campos
int _leerAlias(char *alias, const char *formato);
int _leerCategoria(int *categoria);
int _leerColectivo(char *colectivo, const char *formato);
int _leerSeguidores(long long int *seguidores);
int _leerVerificado(int *verificado);
int _leerTituloReto(char *titulo);
int _leerDificultad(int *dificultad);
int _leerDescripcion(char *descripcion);
int _leerConfirmacionGuardado(char *guardar);

// Comprueba las tres variantes aceptadas para terminar las modificaciones de retos
int _esFinDeRetos(const char *titulo);

// FUNCIONES PUBLICAS: su prototipo está en creatorverse.h

////////////////////////////////////////////////////////////////////////////////////////
// PARA COMPLETAR POR EL/LA ESTUDIANTE:
// COMPLETA TODOS LOS COMENTARIOS INDICADOS EN MAYUSCULAS EN ESTA FUNCION
// Y EN LA FUNCION PRIVADA _splitByComma()
////////////////////////////////////////////////////////////////////////////////////////
void inicializarCreadores(TABB *A, const char *nombreArchivo) {
  TIPOELEMENTOABB creador;
  TCOLA retos; // cola de retos del creador actual

  char linea[1000]; // cada linea del archivo tiene toda la informacion de un
                    // creador
  char *token;      // variable que va leyendo cada campo del creador

  crearAbb(A);

  FILE *fp = fopen(nombreArchivo, "rt");
  if (fp == NULL) {
    perror("Error abriendo el archivo\n");
    return;
  }
  while (fgets(linea, sizeof(linea), fp)) {
    _strip_line(linea);         // elimino el cambio de linea final
    token = strtok(linea, "|"); // primer token
    int n = 0;                  // tengo 7 campos, contador de campos
    while (n < 7) {
      n++;
      switch (n) {
      case 1: // alias
        strncpy(creador.alias, token,
                MAXCLAVE); // se supone que el alias no supera MAXCLAVE, por eso
                           // no se le quita -1 par el terminador nulo
        break;
      case 2: // categoria
        creador.categoria = atoi(token);
        break;
      case 3: // colectivo
        strncpy(creador.colectivo, token, MAXCOLECTIVO);
        break;
      case 4: // seguidores
        creador.seguidores = atoll(token);
        break;
      case 5: // verificado
        creador.verificado = atoi(token);
        break;
      case 6: // cola de retos separados por comas
        crearCola(&retos);

        if (strcmp(token, "-") != 0) {
          _splitByComma(token, &retos);
        }
        creador.retos = retos;
        break;
      case 7: // descripcion
        strncpy(creador.descripcion, token, MAXDESCRIPCION);
        break;
      }
      token = strtok(NULL, "|");
    }
    // insertar el creador en el arbol si no existe ya
    if (esMiembroAbb(*A, creador) == 0) {
      insertarElementoAbb(A, creador);
    }
  }
  fclose(fp);
}

void anhadirCreador(TABB *A) {
  // LOS DATOS SE GUARDAN LOCALMENTE AQUI HASTA QUE SE COMPLETE EL
  // PROCESO Y SE ALMACENEN CORRECTAMENTE EN EL ARBOL

  char alias[MAXCLAVE] = "\0";
  printf("\nIngrese el alias del creador: ");
  _leerAlias(alias, "%s");

  int categoria = -1;
  while (categoria < 1 || categoria > 5) {
    printf("\nIngrese la categoria del creador (1-5): ");
    _leerCategoria(&categoria);
  }

  char colectivo[MAXCOLECTIVO] = "\0";
  printf("\nIngrese el colectivo del creador (use '-' cuando lo "
         "desconozca): ");
  _leerColectivo(colectivo, "%s");

  long long int seguidores = -1;
  while (seguidores < 0) {
    printf("\nIngrese la cantidad de seguidores del creador: ");
    _leerSeguidores(&seguidores);
  }

  int verificado = -1;
  while (verificado != 0 && verificado != 1) {
    printf("\nIngrese si el creador esta verificado (0 o 1): ");
    _leerVerificado(&verificado);
  }

  TCOLA retos;
  crearCola(&retos);
  while (1) {
    TIPOELEMENTOCOLA reto = {0};
    printf("\nIngrese el titulo del reto (o 'FIN'/'fin'/'Fin' para "
           "terminar): ");
    _leerTituloReto(reto.titulo); // el espacio antes del % elimina el salto de
                                  // linea que queda en el buffer del teclado

    if (_esFinDeRetos(reto.titulo)) {
      break;
    }

    while (reto.dificultad < 1 || reto.dificultad > 5) {
      printf("\nIngrese la dificultad del reto (1-5): ");
      _leerDificultad(&reto.dificultad);
    }

    insertarCola(&retos, reto);
  }
  char descripcion[MAXDESCRIPCION] = "\0";
  printf("\nIngrese la descripcion del creador: ");
  _leerDescripcion(descripcion); // lee hasta el salto de linea, lo coje
                                 // como string, no hace falta el %s

  char guardar = ' ';
  while (guardar != 'N' && guardar != 'n' && guardar != 'S' && guardar != 's') {
    printf("\nDesea guardar el creador en el arbol? (S/N): ");
    _leerConfirmacionGuardado(&guardar);
  }

  if (guardar == 'S' || guardar == 's') {
    TIPOELEMENTOABB creador = {0};
    strcpy(creador.alias, alias);
    creador.categoria = categoria;
    strcpy(creador.colectivo, colectivo);
    creador.seguidores = seguidores;
    creador.verificado = verificado;
    creador.retos = retos;
    strcpy(creador.descripcion, descripcion);

    if (esMiembroAbb(*A, creador) == 0) {
      insertarElementoAbb(A, creador);
      printf("\nCreador guardado en el arbol\n");
    } else {
      destruirCola(&retos);
      printf("\nYa existe un creador con ese alias\n");
    }
  } else {
    destruirCola(&retos);
  }
}

// FUNCION RECURSIVA QUE RECORRA EL ARBOL EN ORDEN Y LLAME A
//  _imprimirCreador PARA CADA NODO
void listarCreadores(TABB A) {

  if (esAbbVacio(A)) {
    return;
  }

  listarCreadores(izqAbb(A));

  TIPOELEMENTOABB creador;
  leerElementoAbb(A, &creador);
  _imprimirCreador(creador);

  listarCreadores(derAbb(A));
}

void eliminarCreador(TABB *A) {
  TIPOELEMENTOABB creador = {0};
  if (!_solicitarCreador(*A, &creador)) {
    return;
  }
  suprimirElementoAbb(A, creador);
  printf("Creador eliminado del arbol\n");
}

void modificarCreador(TABB *A) {
  TIPOELEMENTOABB creador = {0};
  if (!_solicitarCreador(*A, &creador)) {
    return;
  }

  char opcion = ' ';
  while (opcion < '0' || opcion > '6') {
    printf("\nCampo a modificar:\n");
    printf("1. Alias\n");
    printf("2. Categoria\n");
    printf("3. Colectivo\n");
    printf("4. Seguidores\n");
    printf("5. Verificado\n");
    printf("6. Descripcion\n");
    printf("0. Cancelar\n");
    printf("Seleccione una opcion: ");
    if (scanf(" %c", &opcion) != 1) {
      return;
    }
    if (opcion < '0' || opcion > '6') {
      printf("Opcion no valida\n");
    }
  }

  switch (opcion) {
  case '0':
    return;
  case '1': {
    TIPOELEMENTOABB anterior = creador;
    printf("\nNuevo alias: ");
    if (_leerAlias(creador.alias, " %s") != 1) {
      return;
    }
    if (strcmp(anterior.alias, creador.alias) == 0) {
      printf("El alias no ha cambiado\n");
      return;
    }
    if (esMiembroAbb(*A, creador)) {
      printf("Ya existe un creador con ese alias\n");
      return;
    }

    // borrar el nodo elimina sus retos, hacer copia temporal
    TCOLA retos;
    crearCola(&retos);
    _trasladarCola(&anterior.retos, &retos);
    suprimirElementoAbb(A, anterior);

    creador.retos = retos;
    insertarElementoAbb(A, creador);
    printf("Creador modificado\n");
    break;
  }
  case '3':
    printf("Nuevo colectivo (use '-' cuando lo desconozca): ");
    if (_leerColectivo(creador.colectivo, " %[^\n]") != 1) {
      return;
    }
    break;
  case '6':
    printf("Nueva descripcion: ");
    if (_leerDescripcion(creador.descripcion) != 1) {
      return;
    }
    break;
  case '2': {
    int valor = -1;
    while (valor < 1 || valor > 5) {
      printf("\nNueva categoria (1-5): ");
      if (_leerCategoria(&valor) != 1) {
        printf("Valor no valido\n");
        return;
      }
    }
    creador.categoria = valor;
    break;
  }
  case '4': {
    long long int valor = -1;
    while (valor < 0) {
      printf("\nNueva cantidad de seguidores (0 o mas): ");
      _leerSeguidores(&valor);
    }
    creador.seguidores = valor;
    break;
  }
  case '5': {
    int valor = -1;
    while (valor != 0 && valor != 1) {
      printf("Verificado (0 o 1): ");
      _leerVerificado(&valor);
    }
    creador.verificado = valor;
    break;
  }
  }

  if (opcion != '1') {
    modificarElementoAbb(*A, creador);
    printf("Creador modificado\n");
  }
}

void nuevosRetos(TABB *A) {
  TIPOELEMENTOABB creador = {0};
  if (!_solicitarCreador(*A, &creador)) {
    return;
  }

  while (1) {
    TIPOELEMENTOCOLA reto = {0};
    printf("Reto (fin para finalizar): ");
    if (_leerTituloReto(reto.titulo) != 1) {
      return;
    }

    if (_esFinDeRetos(reto.titulo)) {
      return;
    }

    while (reto.dificultad < 1 || reto.dificultad > 5) {
      printf("Dificultad (1-5): ");
      _leerDificultad(&reto.dificultad);

      if (reto.dificultad < 1 || reto.dificultad > 5) {
        reto.dificultad = 0;
        printf("Introduce una dificultad entre 1 y 5\n");
      }
    }

    insertarCola(&creador.retos, reto);
    modificarElementoAbb(*A, creador);
  }
}

void completarReto(TABB *A) {
  TIPOELEMENTOABB creador = {0};
  if (!_solicitarCreador(*A, &creador)) {
    return;
  }

  if (esVaciaCola(creador.retos)) {
    printf("Este creador no tiene retos pendientes\n");
    return;
  }

  TIPOELEMENTOCOLA reto = primeroCola(creador.retos);
  printf("Reto completado: %s [dificultad: %d]\n", reto.titulo,
         reto.dificultad);
  suprimirCola(&creador.retos);
  modificarElementoAbb(*A, creador);

  if (esVaciaCola(creador.retos)) {
    printf("Este creador no tiene mas retos\n");
  } else {
    reto = primeroCola(creador.retos);
    printf("Proximo reto: %s [dificultad: %d]\n", reto.titulo, reto.dificultad);
  }
}

void guardarCreadores(TABB A, const char *nombreArchivo) {
  // fopen crea el archivo si no existe; si existe destruye el contenido, asi
  // que no actualiza eficientemente porque reconstruye todo, pero sirve para
  // este tema
  // w: es de modo escritura
  FILE *fp = fopen(nombreArchivo, "w");

  if (fp == NULL) {
    // perror es el printf para errores, asi sale mas descriptivo
    perror("Error abriendo el archivo para guardar creadores");
    return;
  }

  _guardarCreadoresRec(A, fp);

  // comprobar errores tanto de escritura como de cierre.

  // si hay fallos durante el proceso de
  // escritura (0:bien,!=0 para lo demas)
  int errorEscritura = ferror(fp);
  // este cierra el archivo terminando todo el proceso de actualizacion
  // de DB; la funcion devuelve o: si salio bien, EOF : si fallo
  int errorCierre = fclose(fp);

  if (errorEscritura || errorCierre == EOF) {
    fprintf(stderr, "Error al guardar los creadores\n");
  }
}

void buscarCreador(TABB A) {
  TIPOELEMENTOABB creador = {0};
  if (!_solicitarCreador(A, &creador)) {
    return;
  }

  _imprimirCreador(creador);
}

void buscarRetoMasDificil(TABB A) {
  int maxima = 0; // Las dificultades validas van de 1 a 5.

  // Primer recorrido: localizar la dificultad maxima.
  _obtenerDificultadMaxima(A, &maxima);
  if (maxima == 0) {
    printf("No hay retos pendientes\n");
    return;
  }

  printf("Retos con dificultad maxima: %d\n", maxima);

  // Segundo recorrido: mostrar todos los empates.
  _imprimirRetosConDificultad(A, maxima);
}

void buscarCreadoresConMasRetos(TABB A) {
  if (esAbbVacio(A)) {
    printf("No hay creadores registrados\n");
    return;
  }

  int maximo = 0;
  _obtenerMaximoRetos(A, &maximo);
  printf("Creadores con mas retos pendientes: %d\n", maximo);
  _imprimirCreadoresConRetos(A, maximo);
}

///////////////////////////////////////////////////////
// FUNCIONES PRIVADAS
//////////////////////////////////////////////
int _esFinDeRetos(const char *titulo) {
  return strcmp(titulo, "FIN") == 0 || strcmp(titulo, "fin") == 0 ||
         strcmp(titulo, "Fin") == 0;
}

int _leerAlias(char *alias, const char *formato) {
  return scanf(formato, alias);
}

int _leerCategoria(int *categoria) { return scanf("%d", categoria); }

int _leerColectivo(char *colectivo, const char *formato) {
  return scanf(formato, colectivo);
}

int _leerSeguidores(long long int *seguidores) {
  return scanf("%lld", seguidores);
}

int _leerVerificado(int *verificado) { return scanf("%d", verificado); }

int _leerTituloReto(char *titulo) { return scanf(" %[^\n]", titulo); }

int _leerDificultad(int *dificultad) { return scanf("%d", dificultad); }

int _leerDescripcion(char *descripcion) {
  return scanf(" %[^\n]", descripcion);
}

int _leerConfirmacionGuardado(char *guardar) { return scanf(" %c", guardar); }

// Requiere que la cola de origen no este vacia.
void _trasladarPrimerReto(TCOLA *origen, TCOLA *destino) {
  TIPOELEMENTOCOLA reto = primeroCola(*origen);
  insertarCola(destino, reto);
  suprimirCola(origen);
}

// Anade todos los retos al destino y deja el origen vacio.
void _trasladarCola(TCOLA *origen, TCOLA *destino) {
  while (!esVaciaCola(*origen)) {
    _trasladarPrimerReto(origen, destino);
  }
}

// Cuenta pasando los retos a una cola auxiliar y restaura su orden original.
int _contarRetos(TCOLA retos) {
  int cantidad = 0;
  TCOLA temporal;
  crearCola(&temporal);

  while (!esVaciaCola(retos)) {
    _trasladarPrimerReto(&retos, &temporal);
    cantidad++;
  }

  _trasladarCola(&temporal, &retos);
  destruirCola(&temporal);
  return cantidad;
}

void _obtenerMaximoRetos(TABB A, int *maximo) {
  if (esAbbVacio(A)) {
    return;
  }

  _obtenerMaximoRetos(izqAbb(A), maximo);

  TIPOELEMENTOABB creador;
  leerElementoAbb(A, &creador);
  int cantidad = _contarRetos(creador.retos);
  if (cantidad > *maximo) {
    *maximo = cantidad;
  }

  _obtenerMaximoRetos(derAbb(A), maximo);
}

// Muestra todos los empates por orden alfabetico de alias.
void _imprimirCreadoresConRetos(TABB A, int maximo) {
  if (esAbbVacio(A)) {
    return;
  }

  _imprimirCreadoresConRetos(izqAbb(A), maximo);

  TIPOELEMENTOABB creador;
  leerElementoAbb(A, &creador);
  if (_contarRetos(creador.retos) == maximo) {
    _imprimirCreador(creador);
  }

  _imprimirCreadoresConRetos(derAbb(A), maximo);
}

// Primer recorrido: actualiza el maximo y restaura cada cola.
void _obtenerDificultadMaxima(TABB A, int *maxima) {
  if (esAbbVacio(A)) {
    return;
  }

  _obtenerDificultadMaxima(izqAbb(A), maxima);

  TIPOELEMENTOABB creador;
  leerElementoAbb(A, &creador);
  TCOLA temporal;
  crearCola(&temporal);

  while (!esVaciaCola(creador.retos)) {
    TIPOELEMENTOCOLA reto = primeroCola(creador.retos);
    if (reto.dificultad > *maxima) {
      *maxima = reto.dificultad;
    }
    _trasladarPrimerReto(&creador.retos, &temporal);
  }

  // Devolver los retos en el mismo orden en el que se extrajeron.
  _trasladarCola(&temporal, &creador.retos);
  destruirCola(&temporal);

  _obtenerDificultadMaxima(derAbb(A), maxima);
}

// Segundo recorrido: imprime todos los retos que alcanzan el maximo.
void _imprimirRetosConDificultad(TABB A, int maxima) {
  if (esAbbVacio(A)) {
    return;
  }

  _imprimirRetosConDificultad(izqAbb(A), maxima);

  TIPOELEMENTOABB creador;
  leerElementoAbb(A, &creador);
  TCOLA temporal;
  crearCola(&temporal);

  while (!esVaciaCola(creador.retos)) {
    TIPOELEMENTOCOLA reto = primeroCola(creador.retos);
    if (reto.dificultad == maxima) {
      printf("Alias: %s, Reto: %s\n", creador.alias, reto.titulo);
    }
    _trasladarPrimerReto(&creador.retos, &temporal);
  }

  // Restaurar tambien los retos que no coinciden con el maximo.
  _trasladarCola(&temporal, &creador.retos);
  destruirCola(&temporal);

  _imprimirRetosConDificultad(derAbb(A), maxima);
}

// Solicita el alias, valida su existencia y recupera sus datos.
int _solicitarCreador(TABB A, TIPOELEMENTOABB *creador) {
  printf("Introduce el alias del creador: ");
  if (_leerAlias(creador->alias, "%s") != 1) {
    return 0;
  }

  if (!esMiembroAbb(A, *creador)) {
    printf("No existe un creador con ese alias\n");
    return 0;
  }

  buscarNodoAbb(A, creador->alias, creador);
  return 1;
}

// lee una cadena de retos y los almacena en la cola
// el formato de cadena es
// "titulo1:dificultad1,titulo2:dificultad2,titulo3:dificultad3,... el titulo es
// texto y la dificultad es un entero
void _splitByComma(char *cadena, TCOLA *cola) {
  TIPOELEMENTOCOLA reto; // va a tener los campos titulo y dificultad

  char cadenareto[MAX_RETO]; // es cada reto con los campos titulo y dificultad,
                             // leo su longitud de la longitud maxima del titulo
                             // en cola.h

  char *start = cadena;
  char *end = cadena;
  while (*end != '\0') {
    if (*end == ',') {
      *end = '\0';
      // cadenareto va a contener titulo:dificultad del reto leido

      strncpy(cadenareto, start, MAX_RETO); // MAX_RETO se lee de cola.h

      // podemos separar los campos de cada reto de forma facil con sscanf

      sscanf(cadenareto, " %[^:]:%d", reto.titulo, &reto.dificultad);

      insertarCola(cola, reto);

      start = end + 1;
    }
    end++;
  }
  // Copia el ultimo token

  strncpy(cadenareto, start, MAX_RETO); // MAX_RETO se lee de cola.h

  sscanf(cadenareto, " %[^:]:%d", reto.titulo, &reto.dificultad);

  insertarCola(cola, reto);
}

// Funcion para eliminar el cambio de linea si uso gets() o fgets()
void _strip_line(char *linea) { linea[strcspn(linea, "\r\n")] = 0; }

// Funcion para imprimir la cola de retos de un creador
void _imprimirCola(TCOLA retos) {
  // copia de la cola temporal para no perder los datos de la cola original
  TCOLA temp;
  crearCola(&temp);

  // imprimir cola
  while (!esVaciaCola(retos)) {
    TIPOELEMENTOCOLA reto = primeroCola(retos);
    printf("Reto: %s, Dificultad: %d\n", reto.titulo, reto.dificultad);
    _trasladarPrimerReto(&retos, &temp);
  }

  // devolver los valores de la cola original
  _trasladarCola(&temp, &retos);
  // destruir la cola temporal
  destruirCola(&temp);
}

// Funcion para imprimir un creador
void _imprimirCreador(TIPOELEMENTOABB creador) {
  printf("Alias: %s\n", creador.alias);
  printf("Categoria: %d\n", creador.categoria);
  printf("Colectivo: %s\n", creador.colectivo);
  printf("Seguidores: %lld\n", creador.seguidores);
  printf("Verificado: %d\n", creador.verificado);
  _imprimirCola(creador.retos);
  printf("Descripcion: %s\n", creador.descripcion);
}

// Funcion para guardar los datos de los creadores en archivo de creadores
// indicado
void _guardarCreadoresRec(TABB A, FILE *fp) {
  if (esAbbVacio(A)) {
    return;
  }

  TIPOELEMENTOABB creador;
  leerElementoAbb(A, &creador);

  // preorden: guardar la raiz antes de correr los hijos
  // guardar informacion del creador (fprintf guarda los datos en 'fp', no es lo
  // mismo que printf que muestra por consola)

  fprintf(fp, "%s|%d|%s|%lld|%d|", creador.alias, creador.categoria,
          creador.colectivo, creador.seguidores, creador.verificado);

  if (esVaciaCola(creador.retos)) { // la cola vacia se declara con "-" por menu
    fprintf(fp, "-");
  } else {
    TCOLA temporal;
    crearCola(&temporal);

    // Guardar los retos y trasladarlos a la cola temporal.
    while (!esVaciaCola(creador.retos)) {
      TIPOELEMENTOCOLA reto = primeroCola(creador.retos);
      fprintf(fp, "%s:%d", reto.titulo, reto.dificultad);
      _trasladarPrimerReto(&creador.retos, &temporal);

      if (!esVaciaCola(creador.retos)) {
        fprintf(fp, ",");
      }
    }

    // Restaurar la cola original manteniendo el orden.
    _trasladarCola(&temporal, &creador.retos);

    destruirCola(&temporal);
  }

  fprintf(fp, "|%s|\n", creador.descripcion);

  // recursiva, guard el subarbol izquierdo y luego derecho (preorden)
  _guardarCreadoresRec(izqAbb(A), fp);
  _guardarCreadoresRec(derAbb(A), fp);
}
