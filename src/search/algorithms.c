
#include <math.h>
#include <stdio.h> 
#include <stdlib.h>
#include "algorithms.h"
#include "../ed/stack.h"
#include "../ed/queue.h"
#include "../ed/heap.h"

typedef struct Celula_expandida{
    Celula *celula;
    struct Celula_expandida *parent;
}Celula_expandida;

ResultData _default_result()
{
    ResultData result;

    result.caminho = NULL;
    result.custo_caminho = 0;
    result.nos_expandidos = 0;
    result.tamanho_caminho = 0;
    result.sucesso = 0;

    return result;
}

ResultData a_star(Labirinto *l, Celula inicio, Celula fim)
{
    // TODO!
    return _default_result();
}

void calcular_vizinhos_validos_pilha(Stack *pilha, Celula_expandida *atual,Labirinto *l){
    int linha_atual = atual->celula->y, coluna_atual = atual->celula->x,linha,coluna;
    Celula_expandida *vizinho = NULL;
    linha = linha_atual - 1;
    coluna = coluna_atual;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            stack_push(pilha,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual - 1;
    coluna = coluna_atual + 1;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
           vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            stack_push(pilha,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual;
    coluna = coluna_atual + 1;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            stack_push(pilha,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual + 1;
    coluna = coluna_atual + 1;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            stack_push(pilha,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual + 1;
    coluna = coluna_atual;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            stack_push(pilha,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual + 1;
    coluna = coluna_atual - 1;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            stack_push(pilha,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual;
    coluna = coluna_atual - 1;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            stack_push(pilha,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual - 1;
    coluna = coluna_atual - 1;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            stack_push(pilha,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }
}

ResultData depth_first_search(Labirinto *l, Celula inicio, Celula fim)
{
    ResultData result = _default_result();
    int alocados = 10;
    Stack *fronteira = stack_construct();
    Stack *visitado = stack_construct();
    Celula_expandida *celula = NULL,*celula_past = NULL,*celula_atual = NULL;
    celula_atual = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
    celula_atual->parent = NULL;
    celula_atual->celula = (Celula *)calloc(1,sizeof(Celula));
    celula_atual->celula->x = inicio.x;
    celula_atual->celula->y = inicio.y;
    stack_push(fronteira,celula_atual);
    labirinto_atribuir(l,inicio.y,inicio.x,FRONTEIRA);
    while(!stack_empty(fronteira)){
        celula_atual = (Celula_expandida *)stack_pop(fronteira);
        stack_push(visitado,celula_atual);
        result.nos_expandidos++;
        if((celula_atual->celula->x == fim.x)&&(celula_atual->celula->y == fim.y)){
            result.sucesso = 1;
            break;
        }
        calcular_vizinhos_validos_pilha(fronteira,celula_atual,l);
    }

    if(result.sucesso == 1){
        int dx, dy;
        celula = (Celula_expandida *)stack_pop(visitado);
        result.caminho = (Celula *)calloc(alocados,sizeof(Celula));
        while(1){
            result.caminho[result.tamanho_caminho] = *(celula->celula);
            result.tamanho_caminho++;
            if(celula->parent == NULL){
                break;
            }
            dx = celula->parent->celula->x - celula->celula->x;
            dy = celula->parent->celula->y - celula->celula->y;
            result.custo_caminho += sqrt(pow(dx, 2) + pow(dy, 2));
            if(alocados == result.tamanho_caminho){
                alocados = alocados*2;
                result.caminho = (Celula *)realloc(result.caminho,sizeof(Celula)*alocados);
            }
            if(result.tamanho_caminho == 1){
                celula_past = celula->parent;
                free(celula->celula);
                free(celula);
                celula = celula_past;
            }else{
                celula = celula->parent;
            }
        }
    }

    while(!stack_empty(visitado)){
        celula = stack_pop(visitado);
        free(celula->celula);
        free(celula);
    }
    while(!stack_empty(fronteira)){
        celula = stack_pop(fronteira);
        free(celula->celula);
        free(celula);
    }
    stack_destroy(fronteira);
    stack_destroy(visitado);
    return result;
}

void calcular_vizinhos_validos_fila(Queue *fila, Celula_expandida *atual,Labirinto *l){
    int linha_atual = atual->celula->y, coluna_atual = atual->celula->x,linha,coluna;
    Celula_expandida *vizinho = NULL;
    linha = linha_atual - 1;
    coluna = coluna_atual;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            queue_push(fila,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual - 1;
    coluna = coluna_atual + 1;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
           vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            queue_push(fila,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual;
    coluna = coluna_atual + 1;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            queue_push(fila,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual + 1;
    coluna = coluna_atual + 1;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            queue_push(fila,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual + 1;
    coluna = coluna_atual;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            queue_push(fila,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual + 1;
    coluna = coluna_atual - 1;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            queue_push(fila,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual;
    coluna = coluna_atual - 1;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            queue_push(fila,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }

    linha = linha_atual - 1;
    coluna = coluna_atual - 1;
    if(!(linha < 0 || linha >= labirinto_n_linhas(l) || coluna < 0 || coluna >= labirinto_n_colunas(l))){
        if((labirinto_obter(l,linha,coluna) != OCUPADO)&&(labirinto_obter(l,linha,coluna) != FRONTEIRA)){
            vizinho = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
            vizinho->celula = (Celula *)calloc(1,sizeof(Celula));
            vizinho->celula->x = coluna;
            vizinho->celula->y = linha;
            vizinho->parent = atual;
            queue_push(fila,vizinho);
            labirinto_atribuir(l,linha,coluna,FRONTEIRA);
        }
    }
}

ResultData breadth_first_search(Labirinto *l, Celula inicio, Celula fim)
{
    ResultData result = _default_result();
    int alocados = 10;
    Queue *fronteira = queue_construct();
    Stack *visitado = stack_construct();
    Celula_expandida *celula = NULL,*celula_past = NULL,*celula_atual = NULL;
    celula_atual = (Celula_expandida *)calloc(1,sizeof(Celula_expandida));
    celula_atual->parent = NULL;
    celula_atual->celula = (Celula *)calloc(1,sizeof(Celula));
    celula_atual->celula->x = inicio.x;
    celula_atual->celula->y = inicio.y;
    queue_push(fronteira,celula_atual);
    
    while(!queue_empty(fronteira)){
        celula_atual = (Celula_expandida *)queue_pop(fronteira);
        stack_push(visitado,celula_atual);
        if((celula_atual->celula->x == fim.x)&&(celula_atual->celula->y == fim.y)){
            result.sucesso = 1;
            break;
        }
        calcular_vizinhos_validos_fila(fronteira,celula_atual,l);
        result.nos_expandidos++;
    }

    if(result.sucesso == 1){
        int dx, dy;
        celula = (Celula_expandida *)stack_pop(visitado);
        result.caminho = (Celula *)calloc(alocados,sizeof(Celula));
        while(1){
            result.caminho[result.tamanho_caminho] = *(celula->celula);
            result.tamanho_caminho++;
            if(celula->parent == NULL){
                break;
            }
            dx = celula->parent->celula->x - celula->celula->x;
            dy = celula->parent->celula->y - celula->celula->y;
            result.custo_caminho += sqrt(pow(dx, 2) + pow(dy, 2));
            if(alocados == result.tamanho_caminho){
                alocados = alocados*2;
                result.caminho = (Celula *)realloc(result.caminho,sizeof(Celula)*alocados);
            }
            if(result.tamanho_caminho == 1){
                celula_past = celula->parent;
                free(celula->celula);
                free(celula);
                celula = celula_past;
            }else{
                celula = celula->parent;
            }
        }
    }

    while(!stack_empty(visitado)){
        celula = stack_pop(visitado);
        free(celula->celula);
        free(celula);
    }
    while(!queue_empty(fronteira)){
        celula = queue_pop(fronteira);
        free(celula->celula);
        free(celula);
    }
    queue_destroy(fronteira);
    stack_destroy(visitado);
    return result;
}

ResultData dummy_search(Labirinto *l, Celula inicio, Celula fim)
{
    int max_path_length = 0;
    float dx, dy;

    ResultData result = _default_result();

    max_path_length = abs(fim.x - inicio.x) + abs(fim.y - inicio.y);
    result.caminho = (Celula *)malloc(sizeof(Celula) * max_path_length);
    result.sucesso = 1;

    Celula atual = inicio;
    result.caminho[result.tamanho_caminho++] = atual;
    result.nos_expandidos++;

    while ((atual.x != fim.x) || (atual.y != fim.y))
    {
        dx = fim.x - atual.x;
        dy = fim.y - atual.y;

        if (dx != 0)
            dx /= fabs(dx);

        if (dy != 0)
            dy /= fabs(dy);

        atual.x += (int)dx;
        atual.y += (int)dy;

        if (labirinto_obter(l, atual.y, atual.x) == OCUPADO || (atual.x > labirinto_n_colunas(l) - 1) || (atual.y > labirinto_n_linhas(l) - 1) || (atual.x < 0) || (atual.y < 0))
        {
            result.sucesso = 0;
            free(result.caminho);
            result.caminho = NULL;
            return result;
        }

        result.caminho[result.tamanho_caminho++] = atual;
        result.nos_expandidos++;
        result.custo_caminho += sqrt(pow(dx, 2) + pow(dy, 2));
    }

    return result;
}
