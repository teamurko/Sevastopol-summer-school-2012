import sys
import string
from random import randint, seed, shuffle, sample, choice

def main(args):
    seed(args[0])
    n = args[1]
    k = args[2]
    print n, k
    print reduce(lambda x, y : str(x) + " " + str(y), \
                 [randint(0, 1000000008) for _ in range(k)])

if __name__ == "__main__":
    main([int(x) for x in sys.argv[1:]])
