#pragma once

#define ht_prototype(type)                                                  \
typedef struct type##_ht_entry_t {                                          \
    const char *key;                                                        \
    const type *value;                                                      \
} type##_ht_entry_t;                                                        \
                                                                            \
typedef struct type##_ht_t {                                                \
    type##_ht_entry_t **entries;                                            \
    uint32_t n_entries;                                                     \
    uint32_t max_entries;                                                   \
} type##_ht_t;                                                              \
                                                                            \
type##_ht_t *type##_ht_init(uint32_t init_size);                            \
void type##_ht_free(type##_ht_t *table);                                    \
                                                                            \
const type *type##_ht_get(type##_ht_t *table, const char *key);             \
void type##_ht_put(type##_ht_t *table, const char *key, const type *value); \
void type##_ht_print(type##_ht_t *table);                                   \
                                                                            \
uint32_t type##_hash(const char *key);                                      \
void type##_ht_expand(type##_ht_t *table);

#define ht_impl(type)                                                                         \
/**                                                                                           \
 * @brief djb2 hash function                                                                  \
 *                                                                                            \
 * @return index into a hash table (needs to be %'d by table size)                            \
 */                                                                                           \
uint32_t type##_hash(const char *key) {                                                       \
    uint32_t hash = 5381;                                                                     \
                                                                                              \
    for (size_t i = 0; i < strlen(key); ++i) {                                                \
        hash = hash * 33 + key[i];                                                            \
    }                                                                                         \
                                                                                              \
    return hash;                                                                              \
}                                                                                             \
                                                                                              \
/**                                                                                           \
 * @brief Initialize an empty hash table allocated on the heap                                \
 *                                                                                            \
 * @param init_size the initial size of the hash table, can be changed by ht_put              \
 * @return a malloc'd hash table                                                              \
 */                                                                                           \
type##_ht_t *type##_ht_init(uint32_t init_max_entries) {                                      \
    type##_ht_t *new_ht = malloc(sizeof(type##_ht_t));                                        \
    new_ht->n_entries = 0;                                                                    \
    new_ht->max_entries = init_max_entries;                                                   \
    new_ht->entries = malloc(sizeof(type##_ht_entry_t) * init_max_entries);                   \
                                                                                              \
    for (size_t i = 0; i < init_max_entries; ++i) {                                           \
        new_ht->entries[i] = NULL;                                                            \
    }                                                                                         \
                                                                                              \
    return new_ht;                                                                            \
}                                                                                             \
                                                                                              \
/**                                                                                           \
 * @brief frees memory allocated for hash table                                               \
 *                                                                                            \
 * @param table table to free memory for                                                      \
 */                                                                                           \
void type##_ht_free(type##_ht_t *table) {                                                     \
    for (size_t i = 0; i < table->max_entries; ++i) {                                         \
        free(table->entries[i]);                                                              \
    }                                                                                         \
                                                                                              \
    free(table->entries);                                                                     \
    free(table);                                                                              \
}                                                                                             \
                                                                                              \
/**                                                                                           \
 * @brief Doubles the size of a hash table                                                    \
 *                                                                                            \
 * @param table hash table to expand the size of                                              \
 */                                                                                           \
void type##_ht_expand(type##_ht_t *table) {                                                   \
    uint32_t prev_max_entries = table->max_entries;                                           \
    table->max_entries *= 2;                                                                  \
    table->entries = realloc(table->entries, sizeof(type##_ht_entry_t) * table->max_entries); \
    table->n_entries = 0; /* Will be incremented in the loop by calling ht_put */             \
                                                                                              \
    /* Loop through table and reindex based on new size */                                    \
    for (size_t i = 0; i < prev_max_entries; ++i) {                                           \
        if (table->entries[i] == NULL) {                                                      \
            continue;                                                                         \
        }                                                                                     \
                                                                                              \
        type##_ht_entry_t *entry = table->entries[i];                                         \
        table->entries[i] = NULL; /* TODO: memory management */                               \
        type##_ht_put(table, entry->key, entry->value);                                       \
    }                                                                                         \
}                                                                                             \
                                                                                              \
/**                                                                                           \
 * @brief Get an element from a hash table                                                    \
 *                                                                                            \
 * @param table table to get from                                                             \
 * @param key key to get                                                                      \
 * @return value of the given key                                                             \
 */                                                                                           \
const type *type##_ht_get(type##_ht_t *table, const char *key) {                              \
    uint32_t index = type##_hash(key) % table->max_entries;                                   \
    type##_ht_entry_t *entry = table->entries[index];                                         \
    if (entry == NULL) {                                                                      \
        return NULL;                                                                          \
    }                                                                                         \
                                                                                              \
    while (entry->key != key) {                                                               \
        if (entry == NULL) {                                                                  \
            return NULL;                                                                      \
        }                                                                                     \
        entry = table->entries[index++];                                                      \
    }                                                                                         \
                                                                                              \
    return entry->value;                                                                      \
}                                                                                             \
                                                                                              \
/**                                                                                           \
 * @brief Put (insert) a value into a hash table                                              \
 *                                                                                            \
 * @param table table to put into                                                             \
 * @param key key to put in                                                                   \
 * @param value value to put in                                                               \
 */                                                                                           \
void type##_ht_put(type##_ht_t *table, const char *key, const type *value) {                  \
    if (table->n_entries + 1 > table->max_entries / 2) {                                      \
        type##_ht_expand(table);                                                              \
    }                                                                                         \
                                                                                              \
    uint32_t hash_index = type##_hash(key) % table->max_entries;                              \
    type##_ht_entry_t *existing_entry = table->entries[hash_index];                           \
                                                                                              \
    if (existing_entry == NULL) {                                                             \
        type##_ht_entry_t *new_entry = malloc(sizeof(type##_ht_entry_t));                     \
        new_entry->key = key;                                                                 \
        new_entry->value = value;                                                             \
        table->entries[hash_index] = new_entry;                                               \
        ++table->n_entries;                                                                   \
        return;                                                                               \
    }                                                                                         \
                                                                                              \
    if (existing_entry->key == key) {                                                         \
        existing_entry->value = value;                                                        \
        return;                                                                               \
    }                                                                                         \
                                                                                              \
    type##_ht_entry_t *new_entry = malloc(sizeof(type##_ht_entry_t));                         \
    new_entry->key = key;                                                                     \
    new_entry->value = value;                                                                 \
                                                                                              \
    while (table->entries[++hash_index] != NULL);                                             \
                                                                                              \
    table->entries[hash_index] = new_entry;                                                   \
    ++table->n_entries;                                                                       \
}
