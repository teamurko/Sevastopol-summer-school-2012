import sys
import string
import operator
import fractions
from functools import reduce
from itertools import takewhile
from random import randint, seed, shuffle, sample, choice

def is_prime(x):
    for w in range(2, x):
        if w * w > x:
            break
        if x % w == 0:
            return False
    return True

def primes_from(start):
    n = start
    while (True):
        if is_prime(n):
            yield n
        n += 1

def candidates_up_to(n):
    for x in takewhile(lambda t : t < n, primes_from(3)):
        for y in takewhile(lambda t : t < x and t * x <= n, primes_from(3)):
            yield [x, y]

def main(args):
    N = 32000
    args = [int(x) for x in args]
    seed(args[0])
    num_tests = args[1]
    candidates = list(candidates_up_to(N))
    print num_tests
    for test in range(num_tests):
        cand2 = sample(candidates, 1)[0]
        n = reduce(operator.mul, cand2)
        phi = reduce(operator.mul, map(lambda x : x - 1, cand2))
        c = randint(0, N)
        e = randint(0, N)
        while fractions.gcd(e, phi) != 1:
            e = randint(0, N)
        print e % phi, n, c

if __name__ == "__main__":
    main(sys.argv[1:])
