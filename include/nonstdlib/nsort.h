#pragma once

typedef enum {
  QUICKSORT,
  BUBBLESORT,
  INSERTIONSORT,
  SELECTIONSORT,
} sorting_algorithm;

void sort(int *arr, int size, sorting_algorithm sa);
void bubblesort(int *arr, int size);
void insertionsort(int *arr, int size);
void quicksort(int *arr, int size);
void selectionsort(int *arr, int size);
