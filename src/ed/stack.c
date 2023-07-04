#include "stack.h"
#include<stdio.h>
#include<stdlib.h>
#include "deque.h"

typedef struct Stack{
    Deque *deque_stack;
}Stack;

Stack *stack_construct(){
    Stack *pilha = (Stack*)calloc(1,sizeof(Stack));
    pilha->deque_stack = deque_construct();
    return pilha;
}

void stack_push(Stack *stack, void *data){
    deque_push_front(stack->deque_stack,data);
}

bool stack_empty(Stack *stack){
    return !(deque_size(stack->deque_stack));
}

void *stack_pop(Stack *stack){
    return deque_pop_front(stack->deque_stack);
}

void stack_destroy(Stack *stack){
    deque_destroy(stack->deque_stack);
    free(stack);
}