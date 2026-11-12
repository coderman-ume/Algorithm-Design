#include "../include/quick_sort.h"

void quick_sort(double array[20], int first, int last) {
    int middle = (first + last) / 2;
    double pivot = array[middle];
    int left = first;
    int right = last;

    do {
        while (array[left] < pivot) left++;
        while (array[right] > pivot) right--;

        if (left <= right) {
            double temp = array[left];
            array[left] = array[right];
            array[right] = temp;
            left++;
            right--;
        }
    } while (left <= right);

    if (first < right)
        quick_sort(array, first, right);
    if (left < last)
        quick_sort(array, left, last);
}
