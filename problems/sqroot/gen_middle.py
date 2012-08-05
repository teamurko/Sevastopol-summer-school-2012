#!/usr/env python
import random
import fractions

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


num_tests = 30000
print(num_tests)
pairs = rand_pairs()
for i in range(num_tests):
    for a, n in pairs:
        if a % n != 0:
            print a, n
            break

