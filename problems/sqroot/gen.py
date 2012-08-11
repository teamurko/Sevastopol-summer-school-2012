#!/usr/env python
import sys
import random
import fractions
from itertools import dropwhile

def rand():
    return random.randint(1, 2**15 - 1)

def is_prime(n):
    if n <= 1:
        return False
    for i in range(2, n):
        if i * i > n:
            break
        if n % i == 0:
            return False
    return True

def primes():
    for i in range(2, 2**15):
        if is_prime(i):
            yield i

def rand_pairs():
    cache = primes()
    while True:
        for p in cache:
            yield (rand(), p)
        cache = primes()


def main(args):
    max_tests = args[0]
    max_prime = args[1]
    rev_primes = reversed(list(primes()))
    num_tests = 0
    tests = []
    for p in dropwhile(lambda x: x > max_prime, rev_primes):
        if num_tests == max_tests:
            break
        for a in range(1, p):
            if num_tests == max_tests:
                break
            num_tests += 1
            tests.append((a, p))
    print(num_tests)
    for a, p in tests:
        print a, p

if __name__ == "__main__":
    main([int(x) for x in sys.argv[1:]])

