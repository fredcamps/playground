#include <stdio.h>
#include <math.h>

/**
 *  Put all prime factors at result of a given number n
 */
void prime_factors(int *results, int n)
{
    int d = 2;
    int c = 0;
    while ((d*d) <= n) {
        while (n % d == 0) {
            results[c] = d;
            n = (int) floor((double) (n)/ (double) d);
            c++;
        }
        d++;
    }

    if (n>2) {
        results[c] = n;
        c++;
    }
}


int main(int argc, char *argv[])
{
    int results[10000];
    int choice = 3115;
    prime_factors(results, choice);
    int length = 10;
    printf("\n prime factor of %d: ", choice);
    for (int i = 0; i < length; ++i) {
        if (results[i] != 0) {
            printf("%d ", results[i]);
        }
    }


    return 0;
}
