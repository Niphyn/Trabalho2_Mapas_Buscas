#include<stdlib.h>
#include<stdio.h>
#include "deque.h"

#define TAM_BLOCO 1

//uma base
typedef struct Deque{
    void ***blocos;
    int bloco_inicial;
    int bloco_final;
    int indice_inicial;
    int indice_final;
    int n_blocos;
}Deque;

//uma base
Deque *deque_construct(){
    Deque *d = (Deque *)calloc(1,sizeof(Deque));
    d->blocos = (void ***)calloc(5,sizeof(void**));
    d->bloco_inicial = 2;
    d->bloco_final = 2;
    d->blocos[d->bloco_inicial] = (void **)calloc(TAM_BLOCO,sizeof(void*));
    d->indice_inicial = 0;
    d->indice_final = 0;
    d->n_blocos = 5;
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
        Deque *novo_deque = (Deque *)calloc(1,sizeof(Deque));
        novo_deque->blocos = (void ***)calloc((d->n_blocos*2 + 1),sizeof(void**));
        novo_deque->bloco_inicial = d->n_blocos + 1 - d->n_blocos/2;
        novo_deque->bloco_final = d->n_blocos + 1 + d->n_blocos/2;
        //novo_deque->blocos[novo_deque->bloco_inicial] = (void **)calloc(TAM_BLOCO,sizeof(void*));
        novo_deque->indice_inicial = d->indice_inicial;
        d->indice_final = d->indice_final;
        d->n_blocos = d->n_blocos*2 + 1;
        for(int i = 0; i <d->n_blocos;i++){
            novo_deque->blocos[novo_deque->bloco_inicial + i] = d->blocos[i];
        }
        free(d->blocos);
        free(d);
        d = novo_deque;
    }
}

//uma base
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

//uma base
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

//uma base
void *deque_pop_front(Deque *d){
    int idx_bloco, idx_indice,prox_indice;
    idx_indice = d->indice_inicial;
    prox_indice = idx_indice + 1;
    idx_bloco = d->bloco_inicial;
    void *retorno = d->blocos[idx_bloco][idx_indice];
    if(prox_indice == TAM_BLOCO){
        prox_indice = 0;
        if((idx_bloco != d->bloco_inicial)||(idx_bloco != d->bloco_final)){
            free(d->blocos[idx_bloco]);
            idx_bloco = idx_bloco + 1;
        }
    }
    d->indice_inicial = prox_indice;
    d->bloco_inicial = idx_bloco;
    return retorno;
}

//com problemas no input9.txt
void *deque_pop_back(Deque *d){
    int idx_bloco, idx_indice;
    idx_indice = d->indice_final - 1;
    idx_bloco = d->bloco_final;
    void *retorno;
    if(idx_indice == -1){
        idx_indice = TAM_BLOCO - 1;
        if((idx_bloco != d->bloco_inicial)||(idx_bloco != d->bloco_final)){
            free(d->blocos[idx_bloco]);
        }
        idx_bloco = idx_bloco -1;
    }
    retorno = d->blocos[idx_bloco][idx_indice];
    d->indice_final = idx_indice;
    d->bloco_final = idx_bloco;
    return retorno;
}

//uma base
int deque_size(Deque *d){
    return (d->bloco_final - d->bloco_inicial)*TAM_BLOCO + d->indice_final - d->indice_inicial;
}

//uma base
void *deque_get(Deque *d, int idx){
    int pos_item, bloco_idx, item_idx;
    pos_item = idx + d->indice_inicial;
    bloco_idx = pos_item/TAM_BLOCO + d->bloco_inicial;
    item_idx = pos_item%TAM_BLOCO;
    return d->blocos[bloco_idx][item_idx];
}

//uma base
void deque_destroy(Deque *d){
    for(int i = d->bloco_inicial; i <=d->bloco_final;i++){       
        free(d->blocos[i]);
    }
    free(d->blocos);
    free(d);
}