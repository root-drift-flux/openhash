#ifndef HASHMAP_H
#define HASHMAP_H
#include <stddef.h>

typedef enum {
	SLOT_EMPTY,
	SLOT_OCCUPIED,
	SLOT_TOMBSTONE

} slot_state;


typedef struct {
    char        *key;
    int         value;
    slot_state  state;
} slot;


typedef struct {
    slot    *slots;
    size_t  capacity;
    size_t  count;
} hashmap;

hashmap *hm_create(void);
void    hm_free(hashmap *h);
int     hm_put(hashmap *h, const char *key, int value);
int     hm_get(hashmap *h, const char *key, int *out_value);
int     hm_remove(hashmap *h, const char *key);

#endif
