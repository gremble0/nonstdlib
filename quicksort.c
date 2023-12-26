#include <stdio.h>

#include "quicksort.h"

void quicksort(int buf[], int start, int end) {
    // basecase
    if (start >= end) {
        return;
    }

    // int pivot = (buf[0] + buf[end - 1]) / 2;
    // int pivot = buf[end / 2];
    int pivot = buf[end - 1];

    printf("start: %d, end: %d\n", start, end);
    for (int i = 0; i < 7; i++) {
        printf("%d: %d, ", i, buf[i]);
    }
    printf("\n");

    int left_i = 0, right_i = end - 1;
    // loop up until the second to last element in array
    while (buf[left_i] < pivot) {
        left_i++;
    }

    while (buf[right_i] > pivot) {
        right_i++;
    }

    if (left_i < right_i) {
        swap(buf, left_i, right_i);
        quicksort(buf, start, end);
    } else {
        swap(buf, left_i, end - 1); // swap left with pivot
        quicksort(buf, start, left_i);
        quicksort(buf, left_i, end);
    }
}

void swap(int buf[], int i, int j) {
    int at_i = buf[i];
    buf[i] = buf[j];
    buf[j] = at_i;
}
