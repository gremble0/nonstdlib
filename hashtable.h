#include <stdint.h>

typedef struct ht_entry {
    uint8_t *key;
    uint8_t *value;
    struct ht_entry *next;
} ht_entry;

typedef struct ht {
    ht_entry **entries;
    uint32_t n_entries;
    uint32_t max_size;
} ht;
