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

typedef struct HashTable {
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
    return NULL;
}

void hash_table_destroy(HashTable *h){

}

int hash_table_iterator_is_over(HashTableIterator *it){
    return 1;
}

HashTableItem *hash_table_iterator_next(HashTableIterator *it){
    return NULL;
}

void hash_table_iterator_destroy(HashTableIterator *it){

}
