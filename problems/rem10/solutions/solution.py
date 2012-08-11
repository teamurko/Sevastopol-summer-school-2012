import sys

def pow_mod(a, n, m):
    res = 1 % m
    while n > 0:
        if (n & 1) == 1:
            res = res * a % m
        a = a * a % m
        n >>= 1
    return res

def pow(a, n):
    res = 1
    while n > 0:
        if (n & 1) == 1:
            res *= a
        a *= a
        n >>= 1
    return res

def calc(zwei, funf, n):
    if n == 1:
        return 19 % (pow(2, zwei) * pow(5, funf))
    if funf == 0:
        if zwei == 0:
            return 0
        m = calc(zwei - 1, 0, n - 1)
    else:
        m = calc(zwei + 1, funf - 1, n - 1)
    return pow_mod(19, m, pow(2, zwei) * pow(5, funf))

def main():
    k, n = [int(x) for x in sys.stdin.readline().strip().split()]
    print calc(k, k, n)

if __name__ == "__main__":
    main()
