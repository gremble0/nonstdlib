#include "quicksort.h"

void quicksort(int buf[], int start, int end) {
    // basecase
    // if (end == 0) {
    //     return;
    // }

    // int pivot = (buf[0] + buf[end - 1]) / 2;
    // int pivot = buf[end / 2];
    int pivot = buf[end - 1];

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
    }
}

void swap(int buf[], int i, int j) {
    int at_i = buf[i];
    buf[i] = buf[j];
    buf[j] = at_i;
}
