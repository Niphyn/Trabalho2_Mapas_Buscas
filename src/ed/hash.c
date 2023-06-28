#include "hash.h"
#include "forward_list.h"

typedef struct HashTable {
    ForwardList **buckest;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
}HashTable;

typedef struct HashTableIterator{
    HashTable *h;
    HashTableItem *item;
    int bucket;
    int indice_item;
}HashTableIterator;

HashTableIterator *hash_table_iterator(HashTable *h){
    HashTableIterator *iterator = (HashTableIterator*)calloc(1,sizeof(HashTableIterator));
    iterator->h = h;
    int i = 0;
    while(i < h->table_size){
        if(h->bucket[i] != NULL){
            if(forward_list_size(h->bucket[i]) != 0){
                break;
            }
        }
        i++;
    }
    iterator->bucket = i;
    if(i != h->table_size){
        iterator->indice_item = 0;
        iterator->item = (HashTableItem*)forward_list_get(h->buckets[i],indice_item);
    }else{
        iterator->indice_item = -1;
        iterator->item = NULL;
    }
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
    h->buckest = (ForwardList**)calloc(table_size,sizeof(ForwardList*));
    h->hash_fn = hash_fn;
    h->cmp_fn = cmp_fn;
    h->table_size = table_size;
    h->n_elements = 0;
    return h;
}

void *hash_table_set(HashTable *h, void *key, void *val){
    HashTableItem *item_atualizado = NULL;
    void *retorno = NULL
    int i = h->hash_fn(h,key);
    if(h->buckets[i] == NULL){
        h->buckets[i] = forward_list_construct();
    }
    item_atualizado = (HashTableItem*)forward_list_find(h->buckets[i],key,h->cmp_fn,);
    if(item_atualizado != NULL){
        retorno = item_atualizado->val;
        item_atualizado->val = val;
    }else{
        HashTableItem *item = (HashTableItem*)calloc(1,sizeof(HashTableItem));
        item->key = key;
        item->val = val;
        forward_list_push_front(h->buckets[i],item);
        h->n_elements = h->n_elements + 1;
    }
    return retorno;
}

void *hash_table_get(HashTable *h, void *key){
    int i = h->hash_fn(h,key);
    return forward_list_find(h->buckets[i],key,h->cmp_fn);
}

void *hash_table_pop(HashTable *h, void *key){
    void *n = NULL;
    int i = h->hash_fn(h,key);
    HashTableItem item = (HashTableItem*)hash_table_get(h,key);
    if(item == NULL){
        return NULL;
    }else{
        n = item->val;
        forward_list_remove(h->buckets[i],item);
        free(item);
        h->n_elements = h->n_elements-1;
        return n;
    }
}

void hash_table_destroy(HashTable *h){
    HashTableIterator *iterator = hash_table_iterator(h);
    HashTableItem item = iterator->item;
    while(item != NULL){
        free(item);
        item = hash_table_iterator_next(iterator);
    }
    for(int i = 0; i < h->table_size; i++){
        forward_list_destroy(h->buckets[i]);
    }
    hash_table_destroy(iterator);
    free(h);
}

int hash_table_iterator_is_over(HashTableIterator *it){
    if(it->item == NULL){
        return 1;
    }else{
        return 0;
    }
}

HashTableItem *hash_table_iterator_next(HashTableIterator *it){
    if(it->indice_item + 1 < forward_list_size(it->h->buckets[it->bucket])){
        it->indice_item = indice_item + 1;
        it->item = forward_list_get(it->h->buckets[it->bucket],it->indice_item);
        return it->item;
    }else{
        int i = it->bucket;
        while(i < it->h->table_size){
            if(){

                }
            }
        }
        if(i >= it->h->table_size){
            return NULL;
        }else{
            
        }
    }
}

void hash_table_iterator_destroy(HashTableIterator *it){
    free(it);
}