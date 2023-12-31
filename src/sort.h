#pragma once

typedef enum {
    QUICKSORT,
    BUBBLESORT,
    INSERTIONSORT,
    SELECTIONSORT,

    // Just to emulate a foreach
    NUM_SORT_ALGOS,
} sorting_algorithm;

void sort(int buf[], int bufsize, sorting_algorithm sa);

void quicksort(int buf[], int bufsize);
void bubblesort(int buf[], int bufsize);
void insertionsort(int buf[], int bufsize);
void selectionsort(int buf[], int bufsize);
