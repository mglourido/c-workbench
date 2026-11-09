#include "grafo.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////
// PROTOTIPOS DE LAS FUNCIONES PRIVADAS ///////////////////////////////////
// DEFINICIONES NECESARIAS PARA CARGAR EL ARCHIVO
#define TAM_LINEA (2 * TAM_ALIAS + TAM_COLECTIVO + 80)
// CATEGORIAS Y MODALIDADES PERMITIDAS
#define NUM_CATEGORIAS 5
static const char MODALIDADES[] = {'D', 'R'};
#define N_MODALIDADES ((int)sizeof MODALIDADES)
#define TAM_ENTRADA 30 // maximo de caracteres leidos para la categoria, el coste y la duracion
static int _modalidadValida(char modalidad);
static int _cargarDatos(TGRAFO *G, const char *nombre_fichero);
static const char *_comprobarArgumentos(int argc, char *argv[]);
static void _procesarCreador(TGRAFO *G);
static void _procesarColaboracion(TGRAFO *G);
static void _strip_line(char *linea);
// TUS FUNCIONES PRIVADAS
/*
 * TODO:
 * ANHADE AQUI LOS PROTOTIPOS DE LAS FUNCIONES PRIVADAS QUE CREES
 */
//////////////////////////////////////////////////////////////////////////
static int _leerVerticesCategoria(TGRAFO G, int categoria);
static int *_leerArcosVertice(TGRAFO G, int pos1);
static int _leerArcosModalidad(TGRAFO G, char modalidad);
static void _guardarVerticesDisco(TGRAFO G, FILE *fp);
static void _guardarArcosDisco(TGRAFO G, FILE *fp);
static int _escribirGrafo(TGRAFO G, const char *nombreArchivo);
static void _errorLectura(void);
static int _posicionPorAlias(TGRAFO G, const char *alias);
static void _imprimirColaboraciones(TGRAFO G, int pos);
static void _borrarColaboracion(TGRAFO *G, int pos1, int pos2);
// Criterio de optimizacion de los caminos minimos (peso de cada arco)
enum { CRITERIO_COSTE, CRITERIO_DURACION };
#define INFINITO 1e30 // mayor que cualquier coste o duracion real
static void _floydWarshall(TGRAFO G, int criterio, double D[][MAXVERTICES],
                           int P[][MAXVERTICES]);
static void _imprimirCamino(TGRAFO G, int P[][MAXVERTICES], int origen,
                            int destino);
static void _caminoMinimoCreadores(TGRAFO G, int criterio);
///////////////////////////////////////////////////////////////////////////
// IMPLEMENTACION DE LAS FUNCIONES PUBLICAS

// Funcion que inicializa el grafo cargando los datos de fichero si existe
void inicializar(TGRAFO *G, int argc, char *argv[]) {
  const char *nombreFichero;
  crearGrafo(G);
  nombreFichero = _comprobarArgumentos(argc, argv);
  if (nombreFichero != NULL) {
    _cargarDatos(G, nombreFichero);
  }
}
// TUS FUNCIONES PUBLICAS
/*
 * TODO:
 * ANHADE AQUI LA IMPLEMENTACION DE LAS FUNCIONES QUE LLAMES DESDE EL MENU
 */
//////////////////////////////////////////////////////////////////////////
void anhadirVertice(TGRAFO *G) {
  TIPOVERTICE v = {0};

  // recoger datos
  printf("\nIntroduce el alias: ");
  if (scanf(" %99s", v.alias) != 1) {
    _errorLectura();
    return;
  }
  v.alias[TAM_ALIAS - 1] = '\0';

  char categoria[TAM_ENTRADA];
  printf("\nIntroduce la categoria (1-5): ");
  if (scanf(" %29s", categoria) != 1) {
    _errorLectura();
    return;
  }
  categoria[TAM_ENTRADA - 1] = '\0';
  char *fin; // primer caracter que strtol no ha podido convertir
  v.categoria = (int)strtol(categoria, &fin, 10);
  if (*fin != '\0' || v.categoria > NUM_CATEGORIAS || v.categoria < 1) {
    printf("\nCategoria inexistente, se ha cancelado el proceso.\n");
    return;
  }

  printf("\nIntroduce el colectivo: ");
  if (scanf(" %99s", v.colectivo) != 1) {
    _errorLectura();
    return;
  }
  v.colectivo[TAM_COLECTIVO - 1] = '\0';

  // Comprobar si se puede insertar

  if (existeVertice(*G, v)) {
    printf("\nEse creador ya existe.\n");
    return;
  }

  if (leerN(*G) == MAXVERTICES) {
    printf("\nYa se ha alcanzado el numero maximo de creadores");
    return;
  }

  // todo correcto: insertar vertice en grafo
  crearVertice(G, v);
  printf("\nCreador guardado.\n");
}
void eliminarVertice(TGRAFO *G) {
  TIPOVERTICE v = {0};

  printf("\nIntroduce el alias del creador: ");
  if (scanf(" %99s", v.alias) != 1) {
    _errorLectura();
    return;
  }
  v.alias[TAM_ALIAS - 1] = '\0';

  const int pos1 = posicionVertice(*G, v);
  if (pos1 == -1) {
    printf("\nCreador no borrado, no existe\n");
    return;
  }

  int *arcos = _leerArcosVertice(*G, pos1);
  if (arcos != NULL) {
    printf("\nBorrando colaboraciones del creador.\n");
    int i = 0;
    while (arcos[i] >= 0) {
      _borrarColaboracion(G, pos1, arcos[i]);
      i++;
    }
    free(arcos);
  }
  borrarVertice(G, v);
  printf("\nCreador borrado.\n");
}

void anhadirArco(TGRAFO *G) {
  char alias1[TAM_ALIAS];
  char alias2[TAM_ALIAS];

  printf("\nEscribe el alias del primer creador:");
  if (scanf(" %99s", alias1) != 1) {
    _errorLectura();
    return;
  }
  alias1[TAM_ALIAS - 1] = '\0';
  printf("\nEscribe el alias del segundo creador:");
  if (scanf(" %99s", alias2) != 1) {
    _errorLectura();
    return;
  }
  alias2[TAM_ALIAS - 1] = '\0';

  TIPOARCO colaboracion = {0};

  char coste[TAM_ENTRADA];
  printf("\nCual es el coste de la colaboracion : ");
  if (scanf(" %29s", coste) != 1) {
    _errorLectura();
    return;
  }
  coste[TAM_ENTRADA - 1] = '\0';
  char *fin; // primer caracter que strtof no ha podido convertir
  colaboracion.coste = strtof(coste, &fin);

  if (*fin != '\0' || !(colaboracion.coste >= 0)) { // tambien rechaza nan
    printf("\nEl coste debe ser un numero no negativo, cancelado operacion.\n");
    return;
  }

  char duracion[TAM_ENTRADA];
  printf("\nCual es la duracion de la colaboracion (meses) : ");
  if (scanf(" %29s", duracion) != 1) {
    _errorLectura();
    return;
  }
  duracion[TAM_ENTRADA - 1] = '\0';
  colaboracion.duracion = strtof(duracion, &fin);

  if (*fin != '\0' || !(colaboracion.duracion > 0)) { // tambien rechaza nan
    printf("\nLa duracion debe ser un numero mayor a 0, cancelado operacion.\n");
    return;
  }

  printf("\nCual es la modalidad de la colaboracion : ");
  if (scanf(" %c", &colaboracion.modalidad) != 1) {
    _errorLectura();
    return;
  }

  if (!_modalidadValida(colaboracion.modalidad)) {
    printf("\nLa modalidad debe ser R/D , valor introducido no valido, cancelado "
           "operacion.\n");
    return;
  }

  const int VP1 = _posicionPorAlias(*G, alias1);
  const int VP2 = _posicionPorAlias(*G, alias2);

  if (VP1 == -1 || VP2 == -1 || (VP1 == VP2)) {
    printf("\nCreadores no validos\n");
    return;
  }
  const int vc = existeArco(*G, VP1, VP2);
  if (vc) {
    printf("\nYa existe la colaboracion entre ambos creadores\n");
    return;
  }

  // todo bien: crear arco
  crearArco(G, VP1, VP2, colaboracion);
  printf("\nColaboracion creada\n");
}
void eliminarArco(TGRAFO *G) {
  char alias1[TAM_ALIAS];
  char alias2[TAM_ALIAS];

  printf("\nEscribe el alias del primer creador:");
  if (scanf(" %99s", alias1) != 1) {
    _errorLectura();
    return;
  }
  alias1[TAM_ALIAS - 1] = '\0';
  printf("\nEscribe el alias del segundo creador:");
  if (scanf(" %99s", alias2) != 1) {
    _errorLectura();
    return;
  }
  alias2[TAM_ALIAS - 1] = '\0';

  const int VP1 = _posicionPorAlias(*G, alias1);
  const int VP2 = _posicionPorAlias(*G, alias2);

  if (VP1 == -1 || VP2 == -1) {
    printf("\nCreadores no validos\n");
    return;
  }

  const int VC1 = existeArco(*G, VP1, VP2);
  const int VC2 = existeArco(*G, VP2, VP1);
  if (!VC1 && !VC2) {
    printf("\nNo existe la colaboracion entre ambos creadores\n");
    return;
  }

  _borrarColaboracion(G, VP1, VP2);

  printf("\nColaboraciones borradas.\n");
}

void imprimirGrafo(TGRAFO G) {
  TIPOVERTICE *vertices = leerVertices(G);
  const int N_VERTICES = leerN(G);
  if (N_VERTICES == 0) {
    printf("\nNo hay creadores ni colaboraciones\n");
    return;
  }

  for (int i = 0; i < N_VERTICES; i++) {
    const TIPOVERTICE vActual = vertices[i];
    const int POSICION_VA = posicionVertice(G, vActual);
    // mostrar vertice
    printf("\n%s (categoria %i, %s)", vActual.alias, vActual.categoria,
           vActual.colectivo);

    // mostrar sus arcos
    _imprimirColaboraciones(G, POSICION_VA);
  }

  printf("\nLista mostrada.\n");
}
void imprimirArcosVertice(TGRAFO G) {
  char alias[TAM_ALIAS];

  printf("\nAlias que se desea consultar: ");
  if (scanf(" %99s", alias) != 1) {
    _errorLectura();
    return;
  }
  alias[TAM_ALIAS - 1] = '\0';

  const int POSICION_V = _posicionPorAlias(G, alias);
  if (POSICION_V == -1) {
    printf("\nEl creador no existe\n");
    return;
  }

  printf("\nColaboraciones de %s:", alias);
  _imprimirColaboraciones(G, POSICION_V);
  printf("\nLista mostrada.\n");
}
void mostrarEstadisticas(TGRAFO G) {
  TIPOVERTICE *vertices = leerVertices(G);
  const int N_CREADORES = leerN(G);
  if (N_CREADORES == 0) {
    printf("\nNo hay creadores ni colaboraciones\n");
    return;
  }

  // contabilizar creadores por categoria
  int n_creadores_categorias[NUM_CATEGORIAS] = {0};
  for (int i = 0; i < NUM_CATEGORIAS; i++) {
    n_creadores_categorias[i] = _leerVerticesCategoria(G, i + 1);
  }

  // contabilizar arcos, coste y duracion, y grado de cada creador.
  // Cada colaboracion son 2 arcos (uno en cada sentido), por eso los totales
  // se dividen entre 2 al final.
  int ncolaboraciones[MAXVERTICES] = {
      0}; // numero de colaboraciones de cada creador
  int maxNcolaboraciones = 0;
  int arcosTotales = 0;
  float costeTotal = 0;
  float duracionTotal = 0;
  for (int i = 0; i < N_CREADORES; i++) {
    int *arcos = _leerArcosVertice(G, i);
    if (arcos == NULL)
      continue;
    int k = 0;
    while (arcos[k] >= 0) {
      const TIPOARCO ARCO = leerArco(G, i, arcos[k]);
      costeTotal += ARCO.coste;
      duracionTotal += ARCO.duracion;
      k++;
    }
    free(arcos);
    ncolaboraciones[i] = k;
    arcosTotales += k;
    if (k > maxNcolaboraciones)
      maxNcolaboraciones = k;
  }
  const int ARCOS_UNICOS =
      arcosTotales / 2; // cada colaboracion tiene 2 arcos, se debe contar 1

  // contabilizar arcos por modalidad
  int n_colaboraciones_modalidad[N_MODALIDADES] = {0};
  for (int i = 0; i < N_MODALIDADES; i++) {
    n_colaboraciones_modalidad[i] = _leerArcosModalidad(G, MODALIDADES[i]);
  }

  //*IMPRIMIR DATOS
  printf("\nEstadisticas de la red:\n");
  printf("\nNumero total de creadores: %i", N_CREADORES);
  for (int i = 0; i < NUM_CATEGORIAS; i++) {
    printf("\nNumero total de creadores de la categoria %i : %i", i + 1,
           n_creadores_categorias[i]);
  }
  printf("\nNumero total de colaboraciones: %i", ARCOS_UNICOS);
  for (int i = 0; i < N_MODALIDADES; i++) {
    printf("\nNumero total de colaboraciones de la modalidad %c : %i",
           MODALIDADES[i], n_colaboraciones_modalidad[i]);
  }

  if (ARCOS_UNICOS == 0) {
    printf("\nNo hay colaboraciones registradas, no se pueden calcular "
           "medias ni el creador con mas colaboraciones.\n");
    return;
  }

  // cada colaboracion esta sumada 2 veces en costeTotal y duracionTotal
  const float COSTE_MEDIO_COLABORACIONES = (costeTotal / 2) / ARCOS_UNICOS;
  const float DURACION_MEDIA_COLABORACIONES =
      (duracionTotal / 2) / ARCOS_UNICOS; // ya viene n meses
  printf("\nCoste medio de las colaboraciones: %f", COSTE_MEDIO_COLABORACIONES);
  printf("\nDuracion media de las colaboraciones: %f meses",
         DURACION_MEDIA_COLABORACIONES);

  // todos los creadores empatados en numero maximo de colaboraciones
  printf("\n-Creador/es con maximo numero de colaboraciones: ");
  for (int i = 0; i < N_CREADORES; i++) {
    if (ncolaboraciones[i] == maxNcolaboraciones) {
      printf("\nNombre: %s , %i colaboraciones", vertices[i].alias,
             ncolaboraciones[i]);
    }
  }
  printf("\n");
}
void redColaboracionCosteMinimo(TGRAFO G) {
  const int N = leerN(G);
  if (N == 0) {
    printf("\nNo hay creadores ni colaboraciones\n");
    return;
  }
  TIPOVERTICE *vertices = leerVertices(G);

  int visitado[MAXVERTICES] = {0}; // 0:no visitado , 1:visitado
  int numVisitados = 0;
  int numComponentes = 0;
  float costeTotal = 0;

  // un Prim por componente conexa
  while (numVisitados < N) {
    // primer vertice sin visitar = semilla de la nueva componente
    int semilla = 0;
    while (visitado[semilla])
      semilla++;
    visitado[semilla] = 1;
    numVisitados++;
    numComponentes++;
    printf("\nRed de coste mínimo de Componente Conexa %d\n", numComponentes);

    int encontrado = 1;
    while (encontrado) {
      encontrado = 0;
      int vx = -1;
      int vy = -1;
      float minimo = 0;//coste del arco con peos minimo encontrado

      // arco de menor coste entre un vertice visitado y uno no visitado
      for (int i = 0; i < N; i++) {
        if (!visitado[i])
          continue;
        for (int j = 0; j < N; j++) {
          if (visitado[j] || !existeArco(G, i, j))
            continue;
          const float COSTE = leerArco(G, i, j).coste;
          if (!encontrado || COSTE < minimo) {
            minimo = COSTE;
            vx = i;//posicion del vertice visitado , vertice origen
            vy = j;//posicion del vertice no visitado, vertice destino
            encontrado = 1;
          }
        }
      }

      if (encontrado) {
        visitado[vy] = 1;
        numVisitados++;
        costeTotal += minimo;
        printf("%15s--%c--%-15s: %9.2f €\n", vertices[vx].alias,
               leerArco(G, vx, vy).modalidad, vertices[vy].alias, minimo);
      }
    }
  }
  printf("\nCoste total del bosque: %.2f €\n", costeTotal);
}

void caminosCosteMinimoCreadores(TGRAFO G) {
  _caminoMinimoCreadores(G, CRITERIO_COSTE);
}

void caminosDuracionMinimaCreadores(TGRAFO G) {
  _caminoMinimoCreadores(G, CRITERIO_DURACION);
}

int guardarGrafo(TGRAFO G, int argc, char **argv) {
  //*conseguir nombre donde guardar
  // rutaEjecutable -f rutaDatos -> 3 argumentos (se usa esa ruta); en otro caso
  // se debe pedir
  char archivoSalida[1024]; // guarda la ruta del archivo exactamente
                            // introducida por el usuario, sin cambios
  const char *nombreArchivo = (argc == 3) ? argv[2] : NULL;

  // no se termina hasta guardar bien: si falla, se pide otro nombre
  while (1) {
    if (nombreArchivo == NULL) {
      printf("Nombre del archivo para guardar los creadores: ");
      if (scanf(" %1023[^\n]", archivoSalida) != 1) {
        fprintf(stderr, "No se pudo leer el nombre del archivo\n");
        return 0; // sin entrada no se puede reintentar
      }
      nombreArchivo = archivoSalida;
    }

    if (_escribirGrafo(G, nombreArchivo)) {
      return 1;
    }
    fprintf(stderr, "No se pudo guardar en '%s'. Prueba con otro nombre.\n",
            nombreArchivo);
    nombreArchivo = NULL; // en el siguiente intento se pide otro nombre
  }
}
///////////////////////////////////////////////////////////////////////////
// IMPLEMENTACION DE LAS FUNCIONES PRIVADAS
/*
 * TODO:
 * COMPLETAR LAS FUNCIONES _procesarCreador() Y _procesarColaboracion()
 */

// Funcion privada que comprueba los argumentos de main
static const char *_comprobarArgumentos(int argc, char *argv[]) {
  if (argc == 3 && strcmp(argv[1], "-f") == 0) {
    return argv[2];
  }
  fprintf(stderr, "Aviso: los argumentos de ejecución no son correctos.\n");
  fprintf(stderr, "Uso: ./creatornet -f <fichero_datos>\n");
  fprintf(stderr, "CreatorNet se iniciara con una red vacia.\n");
  return NULL;
}

// Funcion privada que carga los datos del archivo
static int _cargarDatos(TGRAFO *G, const char *nombreFichero) {
  FILE *fichero;
  char linea[TAM_LINEA];
  char *token;

  int cargaCorrecta = 0;
  fichero = fopen(nombreFichero, "r");
  if (fichero == NULL) {
    fprintf(stderr, "Aviso: no se ha podido abrir el fichero '%s'.\n",
            nombreFichero);
    fprintf(stderr, "CreatorNet se iniciara con una red vacia.\n");
    return cargaCorrecta;
  }
  cargaCorrecta = 1;
  while (fgets(linea, sizeof linea, fichero)) {
    _strip_line(linea);
    token = strtok(linea, ";");
    if (token) {
      switch (token[0]) {
      case 'C':
        _procesarCreador(G); // actua sobre token actual
        break;
      case 'A':
        _procesarColaboracion(G); // actua sobre token actual
        break;
      default:
        printf("Tipo de registro desconocido: %s\n", token);
      }
    }
  }
  if (ferror(fichero)) {
    fprintf(stderr,
            "Aviso: se ha producido un error durante la "
            "lectura del fichero '%s'.\n",
            nombreFichero);
    cargaCorrecta = 0;
  }
  fclose(fichero);
  return cargaCorrecta;
}
/**
 * Busca la posicion de un creador a partir de su alias
 *@param G grafo
 *@param alias alias del creador
 *@return posicion del vertice, o -1 si no existe
 */
static int _posicionPorAlias(TGRAFO G, const char *alias) {
  TIPOVERTICE v = {0};
  strncpy(v.alias, alias, TAM_ALIAS - 1);
  return posicionVertice(G, v);
}
/**
 * Imprime las colaboraciones de un creador
 *@param G grafo
 *@param pos posicion del creador en el grafo
 */
static void _imprimirColaboraciones(TGRAFO G, int pos) {
  TIPOVERTICE *vertices = leerVertices(G);
  const int N_VERTICES = leerN(G);
  int *arcos = _leerArcosVertice(G, pos);
  if (arcos == NULL)
    return;
  int j = 0;
  while (arcos[j] >= 0 && j < N_VERTICES) {
    const TIPOARCO AC = leerArco(G, pos, arcos[j]);
    const TIPOVERTICE VC = vertices[arcos[j]];
    printf("\n  [%c] %-15s coste: %8.2f €  duracion: %6.2f h", AC.modalidad,
           VC.alias, AC.coste, AC.duracion);

    j++;
  }
  free(arcos);
}
/**
 * Borra la colaboracion entre dos creadores en los dos sentidos del arco
 *@param G grafo
 *@param pos1 posicion del primer creador
 *@param pos2 posicion del segundo creador
 */
static void _borrarColaboracion(TGRAFO *G, int pos1, int pos2) {
  if (existeArco(*G, pos1, pos2))
    borrarArco(G, pos1, pos2);
  if (existeArco(*G, pos2, pos1))
    borrarArco(G, pos2, pos1);
}
/**
 * Comprueba si la modalidad es una de las permitidas (MODALIDADES)
 *@param modalidad caracter que identifica la modalidad
 *@return 1 si es valida, 0 si no
 */
static int _modalidadValida(char modalidad) {
  for (int i = 0; i < N_MODALIDADES; i++) {
    if (modalidad == MODALIDADES[i])
      return 1;
  }
  return 0;
}
/**
 * Algoritmo de Floyd-Warshall. Calcula la distancia minima entre todos los
 * pares de creadores segun el criterio dado.
 *@param G grafo
 *@param criterio CRITERIO_COSTE o CRITERIO_DURACION (peso de cada arco)
 *@param D matriz de salida: D[i][j] = distancia minima de i a j (INFINITO si
 *         no hay camino)
 *@param P matriz de salida: P[i][j] = vertice previo a j en el camino minimo
 *         desde i (-1 si no hay camino o i == j)
 */
static void _floydWarshall(TGRAFO G, int criterio, double D[][MAXVERTICES],
                           int P[][MAXVERTICES]) {
  const int N = leerN(G);

  // inicializacion de las matrices
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j) {
        D[i][j] = 0;
        P[i][j] = -1;
      } else if (existeArco(G, i, j)) {
        const TIPOARCO ARCO = leerArco(G, i, j);
        D[i][j] = (criterio == CRITERIO_COSTE) ? ARCO.coste : ARCO.duracion;
        P[i][j] = i;
      } else {
        D[i][j] = INFINITO;
        P[i][j] = -1;
      }
    }
  }

  // calculo iterativo: se permite pasar por el vertice k como intermedio
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (D[i][j] > D[i][k] + D[k][j]) {
          D[i][j] = D[i][k] + D[k][j];
          P[i][j] = P[k][j];
        }
      }
    }
  }
}

/**
 * Imprime el camino minimo de origen a destino con la modalidad de cada
 * colaboracion: A --R-- B --D-- C. Debe existir camino.
 *@param G grafo
 *@param P matriz de predecesores de Floyd-Warshall
 *@param origen posicion del creador de origen
 *@param destino posicion del creador de destino
 */
static void _imprimirCamino(TGRAFO G, int P[][MAXVERTICES], int origen,
                            int destino) {
  if (origen != destino) {
    const int PREVIO = P[origen][destino];
    _imprimirCamino(G, P, origen, PREVIO);
    printf(" --%c-- ", leerArco(G, PREVIO, destino).modalidad);
  }
  printf("%s", leerVertices(G)[destino].alias);
}

/**
 * Pide dos alias e imprime el camino minimo entre ellos segun el criterio
 *@param G grafo
 *@param criterio CRITERIO_COSTE o CRITERIO_DURACION
 */
static void _caminoMinimoCreadores(TGRAFO G, int criterio) {
  char aliasOrigen[TAM_ALIAS];
  char aliasDestino[TAM_ALIAS];

  printf("\nEscribe el alias del creador de origen:");
  if (scanf(" %99s", aliasOrigen) != 1) {
    _errorLectura();
    return;
  }
  aliasOrigen[TAM_ALIAS - 1] = '\0';
  printf("\nEscribe el alias del creador de destino:");
  if (scanf(" %99s", aliasDestino) != 1) {
    _errorLectura();
    return;
  }
  aliasDestino[TAM_ALIAS - 1] = '\0';

  const int ORIGEN = _posicionPorAlias(G, aliasOrigen);
  const int DESTINO = _posicionPorAlias(G, aliasDestino);
  if (ORIGEN == -1) {
    printf("\nEl creador %s no existe\n", aliasOrigen);
    return;
  }
  if (DESTINO == -1) {
    printf("\nEl creador %s no existe\n", aliasDestino);
    return;
  }

  double D[MAXVERTICES][MAXVERTICES];
  int P[MAXVERTICES][MAXVERTICES];
  _floydWarshall(G, criterio, D, P);

  const char *NOMBRE_CRITERIO =
      (criterio == CRITERIO_COSTE) ? "coste" : "duracion";
  if (D[ORIGEN][DESTINO] >= INFINITO) {
    printf("\nEl camino minimo por %s entre %s y %s NO EXISTE\n",
           NOMBRE_CRITERIO, aliasOrigen, aliasDestino);
    return;
  }

  printf("\nCamino minimo por %s entre %s y %s:\n    ", NOMBRE_CRITERIO,
         aliasOrigen, aliasDestino);
  _imprimirCamino(G, P, ORIGEN, DESTINO);
  if (criterio == CRITERIO_COSTE) {
    printf("\n\n    Coste de la producción: %.2f €\n", D[ORIGEN][DESTINO]);
  } else {
    printf("\n\n    Duración total: %.2f h\n", D[ORIGEN][DESTINO]);
  }
}

/**
 * Avisa de que ha fallado la lectura de un dato
 */
static void _errorLectura(void) {
  printf("\nFallo al leer los datos, operacion cancelada.\n");
}

// Funcion privada que elimina el cambio de linea al final del string
static void _strip_line(char *linea) { linea[strcspn(linea, "\r\n")] = 0; }

// Funcion privada para procesar el token del creador
static void _procesarCreador(TGRAFO *G) {
  TIPOVERTICE creador = {0};
  char *token;
  int valido; // 1 mientras todos los campos leidos hasta ahora sean validos

  /* Alias */
  token = strtok(NULL, ";");
  /**
   * Comprobar que token no es NULL y copiar el alias en
   * creador.alias, respetando la longitud definida mediante
   * TAM_ALIAS y asegurando que la cadena termina en '\0' utilizando:
   *
   *
   */
  valido = token != NULL;
  if (valido) {
    strncpy(creador.alias, token, TAM_ALIAS - 1);
    creador.alias[TAM_ALIAS - 1] = '\0';
  }

  /* Categoria */
  token = strtok(NULL, ";");

  /**
   *  Comprobar que token no es NULL, convertir su contenido
   * a un valor entero y almacenarlo en creador.categoria usando atoi().
   */
  valido = valido && token != NULL;
  if (valido) {
    creador.categoria = atoi(token);
    valido = creador.categoria >= 1 && creador.categoria <= NUM_CATEGORIAS;
  }
  /* Colectivo */
  token = strtok(NULL, ";");

  /**
   * Comprobar que token no es NULL y copiar el colectivo en
   * creador.colectivo, respetando la longitud definida
   * mediante TAM_COLECTIVO y asegurando que la cadena
   * termina en '\0'.
   */
  valido = valido && token != NULL;
  if (valido) {
    strncpy(creador.colectivo, token, TAM_COLECTIVO - 1);
    creador.colectivo[TAM_COLECTIVO - 1] = '\0';
  }

  /**
   * Comprobar, mediante las operaciones publicas del TAD,
   * si el/la creador/a ya existe en el grafo.
   *
   * Si no existe, insertar creador en el grafo.
   */
  if (valido && !existeVertice(*G, creador) && crearVertice(G, creador) != -1) {
    return; // creador incorporado
  }
  fprintf(stderr,
          "Aviso: registro de creador ignorado (alias '%s'): campos "
          "incorrectos, creador repetido o red llena.\n",
          creador.alias);
}

static void _procesarColaboracion(TGRAFO *G) {
  TIPOVERTICE creadorOrigen = {0};
  TIPOVERTICE creadorDestino = {0};
  TIPOARCO colaboracion = {0};
  char *token;
  int posicionOrigen = -1;
  int posicionDestino = -1;
  int valido; // 1 mientras todos los campos leidos hasta ahora sean validos

  /* Alias del/de la creador/a de origen */
  token = strtok(NULL, ";");

  /**
   * Comprobar que token no es NULL y copiar el alias en
   * creadorOrigen.alias, respetando la longitud definida
   * mediante TAM_ALIAS y asegurando que la cadena termina
   * en '\0'.
   */
  valido = token != NULL;
  if (valido) {
    strncpy(creadorOrigen.alias, token, TAM_ALIAS - 1);
    creadorOrigen.alias[TAM_ALIAS - 1] = '\0';
  }
  /* Alias del/de la creador/a de destino */
  token = strtok(NULL, ";");

  /**
   * Comprobar que token no es NULL y copiar el alias en
   * creadorDestino.alias, respetando la longitud definida
   * mediante TAM_ALIAS y asegurando que la cadena termina
   * en '\0'.
   */
  valido = valido && token != NULL;
  if (valido) {
    strncpy(creadorDestino.alias, token, TAM_ALIAS - 1);
    creadorDestino.alias[TAM_ALIAS - 1] = '\0';
  }
  /* Coste de la colaboracion */
  token = strtok(NULL, ";");

  /**
   * Comprobar que token no es NULL, convertir su contenido
   * a un valor real y almacenarlo en colaboracion.coste con atof().
   */
  valido = valido && token != NULL;
  if (valido) {
    colaboracion.coste = atof(token);
    valido = colaboracion.coste >= 0;
  }

  /* Duracion de la colaboracion */
  token = strtok(NULL, ";");

  /**
   * Comprobar que token no es NULL, convertir su contenido
   * a un valor real y almacenarlo en colaboracion.duracion.
   */
  valido = valido && token != NULL;
  if (valido) {
    colaboracion.duracion = atof(token);
    valido = colaboracion.duracion > 0;
  }
  /* Modalidad de la colaboracion */
  token = strtok(NULL, ";");

  /**
   * Comprobar que token no es NULL y almacenar el carActer
   * correspondiente en colaboracion.modalidad.
   */
  valido = valido && token != NULL && _modalidadValida(token[0]);
  if (valido)
    colaboracion.modalidad = token[0];

  /**
   * Comprobar, mediante las operaciones publicas del TAD,
   * que creadorOrigen y creadorDestino existen en el grafo.
   *
   * Si alguno de ellos no existe, no se insertara la
   * colaboracion.
   */
  valido = valido && existeVertice(*G, creadorOrigen) &&
           existeVertice(*G, creadorDestino);
  /**
   * Obtener las posiciones de ambos vertices en el grafo
   * y almacenarlas en posicionOrigen y posicionDestino.
   */
  if (valido) {
    posicionDestino = posicionVertice(*G, creadorDestino);
    posicionOrigen = posicionVertice(*G, creadorOrigen);
  }
  /**
   * Comprobar que no existe previamente una colaboracion
   * entre ambos vertices (ni es de un creador consigo mismo).
   *
   * Si no existe, insertar colaboracion entre
   * posicionOrigen y posicionDestino mediante la operacion
   * publica correspondiente del TAD.
   *
   * No se insertara dos veces la colaboracion. La operacion
   * del TAD debera encargarse de mantener la simetria de la
   * matriz de adyacencia.
   */
  valido = valido && posicionOrigen != posicionDestino &&
           !existeArco(*G, posicionOrigen, posicionDestino);
  if (valido) {
    crearArco(G, posicionOrigen, posicionDestino, colaboracion);
  } else {
    fprintf(stderr,
            "Aviso: registro de colaboracion ignorado (%s--%s): campos "
            "incorrectos, creadores inexistentes, repetida o de un creador "
            "consigo mismo.\n",
            creadorOrigen.alias, creadorDestino.alias);
  }
}
// esta funcion te devuelve un array de todos los
// vertices destino de los arcos que forman junto con el vertice origen dado
// reutiliza las funciones existentes del TAD
static int *_leerArcosVertice(TGRAFO G, int pos1) {
  // paso 1: obtener vertices que hay en grafo(ya hay funcion)
  // paso 2: probar todos los vertices para ver si tienen arco (ya hay funcion)
  // paso 3: guardar posicion vertices destino arcos validos

  int n = leerN(G); // numero de vertices
  int *verticesDestino = malloc((n + 1) * sizeof *verticesDestino);
  if (verticesDestino == NULL)
    return NULL;

  TIPOVERTICE *vertices = leerVertices(G);

  int cantidad = 0; // guarda el numero de vertices guardados
  for (int i = 0; i < n; i++) {

    const int pos2 = posicionVertice(G, vertices[i]);
    if (existeArco(G, pos1, pos2)) {
      verticesDestino[cantidad++] = pos2;
    }
  }

  verticesDestino[cantidad] = -1; // centinela
  return verticesDestino;
}
/**
 *contabiliza los creadores que hay de la categoria dada
 *@param G grafo
 *@param categoria categoria del vertice
 */

static int _leerVerticesCategoria(TGRAFO G, int categoria) {
  TIPOVERTICE *vertices = leerVertices(G);
  const int N = leerN(G);
  int contador = 0;

  for (int i = 0; i < N; i++) {
    if (vertices[i].categoria == categoria)
      contador++;
  }
  return contador;
}
/**
 * contabiliza los arcos de la modalidad dada
 *@param G grafo
 *@param modalidad modalidad del arco
 */
static int _leerArcosModalidad(TGRAFO G, char modalidad) {
  const int N = leerN(G);
  int contador = 0;
  for (int i = 0; i < N; i++) {
    int *arcos = _leerArcosVertice(G, i);
    if (arcos == NULL)
      continue;
    for (int k = 0; arcos[k] >= 0; k++) {
      if (leerArco(G, i, arcos[k]).modalidad == modalidad) {
        contador++;
      }
    }
    free(arcos);
  }
  return contador / 2; // cada colaboracion son 2 arcos
}
/**
 *guarda en un csv los vertices del grafo
 *@param G grafo
 *@param fp proceso de guardado del csv
 */
static void _guardarVerticesDisco(TGRAFO G, FILE *fp) {
  TIPOVERTICE *vertices = leerVertices(G);
  const int N_VERTICES = leerN(G);
  for (int i = 0; i < N_VERTICES; i++) {
    fprintf(fp, "C;%s;%i;%s;;\n", vertices[i].alias, vertices[i].categoria,
            vertices[i].colectivo);
  }
}

/**
 *guarda en un csv los arcos del grafo
 *@param G grafo
 *@param fp proceso de guardado del csv
 */
static void _guardarArcosDisco(TGRAFO G, FILE *fp) {
  // Cada colaboracion se almacena como 2 arcos (matriz simetrica)
  // el csv solo guarda una direccion del arco
  // se acepta el arco en cualquiera de las 2 direcciones, por si la matriz
  // no estuviera simetrizada (se supone que si lo esta)
  TIPOVERTICE *vertices = leerVertices(G);
  const int N_VERTICES = leerN(G);

  for (int i = 0; i < N_VERTICES; i++) {
    for (int j = i + 1; j < N_VERTICES; j++) {
      if (existeArco(G, i, j) || existeArco(G, j, i)) {
        TIPOARCO arco =
            existeArco(G, i, j) ? leerArco(G, i, j) : leerArco(G, j, i);
        fprintf(fp, "A;%s;%s;%.2f;%.2f;%c\n", vertices[i].alias,
                vertices[j].alias, arco.coste, arco.duracion, arco.modalidad);
      }
    }
  }
}

/**
 * Escribe el grafo completo en un csv
 *@param G grafo
 *@param nombreArchivo ruta del archivo donde guardar
 *@return 1 si se ha guardado correctamente, 0 si ha habido algun error
 */
static int _escribirGrafo(TGRAFO G, const char *nombreArchivo) {
  FILE *fp = fopen(nombreArchivo, "w");
  if (fp == NULL) {
    perror("Error abriendo el archivo para guardar creadores");
    return 0;
  }

  _guardarVerticesDisco(G, fp);
  _guardarArcosDisco(G, fp);

  //* comprobar errores tanto de escritura como de cierre.
  const int ERROR_ESCRITURA = ferror(fp);
  const int ERROR_CIERRE = fclose(fp);

  if (ERROR_ESCRITURA || ERROR_CIERRE == EOF) {
    fprintf(stderr, "Error al guardar los creadores\n");
    return 0;
  }
  return 1;
}
