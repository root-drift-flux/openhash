# openhash

A hash map in C, built from scratch to sharpen my systems programming.
Open addressing with linear probing.

> **Status:** in progress. A learning project — I'm implementing this
> from the ground up to get fluent writing (not just reading) low-level C.

## Design

- **Open addressing, linear probing.** All entries live in one contiguous
  slot array rather than in per-bucket linked lists. On a collision, the
  insert probes forward to the next open slot. This keeps lookups
  cache-friendly, since probed slots are adjacent in memory.
- **Three slot states** — empty, occupied, tombstone. Tombstones mark
  deleted entries so a deletion doesn't break the probe chain that later
  lookups depend on.
- **String keys, owned by the map.** Keys are copied on insert and freed
  on removal, so callers keep ownership of their own strings.
- **FNV-1a** for hashing.

## API

```c
hashmap *hm_create(void);
void     hm_free(hashmap *h);
int      hm_put(hashmap *h, const char *key, int value);
int      hm_get(hashmap *h, const char *key, int *out_value);
int      hm_remove(hashmap *h, const char *key);
```

## Building

```sh
gcc -std=c11 -Wall -Wextra -g hashmap.c main.c -o test
```

## Roadmap

- [ ] Core create / free
- [ ] put / get / remove
- [ ] Load-factor–triggered resize (rehash into a larger table)
- [ ] Test suite + valgrind-clean
