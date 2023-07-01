#include<stdio.h>
#include<stdlib.h>
#include "hash.h"

typedef struct Node{
    HashTableItem *value;
    struct Node *next;
} Node;

typedef struct{
    Node *head;
    Node *last;
    int size;
} ForwardList;

typedef struct HashTable{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
}HashTable;

typedef struct HashTableIterator{
    HashTable *h;
    int bucket;
    int indice_item;
}HashTableIterator;

HashTableIterator *hash_table_iterator(HashTable *h){
    HashTableIterator *iterator = (HashTableIterator*)calloc(1,sizeof(HashTableIterator));
    iterator->h = h;
    iterator->bucket = -1;
    iterator->indice_item = -1;
    return iterator;
}

int hash_table_size(HashTable *h){
    return h->table_size;
}

int hash_table_num_elems(HashTable *h){
    return h->n_elements;
}

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn){
    HashTable *h = (HashTable*)calloc(1,sizeof(HashTable));
    h->buckets = (ForwardList**)calloc(table_size,sizeof(ForwardList*));
    h->hash_fn = hash_fn;
    h->cmp_fn = cmp_fn;
    h->table_size = table_size;
    h->n_elements = 0;
    return h;
}

ForwardList *forward_list_construct(){
    ForwardList *l = (ForwardList *)calloc(1,sizeof(ForwardList));
    l->head = NULL;
    l->last = NULL;
    l->size = 0;
    return l;
}

Node *node_construct(HashTableItem *value, Node *next){
    Node *n = (Node *)calloc(1,sizeof(Node));
    n->next = next;
    n->value = value;
    return n;
}

void forward_list_push_front(ForwardList *l, HashTableItem *data){
    Node *novo = node_construct(data,l->head);
    l->head = novo;
    if(l->last == NULL){
        l->last = novo;
    }
    l->size = l->size + 1;
}

// funcao para insercao/atualizacao de pares chave-valor em O(1).
// Se a chave ja existir, atualiza o valor e retorna o valor antigo para permitir desalocacao.
void *hash_table_set(HashTable *h, void *key, void *val){
    int indice = h->hash_fn(h,key);
    HashTableItem *item = NULL;
    if(h->buckets[indice] == NULL){
        h->buckets[indice] = forward_list_construct();
    }else{
        Node *atual =  h->buckets[indice]->head;
        while(atual != NULL){
            item = atual->value;
            if(!h->cmp_fn(item->key,key)){
                break;
            }
            atual = atual->next;
        }
    }
    void *valor_antigo = NULL;
    if((item != NULL)&&(!h->cmp_fn(item->key,key))){
        valor_antigo = item->val;
        item->val = val;
    }else{
        item = (HashTableItem *)calloc(1,sizeof(HashTableItem));
        item->key = key;
        item->val = val;
        forward_list_push_front(h->buckets[indice],item);
    }
    return valor_antigo;
}

void *hash_table_get(HashTable *h, void *key){
    int indice = h->hash_fn(h,key);
    if(h->buckets[indice] == NULL){
        return NULL;
    }else{
        Node *atual =  h->buckets[indice]->head;
        HashTableItem *item = NULL;
        void *valor_achado = NULL;
        while(atual != NULL){
            item = atual->value;
            if(!h->cmp_fn(item->key,key)){
                valor_achado = item->val;
                break;
            }
            atual = atual->next;
        }
        return valor_achado;
    }
}

void *hash_table_pop(HashTable *h, void *key){
    int indice = h->hash_fn(h,key);
    if(h->buckets[indice] == NULL){
        return NULL;
    }else{
        Node *atual =  h->buckets[indice]->head,*past = NULL;
        HashTableItem *item = NULL;
        void *valor_achado = NULL;
        while(atual != NULL){
            item = atual->value;
            if((!h->cmp_fn(item->key,key))){
                valor_achado = item->val;
                //tirar node da lista
                if(h->buckets[indice]->head == atual){
                    h->buckets[indice]->head = atual->next;
                    if(atual == h->buckets[indice]->last){
                        h->buckets[indice]->head = NULL;
                    }
                }else{
                    if(atual == h->buckets[indice]->last){
                        h->buckets[indice]->last = past;
                        past->next = NULL;
                    }else{
                        past->next = atual->next;
                    }
                }
                h->buckets[indice]->size = h->buckets[indice]->size-1;
                h->n_elements = h->n_elements - 1;
                free(atual);
                free(item);
                break;
            }
            past = atual;
            atual = atual->next;
        }
        return valor_achado;
    }
}

void forward_list_clear(ForwardList *l){
    int tam = l->size;
    Node *atual = l->head,*next = NULL;
    for(int i = 0; i < tam; i++){
        if(i == 0){
            next = atual->next;
        }
        free(atual);
        atual = next;
        if(atual != NULL){
            next = atual->next;
        }
    }
    l->head = NULL;
    l->last = NULL;
    l->size = 0;
}

void hash_table_destroy(HashTable *h){
    HashTableIterator *it = hash_table_iterator(h);

    while (!hash_table_iterator_is_over(it))
    {
        HashTableItem *item = hash_table_iterator_next(it);
        free(item);
    }
    
    free(it);

    for(int i = 0; i < h->table_size; i++){
        if(h->buckets[i] != NULL){
            forward_list_clear(h->buckets[i]);
            free(h->buckets[i]);
        }
    }
    free(h->buckets);
    free(h);
}

int hash_table_iterator_is_over(HashTableIterator *it){
    HashTableIterator *it2 = hash_table_iterator(it->h);
    it2->bucket = it->bucket;
    it2->indice_item = it->indice_item;
    HashTableItem *item = hash_table_iterator_next(it2);
    free(it2);
    return (item == NULL);
}

HashTableItem *forward_list_get(ForwardList *l, int i){
    Node *atual = l->head;
    if(i >= l->size){
        return NULL;
    }else if(i < 0){
        return NULL;
    }else{
        for(int j = 1; j <= i; j++){
            atual = atual->next;
        }
    }
    return atual->value;
}

HashTableItem *hash_table_iterator_next(HashTableIterator *it){
    if(it->bucket == -1){
        it->bucket = 0;
    }
    HashTableItem *item;
    while(it->bucket < it->h->table_size){
        if(it->h->buckets[it->bucket] != NULL){
            item = forward_list_get(it->h->buckets[it->bucket],it->indice_item + 1);
            if(item == NULL){
                it->bucket = it->bucket + 1;
                it->indice_item = -1;
            }else{
                it->indice_item = it->indice_item + 1;
                break;
            }
        }else{
            it->bucket = it->bucket + 1;
        }
    }
    return item;
}

void hash_table_iterator_destroy(HashTableIterator *it){
    free(it);
}
