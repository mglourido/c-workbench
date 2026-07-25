# c-workbench

Repositorio de práctica de algoritmos en C. Claude genera el enunciado (`Problem.md`) de cada problema; el usuario escribe la solución en C.

## Idioma

- Todo el contenido escrito en el repo (nombres de carpetas, `Problem.md`) va **en inglés**.
- La conversación con el usuario en el chat va **en español**.

## Estructura de carpetas

El repositorio se organiza por **técnica/categoría** en la raíz, y cada técnica contiene una carpeta por problema:

```
<Technique>/
  <Problem Name>/
    Problem.md
    solution.c   (lo agrega el usuario, no Claude)
```

Ejemplos actuales de técnicas en la raíz:

- `Two pointers/` — problemas resueltos con dos punteros que se mueven uno hacia el otro, o slow/fast.
- `Three pointers/` — problemas que requieren tres punteros activos simultáneamente en la misma pasada (ej. `low`/`mid`/`high` en Dutch National Flag).
- `Sort + Two Pointers/` — problemas que combinan un paso de ordenamiento previo con two pointers (ej. 3Sum).

Cuando un nuevo problema no encaje claramente en una carpeta existente, crea una carpeta de técnica nueva en la raíz en vez de forzarlo en una que no corresponde.

### Cómo decidir la carpeta de un problema

- Si usa **un solo bucle externo + dos punteros** que se mueven dentro de cada iteración (aunque el bucle externo también sea un índice), sigue siendo **Two pointers** (o `Sort + Two Pointers` si antes hay que ordenar).
- Solo cuenta como **Three pointers** si los tres punteros se mueven de forma independiente y simultánea en una única pasada sobre la estructura (no un puntero fijo + dos que se mueven).
- Si combina una técnica previa (ordenar, hashing, etc.) con two/three pointers, usa el nombre compuesto `"<Técnica previa> + <Two/Three> Pointers"`.

## Nombres de carpetas

- Nombre del problema en formato título, en inglés, tal como aparecería en un enunciado de LeetCode (ej. `Container With Most Water`, `Trapping Rain Water`).
- Sin abreviar salvo que el nombre estándar del problema ya sea corto (ej. `3Sum`, `Two Sum`).
- Un espacio real en el nombre de la carpeta está bien (el repo ya lo usa así), no hace falta usar guiones ni camelCase.

## Formato de `Problem.md`

Cada `Problem.md` sigue esta estructura fija:

```markdown
# <Problem Name>

## Description

Explicación del problema, incluyendo qué técnica conviene usar y por qué
(ej. mencionar explícitamente "two pointers", "slow/fast", "sliding window", etc.,
y la complejidad esperada).

## Input

Descripción de los parámetros de entrada.

## Output

Descripción de qué debe devolver/producir la solución.

## Example

Al menos 2-3 bloques de ejemplo con Input/Output (y Explanation cuando aporte),
en bloques de código, para que el usuario los use como casos de prueba.

## Constraints

Rango de tamaños y valores esperados (estilo LeetCode).
```

Reglas para el contenido:

- Siempre incluir al menos un ejemplo simple y uno con un caso borde (arreglo vacío, un solo elemento, todos iguales, etc.) cuando aplique.
- La sección `Description` debe insinuar la técnica a usar (two/three pointers, slow/fast, sliding window) sin dar el código de la solución.
- No incluir código de solución en `Problem.md` — es solo el enunciado.

## Añadir un problema nuevo

1. Determinar la técnica/carpeta raíz correspondiente (crear una nueva si no encaja en las existentes).
2. Crear `"<Technique>/<Problem Name>/Problem.md"` siguiendo el formato de arriba.
3. Confirmar con el usuario en el chat, en español, en qué carpeta quedó y por qué (especialmente si la clasificación two/three pointers no es obvia).
4. No crear el archivo de solución en C — eso lo escribe el usuario.
