#include<stdlib.h>
#include<stdio.h>
#include "deque.h"

#define TAM_BLOCO 5
#define N_BLOCO 5

typedef struct Deque{
    void ***blocos;
    int bloco_inicial;
    int bloco_final;
    int indice_inicial;
    int indice_final;
    int n_blocos;
}Deque;

Deque *deque_construct(){
    Deque *d = (Deque *)calloc(1,sizeof(Deque));
    d->blocos = (void ***)calloc(N_BLOCO,sizeof(void**));
    d->bloco_inicial = N_BLOCO/2 - 1;
    d->bloco_final = N_BLOCO/2 - 1;
    d->blocos[d->bloco_inicial] = (void **)calloc(TAM_BLOCO,sizeof(void*));
    d->indice_inicial = 0;
    d->indice_final = 0;
    d->n_blocos = N_BLOCO;
    return d;
}

void deque_centralizar(Deque *d){
    void ***prev = d->blocos;
    void ***novo_blocos = (void ***)calloc(d->n_blocos,sizeof(void**));
    int b_ocupados = d->bloco_final - d->bloco_inicial + 1;
    int idx_bloco_inicial = (d->n_blocos - b_ocupados)/2;
    int idx_bloco_final = idx_bloco_inicial + b_ocupados - 1;

    for(int i = 0; i <b_ocupados;i++){
        novo_blocos[idx_bloco_inicial + i] = (void **)calloc(TAM_BLOCO,sizeof(void*));
    }
    int indice_bloco = idx_bloco_inicial;
    int indice_item = d->indice_inicial;
    for(int i = 0; i < deque_size(d); i++){
        novo_blocos[indice_bloco][indice_item] = deque_get(d,i);
        indice_item++;
        if(indice_item == TAM_BLOCO){
            indice_bloco++;
            indice_item = 0;
        }
    }
    for(int i = d->bloco_inicial; i <=d->bloco_final;i++){       
        free(prev[i]);
    }
    free(prev);
    d->bloco_inicial = idx_bloco_inicial;
    d->bloco_final = idx_bloco_final;
    d->blocos = novo_blocos;
}

void deque_realocar(Deque *d){
    int b_ocupados = d->bloco_final - d->bloco_inicial + 1; 
    int b_vazios = d->n_blocos - b_ocupados;
    if(b_vazios >= 2){
        deque_centralizar(d);
    }else{
        void ***prev = d->blocos;
        d->n_blocos = d->n_blocos*2 + 1;
        void ***novo_blocos = (void ***)calloc(d->n_blocos,sizeof(void**));
        int b_ocupados = d->bloco_final - d->bloco_inicial + 1;
        int idx_bloco_inicial = (d->n_blocos - b_ocupados)/2;
        int idx_bloco_final = idx_bloco_inicial + b_ocupados - 1;

        for(int i = 0; i <b_ocupados;i++){
            novo_blocos[idx_bloco_inicial + i] = (void **)calloc(TAM_BLOCO,sizeof(void*));
        }
        int indice_bloco = idx_bloco_inicial;
        int indice_item = d->indice_inicial;
        for(int i = 0; i < deque_size(d); i++){
            novo_blocos[indice_bloco][indice_item] = deque_get(d,i);
            indice_item++;
            if(indice_item == TAM_BLOCO){
                indice_bloco++;
                indice_item = 0;
            }
        }
        for(int i = d->bloco_inicial; i <=d->bloco_final;i++){       
            free(prev[i]);
        }
        free(prev);
        d->bloco_inicial = idx_bloco_inicial;
        d->bloco_final = idx_bloco_final;
        d->blocos = novo_blocos;
    }
}

void deque_push_back(Deque *d, void *val){
    int indice = d->indice_final;
    int bloco = d->bloco_final;
    if(indice == TAM_BLOCO){
        indice = 0;
        bloco = bloco + 1;
        if(bloco == d->n_blocos){
            deque_realocar(d);
            bloco = d->bloco_final + 1;
        }
        d->blocos[bloco] = (void**)calloc(TAM_BLOCO,sizeof(void*));
    }
    d->blocos[bloco][indice] = val;
    d->indice_final = indice + 1;
    d->bloco_final = bloco;
}

void deque_push_front(Deque *d, void *val){
    int indice = d->indice_inicial - 1;
    int bloco = d->bloco_inicial;
    if(indice == -1){
        indice = TAM_BLOCO - 1;
        bloco = bloco - 1;
        if(bloco == -1){
            deque_realocar(d);
            bloco = d->bloco_inicial - 1;
        }
        d->blocos[bloco] = (void**)calloc(TAM_BLOCO,sizeof(void*));
    }
    d->blocos[bloco][indice] = val;
    d->indice_inicial = indice;
    d->bloco_inicial = bloco;
}

void *deque_pop_front(Deque *d){
    int idx_bloco, idx_indice,prox_indice;
    idx_indice = d->indice_inicial;
    prox_indice = idx_indice + 1;
    idx_bloco = d->bloco_inicial;
    void *retorno = d->blocos[idx_bloco][idx_indice];
    if(prox_indice == TAM_BLOCO){
        prox_indice = 0;
        free(d->blocos[idx_bloco]);
        idx_bloco = idx_bloco + 1;
    }
    d->indice_inicial = prox_indice;
    d->bloco_inicial = idx_bloco;
    return retorno;
}

void *deque_pop_back(Deque *d){
    int idx_bloco, idx_indice;
    idx_indice = d->indice_final - 1;
    idx_bloco = d->bloco_final;
    void *retorno;
    if(idx_indice == -1){
        idx_indice = TAM_BLOCO - 1;
        free(d->blocos[idx_bloco]);
        idx_bloco = idx_bloco -1;
    }
    retorno = d->blocos[idx_bloco][idx_indice];
    d->indice_final = idx_indice;
    d->bloco_final = idx_bloco;
    return retorno;
}

int deque_size(Deque *d){
    return (d->bloco_final - d->bloco_inicial)*TAM_BLOCO + d->indice_final - d->indice_inicial;
}

void *deque_get(Deque *d, int idx){
    int pos_item, bloco_idx, item_idx;
    pos_item = idx + d->indice_inicial;
    bloco_idx = pos_item/TAM_BLOCO + d->bloco_inicial;
    item_idx = pos_item%TAM_BLOCO;
    return d->blocos[bloco_idx][item_idx];
}

void deque_destroy(Deque *d){
    for(int i = d->bloco_inicial; i <=d->bloco_final;i++){       
        free(d->blocos[i]);
    }
    free(d->blocos);
    free(d);
}
