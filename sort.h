typedef enum {
    QUICKSORT,
    BUBBLESORT,
} sorting_algorithm;

void sort(int buf[], int bufsize, sorting_algorithm sa);

void quicksort(int buf[], int bufsize);
void bubblesort(int buf[], int bufsize);
