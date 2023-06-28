#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

typedef struct Queue{
    void **vetor;
    int inicio;
    int final;
    int size;
    int n_alocados;
}Queue;

Queue *queue_construct(){
    Queue *fila = (Queue*)calloc(1,sizeof(Queue));
    fila->inicio = -1;
    fila->final = 0;
    fila->n_alocados = 50;
    fila->size = 0;
    fila->vetor = (void**)calloc(fila->n_alocados,sizeof(void*));
    return fila;
}

void queue_organize(Queue *queue){
    void **prev = queue->vetor;
    queue->vetor = (void **)calloc(queue->n_alocados,sizeof(void*));
    int j = queue->inicio;
    for(int i = 0; i < queue->size; i++){
        queue->vetor[i] = prev[j];
        j++;
        if(j == queue->size){
            j = 0;
        }
    }
    queue->inicio = 0;
    queue->final = queue->size;
    free(prev);
}

void queue_push(Queue *queue, void *data){
    if(queue->size == queue->n_alocados){
        queue->n_alocados = queue->n_alocados * 2;
        queue_organize(queue);
    }
    int indice = queue->final;
    queue->size = queue->size + 1;
    queue->final = queue->final + 1;
    if(queue->final == queue->n_alocados){
        queue->final = 0;
    }
    queue->vetor[indice] = data;
    if(queue->inicio == -1){
        queue->inicio = 0;
    }
}

bool queue_empty(Queue *queue){
    return !queue->size;
}

void *queue_pop(Queue *queue){
    queue->size = queue->size - 1;
    int indice = queue->inicio;
    queue->inicio = queue->inicio + 1;
    if(queue->inicio == queue->n_alocados){
        queue->inicio = 0;
    }
    return queue->vetor[indice];
}

void queue_destroy(Queue *queue){
    free(queue->vetor);
    free(queue);
}