#ifndef FUNCIONESDELTDALISTA_H_INCLUDED
#define FUNCIONESDELTDALISTA_H_INCLUDED


typedef struct list list;

/**
 @typedef
 Prototipo de funcion para eliminar de memoria el objeto que se guarda dentro de la lista.

 @param object Puntero al objecto guardado.
 */
typedef void (*list_release_object_callback)(void *object);

/**
 Crea un nuevo puntero de tipo List.

 @return Puntero a la nueva List.
 */
extern list *list_create (list_release_object_callback release);

/**
 Crea un nuevo puntero de tipo List.

 @return Puntero a la nueva List.
 */
extern list *list_create_empty (void);

/**
 Devuele el primer dato de la List.

 Complejidad: O(1)

 @param list Puntero a la List.
 @return Puntero al dato contenido en la cabeza.
 */
extern void *list_first (list *list);

/**
 Devuele el siguiente dato de la List.

 Complejidad: O(1)

 @param list Puntero a la List.
 @return Puntero al dato.

 Ejemplo:

 @code
 void *data = list_first(list);

 while (data != NULL) {
 // Aqui puede manipular el dato o imprimirlo.
 data = list_next(list);
 }
 */
extern void *list_next (list *list);

/**
 Devuelve el ultimo dato de la List.

 Complejidad: O(1)

 @param list Puntero a la List.
 @return Puntero al dato.
 */
extern void *list_last (list *list);

/**
 Devuele el anterior dato de la List.

 Complejidad: O(1)

 @param list Puntero a la List.
 @return Puntero al dato.

 @code
 void *data = list_last(list);

 while (data != NULL) {
 // Aqui puede manipular el dato o imprimirlo.
 data = list_prev(list);
 }
 */
extern void *list_prev (list *list);

/**
 Cantidad de elementos en la List.

 Complejidad: O(1)

 @param list Puntero a la List.
 @return Cantidad de elementos en la List.
 */
extern long list_size (list *list);

/**
 Prueba si la List está vacía.

 Complejidad: O(1)

 @param list Puntero a la List.
 @return 1 (true) si y solo si la List no contiene elementos; 0 (false) lo contrario.
 */
extern int list_empty (list *list);

/**
 Inserta un elemento en al inicio de la List.

 Complejidad: O(1)

 @param list Puntero a la List.
 @param data Puntero al dato que se quiere guardar.
 */
extern void list_push_front (list *list, const void *data);

/**
 Inserta un elemento al final de la lista.

 Complejidad: O(1)

 @param list Puntero a la List.
 @param data Puntero al dato que se quiere guardar.
 */
extern void list_push_back (list *list, const void *data);

/**
 Inserta un elemento despues del current. El current se actualiza cuando se reccore la lista con las funciones firstList, etc.

 Complejidad: O(1)

 @param list Puntero a la List.
 @param data Puntero al dato que se quiere guardar.
 */
extern void list_push_current (list *list, const void *data);

/**
 Elimina el nodo del inicio de la lista,
 si esta activada la funcion release, esta eliminara
 de la memoria el puntero que apunta hacia el objeto.

 Complejidad: O(1)

 @param list Puntero a la List.
 @return Puntero del dato eliminado.
 */
extern void *list_pop_front (list *list);

/**
 Elimina el nodo final de la lista,
 si esta activada la funcion release, esta eliminara
 de la memoria el puntero que apunta hacia el objeto.

 Complejidad: O(1)

 @param list Puntero a la List.
 @return Puntero del dato eliminado.
 */
extern void *list_pop_back (list *list);

/**
 Elimina el nodo en donde se encuentre el current,
 actualiza el current al siguiente de este.
 Si esta activada la funcion release, esta eliminara
 de la memoria el puntero que apunta hacia el objeto.

 Complejidad: O(1)

 @param list Puntero a la List.
 @return Puntero del dato eliminado.
 */
extern void *list_pop_current (list *list);

/**
 Elimina todos los nodos de la lista,
 si esta activada la funcion release, esta eliminara
 de la memoria el puntero que apunta hacia el objeto.

 Complejidad: O(n)

 @param list Puntero a la List.
 */
extern void list_release (list **list);




#endif
