#include "hash.h"
#include "heap.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct HeapNode{
    void *key;
    double priority;
}HeapNode;

typedef struct Heap{
    HashTable *h;
    HeapNode *nodes;
    int size;
    int capacity;
}Heap;


Heap *heap_construct(HashTable *h){
    Heap *heap = (Heap *)calloc(1,sizeof(Heap));
    heap->h = h;
    heap->nodes = (HeapNode *)calloc(10,sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = 10;
    return heap;
}

void heap_swap(Heap *heap, int indice1, int indice2){
    if((heap->size >= 2)&&(indice1 != indice2)&&(indice1 != -1)&&(indice1 != -1)){
        int *i1 = (int *)calloc(1,sizeof(int));
        int *i2 = (int *)calloc(1,sizeof(int));
        *i1 = indice1;
        *i2 = indice2;
        int *valor1 = (int *)hash_table_set(heap->h,heap->nodes[indice1].key,i2);
        int *valor2 = (int *)hash_table_set(heap->h,heap->nodes[indice2].key,i1);
        free(valor1);
        free(valor2);
        void *aux_v = heap->nodes[indice1].key;
        double aux_d = heap->nodes[indice1].priority;
        heap->nodes[indice1].key = heap->nodes[indice2].key;
        heap->nodes[indice1].priority = heap->nodes[indice2].priority;
        heap->nodes[indice2].key = aux_v;
        heap->nodes[indice2].priority = aux_d;
    }
}

void heap_heapfy_up(Heap *heap,int indice_mudado){
    int indice = (indice_mudado - 1)/2, indice_anterior = indice_mudado;
    while(indice > 0){
        if(heap->nodes[indice].priority > heap->nodes[indice_anterior].priority){
            heap_swap(heap,indice,indice_anterior);
        }
        indice_anterior = indice;
        indice = (indice - 1)/2;
    }
    if(indice == 0){
        if(heap->nodes[indice].priority > heap->nodes[indice_anterior].priority){
            heap_swap(heap,indice,indice_anterior);
        }
    }
}

void *heap_push(Heap *heap, void *data, double priority){ 
    int *existe = (int *)hash_table_get(heap->h,data);
    int *indice = (int*)calloc(1,sizeof(int));
    if(existe == NULL){
        if(heap->capacity == heap->size){
            heap->capacity = heap->capacity*2;
            heap->nodes = (HeapNode *)realloc(heap->nodes,sizeof(HeapNode)*heap->capacity);
        }
        HeapNode *node = (HeapNode *)calloc(1,sizeof(HeapNode));
        node->key = data;
        node->priority = priority;
        heap->nodes[heap->size] = *node;
        *indice = heap->size;
        heap->size = heap->size + 1;
        hash_table_set(heap->h,data,indice);
        free(node);
        heap_heapfy_up(heap,heap->size-1);
        return NULL;
    }else{
        if(priority < heap->nodes[*existe].priority){
            heap->nodes[*existe].priority = priority;
            heap_heapfy_up(heap,*existe);
        }
        free(indice);
        return data;
    }
}

bool heap_empty(Heap *heap){
    return heap->size == 0;
}

void *heap_min(Heap *heap){
    return heap->nodes[0].key;
}

double heap_min_priority(Heap *heap){
    return heap->nodes[0].priority;
}

void heap_heapfy_down(Heap *heap){
    int i_parent = 0, i_left = 1, i_right = 2;
    while(i_left < heap->size){
        if(heap->nodes[i_left].priority < heap->nodes[i_parent].priority){
            if((i_right < heap->size)&&(heap->nodes[i_right].priority < heap->nodes[i_parent].priority)){
                double d_right = heap->nodes[i_parent].priority - heap->nodes[i_right].priority;
                double d_left = heap->nodes[i_parent].priority - heap->nodes[i_left].priority;
                if(d_left >= d_right){
                    heap_swap(heap,i_parent,i_left);
                    i_parent = i_left;
                }else{
                    heap_swap(heap,i_parent,i_right);
                    i_parent = i_right;
                }
            }else{
                heap_swap(heap,i_parent,i_left);
                i_parent = i_left;
            }
        }else{
            if((i_right < heap->size)&&heap->nodes[i_right].priority < heap->nodes[i_parent].priority){
                heap_swap(heap,i_parent,i_right);
                i_parent = i_right;
            }else{
                break;
            }
        }
        i_left = 2*i_parent + 1;
        i_right = 2*i_parent + 2;
    }
}

void *heap_pop(Heap *heap){
    if(heap->size >0){
        heap_swap(heap,0,heap->size-1);
        heap->size = heap->size - 1;
        heap_heapfy_down(heap);
        int *retorno = (int *)hash_table_pop(heap->h,heap->nodes[heap->size].key);
        free(retorno);
        return heap->nodes[heap->size].key;
    }else{
        return NULL;
    }
}

void heap_destroy(Heap *heap){
    free(heap->nodes);
    free(heap);
}