#include "stack.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct Stack{
    void **vetor;
    int size;
    int n_alocados;
}Stack;

Stack *stack_construct(){
    Stack *pilha = (Stack*)calloc(1,sizeof(Stack));
    pilha->size = 0;
    pilha->n_alocados = 50;
    pilha->vetor = (void**)calloc(pilha->n_alocados,sizeof(void*));
    return pilha;
}

void stack_push(Stack *stack, void *data){
    if(stack->size == stack->n_alocados){
        stack->n_alocados *= 2;
        stack->vetor = (void**)realloc(stack->vetor, stack->n_alocados*sizeof(void*));
    }
    stack->vetor[stack->size] = data;
    stack->size = stack->size + 1;
}

bool stack_empty(Stack *stack){
    return !(stack->size);
}

void *stack_pop(Stack *stack){
    stack->size = stack->size - 1;
    return stack->vetor[stack->size];
}

void stack_destroy(Stack *stack){
    free(stack->vetor);
    free(stack);
}