#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"


hashmap *hm_create(){
    
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

void hm_free(hashmap *h){
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
