
#include <stdio.h>
#include <stdlib.h>

#include "forward_list.h"

Node *node_construct(data_type value, Node *next){
    Node *n = (Node *)calloc(1,sizeof(Node));
    n->next = next;
    n->value = value;
}

void node_destroy(Node *n){
    free(n);
}

ForwardList *forward_list_construct(){
    ForwardList *l = (ForwardList *)calloc(1,sizeof(ForwardList));
    l->head = NULL;
    l->last = NULL;
    l->size = 0;
}

int forward_list_size(ForwardList *l){
    return l->size;
}

//Funcionamento da função de comparação esperada: iguais = 0, diferentes != 0
data_type forward_list_find(ForwardList *l, void *key, int (*cmp_fn)(data_type data, void *key)){
    Node *atual = l->head;
    while(atual != NULL){
        if(!cmp(atual->value,key)){
            return atual->value
            break;
        }
        atual = atual->next;
    }
    return NULL;
}

void forward_list_push_front(ForwardList *l, data_type data){
    Node *novo = node_construct(data,l->head)
    l->head = novo;
    if(l->last == NULL){
        l->last = novo
    }
    l->size = l->size + 1;
}

void forward_list_push_back(ForwardList *l, data_type data){
    Node *novo = node_construct(data,NULL)
    if(l->last == NULL){
        l->head = novo;
        l->last = novo;
    }else{
        l->last->next = novo;
        l->last = novo;
    }
    l->size = l->size + 1;
}

void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){
    Node *atual = l->head;
    printf("Imprimindo Lista:\n")
    while(atual != NULL){
        print_fn(atual->value);
        atual = atual->next;
    }
}

data_type forward_list_get(ForwardList *l, int i){
    Node *atual = l->head;
    if(i >= forward_list_size(l)){
        printf("Índice acima do tamanho dessa lista.\n");
        exit(1);
    }else if(i < 0){
        printf("Índice abaixo de 0.\n");
        exit(1);
    }else{
        for(int j = 1; j <= i; j++){
            atual = atual->next;
        }
    }
    return atual->value
}

data_type forward_list_pop_front(ForwardList *l){
    Node *destruir = l->head;
    data_type retorno = destruir->value;
    l->head = destruir->next;
    node_destroy(destruir);
    l->size = l->size - 1;
    return retorno;
}

ForwardList *forward_list_reverse(ForwardList *l){
    ForwardList *new_list = forward_list_construct();
    Node *atual = l->head;
    for(int i = 0; i < l->size; i++){
        forward_list_push_back(new_list,atual->value);
        atual = atual->next;
    }
    return new_list;
}

void forward_list_clear(ForwardList *l){
    int tam = forward_list_size(l);
    Node *atual = l->head;
    for(int i = 0; i < tam; i++){
        node_destroy(atual);
        atual = atual->next;
    }
}

void forward_list_remove(ForwardList *l, data_type val){

}

void forward_list_unique(ForwardList *l){

}

void forward_list_cat(ForwardList *l, ForwardList *m){

}

void forward_list_sort(ForwardList *l){

}

void forward_list_destroy(ForwardList *l){
    forward_list_clear(l);
    free(l);
}