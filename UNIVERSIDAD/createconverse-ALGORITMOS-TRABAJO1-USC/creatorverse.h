#ifndef CREATORVERSE_H
#define CREATORVERSE_H

#include "abb.h"

/**
 * Crea el arbol, lee el archivo y lo almacena en el arbol
 * @param A Arbol.
 * @param nombreArchivo Ruta del archivo que contiene los creadores.
 */
void inicializarCreadores(TABB *A, const char *nombreArchivo);

/**
 * Anhade un creador a la base de datos
 * @param A Arbol.
 */
void anhadirCreador(TABB *A);

/**
 * Listado de creadores por orden alfabetico
 * @param A Arbol.
 */
void listarCreadores(TABB A);

/**
 * Elimina un creador de la base de datos
 * @param A Arbol.
 */
void eliminarCreador(TABB *A);

/**
 * Modifica los datos de un creador excepto su cola de retos
 * @param A Arbol
 */
void modificarCreador(TABB *A);

/**
 * Añade nuevos retos al final de la cola del creador indicado
 * @param A Arbol
 */
void nuevosRetos(TABB *A);

/**
 * Completa el primer reto del creador e indica el siguiente
 * @param A Arbol
 */
void completarReto(TABB *A);

/**
 * Busca un creador del arbol e imprime su info
 *@param A Arbol
*/
void buscarCreador(TABB A);

/**
 * Muestra todos los retos con dificultad maxima y el alias de sus creadores
 * Conserva el contenido y el orden de las colas
 * @param A Arbol
 */
void buscarRetoMasDificil(TABB A);

/**
 * Muestra todos los perfiles con el mayor numero de retos pendientes
 * Conserva el contenido y el orden de las colas siempre
 * @param A Arbol
 */
void buscarCreadoresConMasRetos(TABB A);

/**
 *Guarda los datos del arbol de creadores en un archivo indicado
 *@param A Arbol
 *@param nombreArchivo Ruta del archivo(con nombre y formato includio)
 */
void guardarCreadores(TABB A, const char *nombreArchivo);

#endif /* CREATORVERSE_H */
