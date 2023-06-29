
#include "heap.h"

typedef struct Heap{
    Hash *h;
    double *priority;
    int size;
    int capacity;
}Heap;


Heap *heap_construct(HashTable *h){
    Heap *heap = (Hash *)calloc(1,sizeof(Hash));
    heap->h = h;
    heap->priority = (Void *)calloc(10,sizeof(void *));
    heap->size = 0;
    heap->capacity = 10;
    return heap;
}

void heap_push(Heap *heap, void *data, double priority){
    hash_table_set(h,priority,data);
    //realloc
    //inserir no final
    //heapfy
}

bool heap_empty(Heap *heap){
    hash_table_iterator *it = hash_table_iterator();
    bool retorno = hash_table_iterator_next();
    hash_table_iterator_destroy(it); 
    return retorno;
}

void *heap_min(Heap *heap){
    return hash_table_get(heap->h,heap->priority[0]);
}

double heap_min_priority(Heap *heap){
    return heap->priority[0];
}

void *heap_pop(Heap *heap){
    //tirar do heap
    //tirar do hash
}

void heap_destroy(Heap *heap){
    free(heap->priority);
    free(heap);
}