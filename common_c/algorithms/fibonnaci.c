#include <stdio.h>

int fibo(int n) {
    if ((n == 0) || (n == 1))
        return n;
    return fibo(n - 1) + fibo(n - 2);
}

int main(int argc, char *argv[])
{
    printf("\n> %d, %d, %d", fibo(1), fibo(4), fibo(15));
    return 0;
}
