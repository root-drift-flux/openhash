#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

static size_t hash_key(const char *key)
{
    size_t hash = 14695981039346656037UL;   // FNV offset basis (64-bit) 
    for (const char *p = key; *p; p++) {
        hash ^= (unsigned char)*p;           // XOR in the byte 
        hash *= 1099511628211UL;             // multiply by FNV prime 
    }

    return hash;
}

hashmap *hm_create()
{
    
    hashmap *h = malloc(sizeof(hashmap));
    if (h == NULL) {
        return NULL;
    }

    h->slots = calloc(16, sizeof(slot));
    if (h->slots == NULL) {
            free(h);
            return NULL;
    }

    h->capacity = 16;
    h->count = 0;
    return h;
}

void hm_free(hashmap *h)
{
    if (h == NULL){
        return;
    }

    for (size_t i = 0; i < h->capacity; i++){
        if (h->slots[i].state == SLOT_OCCUPIED) {
                free(h->slots[i].key);
        }
    }

    free(h->slots);
    free(h);
    
}

int hm_put(hashmap *h, const char *key, int value) 
{
	size_t index = hash_key(key) % h->capacity; // add key 

    while (h->slots[index].state == SLOT_OCCUPIED) {   // box taken?
        if (strcmp(h->slots[index].key, key) == 0) {   // by this same key?
            h->slots[index].value = value;             // update, done
            return 0;
        }
        
        index = (index + 1) % h->capacity;             // else walk to next box
    }

    h->slots[index].key = strdup(key);
    if (h->slots[index].key == NULL) {
        return -1;
    }

    h->slots[index].value = value;
    h->slots[index].state = SLOT_OCCUPIED;
    h->count++;
    return 0;
}

int hm_get(hashmap *h, const char *key, int *out_value)
{
   size_t index = hash_key(key) % h->capacity;

   while (h->slots[index].state != SLOT_EMPTY){
        if (h->slots[index].state == SLOT_OCCUPIED &&
            strcmp(h->slots[index].key, key) == 0){
            *out_value = h->slots[index].value;
            return 0;
        }

        index = (index + 1) % h->capacity;
   }
    
   return -1;
}






