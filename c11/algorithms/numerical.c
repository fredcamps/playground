#include <stdio.h>

/**
 * Euclidean algorithm
 * Calculates greatest common divisor
 *
 */
int gcd(int a, int b)
{
    int c = 0;
    while (b != 0) {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}

/**
 *
 * Calculates lowest common multiple
 */
int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}

/**
 *
 * Check if number is prime
 */
int is_prime(int n)
{
    int flag = 1;

    if (n >= 0 && n <= 2) {
        return 1;
    }

    for (int i = 2; i <= n/2; i++)
    {
        if(n%i==0)
        {
            flag=0;
            break;
        }
    }

    return flag;
}


int main()
{
    int a, b, c, d;
    printf("Enter value of a:");
    scanf("%d", &a);
    printf("Enter value of b:");
    scanf("%d", &b);
    c = lcm(a, b);
    d = gcd(a, b);
    printf("Lowest Common Multiple: %d", c);
    printf("\nGreater Common Divisor: %d\n", d);
    printf("a number is prime? %d\n", is_prime(a));
    printf("b number is prime? %d\n", is_prime(b));
}
