#ifndef CREATORNET_H
#define CREATORNET_H

#include "grafo.h"


/**
 * Inicializar el grafo leyendo datos de un archivo o iniciando vacio.
 * @param G Puntero al grafo.
 * @param argc numero de cadenas por linea de comandos (argumento de main)
 * @param argv cadenas por linea de comandos: ejecutable -f archivo
 */
void inicializar(TGRAFO *G, int argc, char **argv);

// FUNCIONES PUBLICAS QUE SE LLAMAN DESDE MAIN

/** Opción del menu, introducir un vertice en el grafo
 *cada vertice es un creador
 *@param G grafo
 */
void anhadirVertice(TGRAFO *G);

/** Opción del menú, eliminar un vértice del grafo
 *cada vertice es un creador
 *@param G grafo
 */
void eliminarVertice(TGRAFO *G);

/** Opción del menú, crear una relación entre dos vértices
 *cada arco es una colaboracion
 *@param G grafo
 */
void anhadirArco(TGRAFO *G);

/** Opción del menú, eliminar una relación entre dos vértices
 * cada arco es una colaboracion, eliminar una colaboracion
 *@param G grafo
 */
void eliminarArco(TGRAFO *G);

/** Opción del menú, imprimir el grafo
 *mostrar creadores y colaboraciones
 *@param G grafo
 */
void imprimirGrafo(TGRAFO G);

/** Opción del menú, imprimir arcos de un vertice
 * mostrar colaboraciones de un creador
 *void imprimirArcosVertice(TGRAFO G);
 *@param G grafo
 */
void imprimirArcosVertice(TGRAFO G);

/**
 *Calcula e imprime: n total creadores, n total de creadores por categoria, n
 * colaboraciones totales registradas (cada colaboracion se cuenta 1vez), n
 * colaboraciones de cada modalidad, coste medio(en meses),  duracion media,
 * creador con mayor numero de colaboraciones
 *
 *@param G grafo
 */
void mostrarEstadisticas(TGRAFO G);
/**
 *Calcula e imprime el arbol de expansion minima utilizando el algoritmo de
 * Prim.
 *@param G grafo
 */
void redColaboracionCosteMinimo(TGRAFO G);

/**
 * calcula e imprime el camino de coste minimo de dos creadores (Floyd-Warshall)
 *@param G grafo
 */
void caminosCosteMinimoCreadores(TGRAFO G);

/**
 *  calcula e imprime el camino de duracion minima entre 2 creadores
 * (Floyd-Warshall)
 *@param G grafo
 */
void caminosDuracionMinimaCreadores(TGRAFO G);

/**
 * Guarda un csv de los datos del grafo
 *@param G grafo
 *@param argc numero de argumentos de entrada
 *@param argv el texto de cada arumento de entrada
 *@return 1 si se ha guardado correctamente. Si falla al escribir, se pide otro
 *        nombre de archivo hasta lograrlo; devuelve 0 solo si no se puede leer
 *        mas entrada
 */
int guardarGrafo(TGRAFO G, int argc, char **argv);
#endif /* CREATORNET_H */
