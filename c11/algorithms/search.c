#include <stdio.h>

int binary_find(int *array, int peek, size_t len)
{
    int min = 0;
    int max = (int)len-1;
    for (int i = min; i <= max; i ++) {
        if (peek > array[max/2]) {
            min = max/2 + 1;
        } else {
            max = max/2;
        }

        if (array[i] == peek) {
            return i;
        }
    }

    return -1;
}

int main(int argc, char const *argv[]) {
    int index = 0;
    int peek = 16;
    int array[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20
    };
    size_t len = sizeof(array) / sizeof(int);
    index = binary_find(array, peek, len);
    if (index == -1) {
        printf("%d not found!", peek);
    }
    printf("%d was found at %d!", peek, index);

    return 0;
}
