typedef struct list_t {
    void *items;
    int max_size;
    int cur_size;
} list_t;

void  list_reverse(list_t *arr);
void  list_clear(list_t *arr);
void  list_append(list_t *arr, void *val);
void  list_remove(list_t *arr, void *val);
int   list_contains(list_t *arr, void *val);
void *list_get(list_t *arr, int index);
