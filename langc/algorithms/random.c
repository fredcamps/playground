#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int pseudo_random_range(int min, int max)
{
    int tmp;
    if (min > max) {
        tmp = min;
        min = max;
        max = tmp;
    }
    time_t t;
    srand((unsigned) time(&t));
    return (rand() % (max + 1 - min)) + min;
}


int main(int argc, char *argv[])
{
    printf("%d\n", pseudo_random_range(1, 100));
    printf("%d\n", pseudo_random_range(99, 2));
    printf("%d\n", pseudo_random_range(-99, -10));
    printf("%d\n", pseudo_random_range(-11, -101));
    printf("%d\n", pseudo_random_range(-50, 50));
    printf("%d\n", pseudo_random_range(40, -80));

    printf("%d\n", pseudo_random_range(10, 10));
    printf("%d\n", pseudo_random_range(-1, -1));
    return 0;
}
