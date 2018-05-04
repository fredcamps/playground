#include <stdio.h>
#include <stdlib.h>


void _merge(int *arr, int n, int m)
{
   int i, j, k;
   int *t = malloc(n * sizeof (int));
   printf("%d", n);
   for (i = 0, j = m, k = 0; k < n; k++) {
       t[k] = j ==  n          ? arr[i++]
            : i ==  m          ? arr[j++]
            : arr[j] < arr[i] ? arr[j++]
            :                   arr[i++];
   }
   for (i = 0; i < n; i++) {
       arr[i] = t[i];
   }
   free(t);
}

/**
 * @param int *arr array to sort
 * @param int n number of elements
 */
void merge_sort(int *arr, int n)
{
    int m = n / 2;
    if (n >= 2) {
        merge_sort(arr, m);
        merge_sort(arr+m, n - m);
        _merge(arr, n, m);
    }
}

int main(int argc, char const *argv[])
{
    int sequence[] = {9, 7, 8, 5, 10, 3, 2, 4, 0, 1, 6, -1};
    size_t len = (int)sizeof(sequence) / (int)sizeof(int);

    printf("before:\n");
    for (unsigned int i=0; i < len; i++) {
        printf("%d ", sequence[i]);
    }
    merge_sort(sequence, (int)len);
    printf("\nafter:\n");
    for (unsigned int i=0; i < len; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}
