#include "hashmap.h"
#include <stdio.h>

int main(void){
    
    hashmap *h= hm_create();
    
    hm_put(h, "cat", 3);
    hm_put(h, "dog", 7);
    hm_put(h, "bird", 42);

    int value;

    if (hm_get(h, "dog", &value) == 0)
        printf("dog = %d\n", value);
    else
        printf("dog not found\n");

    if (hm_get(h, "cat", &value) == 0)
        printf("cat = %d\n", value);
    else
        printf("cat not found\n");

    if (hm_get(h, "fish", &value) == 0)
        printf("fish = %d\n", value);
    else
        printf("fish not found\n");

    hm_free(h);
    return 0;

}
