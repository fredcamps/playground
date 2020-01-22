#include <stdio.h>


int *bubble_sort(int array[], size_t len)
{
    int swap = 0;
    for (int y = 0; y < len; y++) {
        for (int x = 0; x < len - y; x++) {
            if (array[x] > array[x+1]) {
                swap = array[x];
                array[x] = array[x+1];
                array[x+1] = swap;
            }
        }
    }

    return array;
}

int *insertion_sort(int array[], size_t len)
{
    int position = 0;
    int swap = 0;
    for (int i = 1; i <= len - 1; i++) {
        position = i;
        while (position > 0 && array[position] < array[position-1]) {
            swap = array[position];
            array[position] = array[position-1];
            array[position-1] = swap;
            position--;
        }
    }

    return array;
}

int *selection_sort(int array[], size_t len)
{
    int min = 0;
    int swap = 0;
    for (int i = 0; i < len; i++) {
        min = i;
        for (int j = (i + 1); j < len; j++) {
            if(array[j] < array[min]) {
                min = j;
            }
        }
        if (i != min) {
            swap = array[i];
            array[i] = array[min];
            array[min] = swap;
        }
    }

    return array;
}

/**
 * Sort algorithms
 *
 * Simple sort: insertion, selection
 * Bubble sort: bubble, shell, comb
 * Efficient sort: merge, heap, quick
 * Distribution sort: counting, bucket, radix
 *
 * Stables: insertion, bubble, merge, counting, bucket, radix
 */
int main(int arg, char *argv[])
{
    int sequence[] = {0,1,2,3,4,7,6,8,5,9};
    size_t size = sizeof(sequence) / sizeof(int);
    int *bubble_sorted,
        *insertion_sorted,
        *selection_sorted;

    bubble_sorted = bubble_sort(sequence, size);
    insertion_sorted = insertion_sort(sequence, size);
    selection_sorted = selection_sort(sequence, size);

    for (int i=0; i < size; i++) {
        printf(
            "bubble: %d, insertion: %d, selection: %d\n",
            bubble_sorted[i],
            insertion_sorted[i],
            selection_sorted[i]
        );
    }

    return 0;
}
