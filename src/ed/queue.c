#include<stdio.h>
#include<stdlib.h>
#include "queue.h"
#include "deque.h"

typedef struct Queue{
    Deque *deque_fila;
}Queue;

Queue *queue_construct(){
    Queue *fila = (Queue*)calloc(1,sizeof(Queue))
    fila->deque_fila = deque_construct();
    return fila;
}

void queue_push(Queue *queue, void *data){
    deque_push_back(queue->deque_fila,data);
}

bool queue_empty(Queue *queue){
    return !deque_size(queue->deque_fila);
}

void *queue_pop(Queue *queue){
    return deque_pop_front(queue->deque_fila);
}

void queue_destroy(Queue *queue){
    deque_destroy(queue->deque_fila);
    free(queue);
}