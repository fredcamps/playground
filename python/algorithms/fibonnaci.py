# Returns the tuple (F(n), F(n+1)).
def fib(n):
    if n == 0:
        return (0, 1)
    else:
        a, b = fib(n // 2)
        c = a * (b * 2 - a)
        d = a * a + b * b
        if n % 2 == 0:
            return (c, d)
        else:
            return (d, c + d)


def fibonacci(n):
    if n < 0:
        raise ValueError("Negative arguments not implemented")
    return fib(n)[0]


for n in range(0, 10):
    print(fibonacci(n))
