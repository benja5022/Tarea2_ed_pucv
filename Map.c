#include "Map.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

typedef struct Node Node;

static Node * _createNode(const void * key, const void * data);

struct Node {
    const void * key;
    /*! Puntero al dato */
    const void * data;

    /*! Puntero al siguiente nodo */
    Node * next;

    /*! Puntero al anterior nodo */
    Node * prev;
};

struct Map {
    /*! Puntero al incio (cabeza) de la lista */
    Node * head;

    /*! Puntero al final (cola) de la lista */
    Node * tail;

    /*! Punteor para poder recorrer la lista */
    Node * current;

    MapCompareCallBack is_equal;

    /*! Cantidad de elemento en la lista */
    long count;
};

static Node* _createNode(const void * key, const void * data) {
    Node  * new = (Node *)malloc(sizeof(Node));

    assert(new != NULL);

    new->key = key;
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}


Map * createMap(MapCompareCallBack is_equal) {
    Map * new = (Map *)malloc(sizeof(Map));
    assert(new != NULL); // No hay memoria para reservar la Mapa.
    new->head = new->tail = new->current = NULL;
    new->count = 0;
    new->is_equal = is_equal;
    return new;
}

long MapCount(Map * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return 0;

    return list->count;
}

int emptyMap(Map * list) {
    assert(list != NULL); // list no puede ser NULL.
    return list->count == 0;
}

void * firstMap(Map * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return NULL;

    list->current = list->head;

    return (void *)list->current->data;
}

void * nextMap(Map * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL || list->current == NULL || list->current->next == NULL) return NULL;

    list->current = list->current->next;

    return (void *)list->current->data;
}

void * lastMap(Map * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return NULL;

    list->current = list->tail;

    return (void *)list->current->data;
}

void * prevMap(Map * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL || list->current == NULL || list->current->prev == NULL) return NULL;

    list->current = list->current->prev;

    return (void *)list->current->data;
}
//**************************************
void _pushFront(Map * list, const void * key, const void * value) {
    assert(list != NULL); // list no puede ser NULL.

    Node * new = _createNode(key, value);

    if (list->head == NULL) {
        list->tail = new;
    } else {
        new->next = list->head;
        list->head->prev = new;
    }

    list->head = new;
    list->count += 1;
}

//*********************
void insertMap(Map * list, const void * key, const void * value){

    _pushFront (list, key, value);

}

void * _popFront(Map * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return NULL;

    Node * aux = list->head;

    void * data = (void *)aux->data;

    if (list->head == list->tail) {
        list->tail = list->head = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    free(aux);

    list->count -= 1;

    return data;
}

void * _popBack(Map * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return NULL;

    Node * aux = list->tail;

    void * data = (void *)aux->data;

    if (list->tail == list->head) {
        list->tail = list->head = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    free(aux);

    list->count -= 1;

    return data;
}
//**************************
void* searchMapString(Map * list, const void * key) {
    assert(list != NULL); // list no puede ser NULL.
    Node* aux = NULL;//= list->head;
    //the minimum element
    if(list ->head == NULL){
        return NULL;
    }
    for(aux=list->head ; aux != NULL ; aux = aux->next){

        if(strcmp((const char *) key, (const char *) aux -> data) == 0 )
        {
            break;
        }
    }

    list->current=aux;
    if (list->head == NULL || list->current == NULL) return NULL;

    return (void *) aux->data;
}

void* searchMapCarrito(Map * list, const void * key) {
    assert(list != NULL); // list no puede ser NULL.
    Node* aux = NULL;//= list->head;
    //the minimum element
    if(list ->head == NULL){
        return NULL;
    }
    for(aux=list->head ; aux != NULL ; aux = aux->next){

        if(strcmp((const char *) key, (const char *) aux->key) == 0 )
        {
            break;
        }
    }

    list->current=aux;
    if (list->head == NULL || list->current == NULL) return NULL;

    return (void *) aux->data;
}
//****************************************

// searchMap original
void* searchMap(Map * list, const void * key) {
    assert(list != NULL); // list no puede ser NULL.


    Node* aux= list->head;
    //the minimum element
    while (aux && list->is_equal(aux->key,key)==0 ) aux=aux->next;

    list->current=aux;
    if (list->head == NULL || list->current == NULL) return NULL;


    return (void *) aux->data;
}



void * eraseMap(Map * list, const void * key) {
    assert(list != NULL); // list no puede ser NULL.

    Node* aux= list->head;
    //the minimum element
    while (aux && list->is_equal(aux->key,key)==0 ) aux=aux->next;

    list->current=aux;
    if (list->head == NULL || list->current == NULL) return NULL;

    if (list->current == list->head) {
        return _popFront(list);
    } else if (list->current == list->tail) {
        return _popBack(list);
    } else {
        if (aux->next != NULL) {
            aux->next->prev = aux->prev;
        }

        if (aux->prev != NULL) {
            aux->prev->next = aux->next;
        }
    }

    void * data = (void *)aux->data;

    list->current = aux->next;

    free(aux);

    list->count -= 1;

    return data;
}

void removeAllMap(Map * list) {
    assert(list != NULL); // list no puede ser NULL.

    while (list->head != NULL) {
        _popFront(list);
    }
}

