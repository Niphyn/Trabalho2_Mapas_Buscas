
#include <stdio.h>
#include <stdlib.h>

#include "forward_list.h"

//Testado
Node *node_construct(data_type value, Node *next){
    Node *n = (Node *)calloc(1,sizeof(Node));
    n->next = next;
    n->value = value;
    return n;
}

//Testado
void node_destroy(Node *n){
    free(n);
}

//Testado
ForwardList *forward_list_construct(){
    ForwardList *l = (ForwardList *)calloc(1,sizeof(ForwardList));
    l->head = NULL;
    l->last = NULL;
    l->size = 0;
    return l;
}

//Testado
int forward_list_size(ForwardList *l){
    return l->size;
}

//Funcionamento da função de comparação esperada: iguais = 0, diferentes != 0
data_type forward_list_find(ForwardList *l, void *key, int (*cmp_fn)(data_type data, void *key)){
    printf("Achando nó %p\n",l->head);
    Node *atual = l->head;
    while(atual != NULL){
        if(!cmp_fn(atual->value,key)){
            return atual->value;
            break;
        }
        atual = atual->next;
    }
    return NULL;
}

//Testado
void forward_list_push_front(ForwardList *l, data_type data){
    Node *novo = node_construct(data,l->head);
    l->head = novo;
    if(l->last == NULL){
        l->last = novo;
    }
    l->size = l->size + 1;
}

//Testado
void forward_list_push_back(ForwardList *l, data_type data){
    Node *novo = node_construct(data,NULL);
    if(l->last == NULL){
        l->head = novo;
        l->last = novo;
    }else{
        l->last->next = novo;
        l->last = novo;
    }
    l->size = l->size + 1;
}

//Testado
void forward_list_print(ForwardList *l, void (*print_fn)(data_type)){
    Node *atual = l->head;
    printf("Lista:[");
    while(atual != NULL){
        print_fn(atual->value);
        if(atual->next != NULL){
            printf(",");
        }
        atual = atual->next;
    }
    printf("]\n");
}

//Testado
data_type forward_list_get(ForwardList *l, int i){
    Node *atual = l->head;
    if(i >= forward_list_size(l)){
        //printf("Índice acima do tamanho dessa lista.\n");
        return NULL;
    }else if(i < 0){
        //printf("Índice abaixo de 0.\n");
        return NULL;
    }else{
        for(int j = 1; j <= i; j++){
            atual = atual->next;
        }
    }
    return atual->value;
}

//Testado
data_type forward_list_pop_front(ForwardList *l){
    Node *destruir = l->head;
    data_type retorno = destruir->value;
    l->head = destruir->next;
    if(l->head == NULL){
        l->last = NULL;
    }
    node_destroy(destruir);
    l->size = l->size - 1;
    return retorno;
}

//Testado
ForwardList *forward_list_reverse(ForwardList *l){
    ForwardList *new_list = forward_list_construct();
    Node *atual = l->head;
    for(int i = 0; i < l->size; i++){
        forward_list_push_front(new_list,atual->value);
        atual = atual->next;
    }
    return new_list;
}

//Testado
void forward_list_clear(ForwardList *l){
    int tam = forward_list_size(l);
    Node *atual = l->head,*next = NULL;
    for(int i = 0; i < tam; i++){
        if(i == 0){
            next = atual->next;
        }
        node_destroy(atual);
        atual = next;
        if(atual != NULL){
            next = atual->next;
        }
    }
    l->head = NULL;
    l->last = NULL;
    l->size = 0;
}

//Testado
void forward_list_remove(ForwardList *l, data_type val){
    Node *atual = l->head,*past = NULL;
    while(atual != NULL){
        if(atual->value == val){
            if(past == NULL){
                atual = atual->next;
                forward_list_pop_front(l);
            }else{
                if(l->last == atual){
                    l->last = past;
                    past->next = NULL;
                    node_destroy(atual);
                    atual = NULL;
                    l->size = l->size - 1;
                }else{
                    past->next = atual->next;
                    node_destroy(atual);
                    atual = past->next;
                    l->size = l->size - 1;
                }
            }
        }else{
            past = atual;
            atual = atual->next;
        }
    }
}

//Testado
void forward_list_unique(ForwardList *l){
    Node *atual, *past, *buscar = l->head;
    while(buscar != NULL){
        atual = buscar->next;
        past = buscar;
        while(atual != NULL){
            if(atual->value == buscar->value){
                if(atual == l->last){
                    l->last = past;
                    past->next = NULL;
                    node_destroy(atual);
                    atual = NULL;
                    past = NULL;
                }else{
                    past->next = atual->next;
                    node_destroy(atual);
                    atual = past->next;
                }         
            }else{
                past = atual;
                atual = atual->next;
            }
        }
        buscar = buscar->next;
    }
}

//Testado
void forward_list_cat(ForwardList *l, ForwardList *m){
    Node *atual = m->head;
    while(atual != NULL){
        forward_list_push_front(l,atual->value);
        atual = atual->next;
    }
}

//Não implementado
void forward_list_sort(ForwardList *l){
}

//Testado
void forward_list_destroy(ForwardList *l){
    forward_list_clear(l);
    free(l);
}