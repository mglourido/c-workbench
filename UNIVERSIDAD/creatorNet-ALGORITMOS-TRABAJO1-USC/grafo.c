#include "./grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
/////////////////////////////////////////////////////////// TIPOS DE DATOS

// Estructura privada
struct tipografo {
  int N;                                // número de vértices del grafo
  TIPOVERTICE VERTICES[MAXVERTICES];    // vector de vértices
  TIPOARCO A[MAXVERTICES][MAXVERTICES]; // matriz de adyacencia
};

#define MODALIDAD_VACIA ' '
static const TIPOARCO ARCO_VACIO = {0, 0, MODALIDAD_VACIA};

//////////////////////////////////////////////////////////////// FUNCIONES
// inicializa los valores de los Arcos TIPOARCO
void _declararValoresArco(TIPOARCO *A);

/*
 * Esta función devuelve 0 si los dos nodos son iguales
 * y 1 en otro caso.
 */
int _compararVertices(TIPOVERTICE V1, TIPOVERTICE V2) {
  return strcmp(V1.alias, V2.alias);
}

// Creación del grafo con 0 nodos
void crearGrafo(TGRAFO *G) {
  *G = (struct tipografo *)malloc(sizeof(struct tipografo));
  (*G)->N = 0;
}
// Destruye el grafo
void destruirGrafo(TGRAFO *G) {
  free(*G);
  *G = NULL;
}

// Devuelve 1 si el grafo G existe y 0 en caso contrario
int existeGrafo(TGRAFO G) { return (G != NULL); }
// Devuelve 1 si el vértice Vert existe en el grafo G
int existeVertice(TGRAFO G, TIPOVERTICE V) {
  return (posicionVertice(G, V) >= 0);
}
// Devuelve 1 si VERTICES(pos1) y VERTICES(pos2) son vértices adyacentes
int existeArco(TGRAFO G, int pos1, int pos2) {
  // hay arco si la posicion no esta marcada como vacia (se usa la modalidad y
  // no el coste, porque un arco puede tener coste 0)
  return (G->A[pos1][pos2].modalidad != MODALIDAD_VACIA);
}

// Inserta un vértice en el grafo, devuelve -1 si no ha podido insertarlo por
// estar el grafo lleno
int crearVertice(TGRAFO *G, TIPOVERTICE Vert) {
  int i;
  if ((*G)->N == MAXVERTICES) {
    // Se ha llegado al maximo numero de vertices
    return -1;
  }

  const int NUEVO = (*G)->N;
  (*G)->N++;
  (*G)->VERTICES[NUEVO] = Vert;
  for (i = 0; i <= NUEVO; i++) { // incluye la diagonal
    (*G)->A[i][NUEVO]=ARCO_VACIO;
    (*G)->A[NUEVO][i]=ARCO_VACIO;
  }
  return NUEVO;
}

// Borra un vertice del grafo
void borrarVertice(TGRAFO *G, TIPOVERTICE Vert) {
  int F, C, P, N = (*G)->N;
  P = posicionVertice(*G, Vert);
  if (P == -1) {
    return;
  }
  for (F = P; F < N - 1; F++) {
    (*G)->VERTICES[F] = (*G)->VERTICES[F + 1];
  }
  for (C = P; C < N - 1; C++) {
    for (F = 0; F < N; F++) {
      (*G)->A[F][C] = (*G)->A[F][C + 1];
    }
  }
  for (F = P; F < N - 1; F++) {
    for (C = 0; C < N; C++) {
      (*G)->A[F][C] = (*G)->A[F + 1][C];
    }
  }
  (*G)->N--;
}

// Crea el arco de relación entre VERTICES(pos1) y VERTICES(pos2)
// Se guarda en ambos sentidos (la colaboracion es simetrica)
void crearArco(TGRAFO *G, int pos1, int pos2, TIPOARCO datos) {
  (*G)->A[pos1][pos2] = datos;
  (*G)->A[pos2][pos1] = datos;
}
// Borra el arco de relación entre VERTICES(pos1) y VERTICES(pos2)
void borrarArco(TGRAFO *G, int pos1, int pos2) {
  (*G)->A[pos1][pos2] = ARCO_VACIO;
}

// Devuelve la posición del vértice Vert en el vector VERTICES del grafo G
// Si devuelve -1 es porque no encontró el vértice
int posicionVertice(TGRAFO G, TIPOVERTICE V) {
  int contador = 0;
  // comparo V con todos los vertices almacenados en VERTICES
  while (contador < G->N) {
    // if (G->VERTICES[contador]==V)  //encontré la posicion de V
    if (_compararVertices(G->VERTICES[contador], V) == 0) {
      return contador;
    }
    contador++;
  }
  return -1;
}
// Devuelve el número de vértices del grafo G
int leerN(TGRAFO G) { return G->N; }
// Devuelve el vector de vértices VERTICES del grafo G
TIPOVERTICE *leerVertices(TGRAFO G) { return G->VERTICES; }

TIPOARCO leerArco(TGRAFO G, int pos1, int pos2) { return (G->A[pos1][pos2]); }
