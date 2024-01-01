typedef struct list_t {
    void *items;
    int max_size;
    int cur_size;
} list_t;

void  list_reverse(list_t *list);
void  list_clear(list_t *list);
void  list_append(list_t *list, void *val);
void  list_remove(list_t *list, void *val);
void *list_pop(list_t *list);
int   list_contains(list_t *list, void *val);
void *list_get(list_t *list, int index);
