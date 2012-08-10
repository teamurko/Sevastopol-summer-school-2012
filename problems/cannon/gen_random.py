import sys
from random import seed, randint

def main(*args):
    args_list = args[0]
    seed(args_list[0])
    num_points = randint(10, 100)
    minx = args_list[1]
    maxx = args_list[2]
    miny = args_list[3]
    maxy = args_list[4]
    if len(args) > 5:
        num_points = int(args[5])
    print num_points
    for pid in range(num_points):
        print randint(minx, maxx), randint(miny, maxy)

if __name__ == "__main__":
    args = [int(x) for x in sys.argv[1:]]
    main(args)
