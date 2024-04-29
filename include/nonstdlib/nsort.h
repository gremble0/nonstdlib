#pragma once

typedef enum {
  SORT_QUICKSORT,
  SORT_BUBBLESORT,
  SORT_INSERTIONSORT,
  SORT_SELECTIONSORT,
} sorting_algorithm;

void sort(int *arr, int size, sorting_algorithm sa);
void bubblesort(int *arr, int size);
void insertionsort(int *arr, int size);
void quicksort(int *arr, int size);
void selectionsort(int *arr, int size);
