import sys
import string
from random import randint, seed, shuffle, sample, choice

def random_name():
    return "".join([choice(string.letters) for _ in range(randint(1, 10))])

def main(args):
    args = [int(x) for x in args]
    seed(args[0])
    num_vertices = randint(args[1], args[2])
    sort_time = randint(args[3], args[4])
    max_size = args[5]
    max_time = args[6]
    max_descendants = args[7]
    vertices = range(num_vertices)
    shuffle(vertices)
    data = [(vertices[0], -1, random_name(), \
             randint(0, max_size), randint(0, max_time))]
    descendants = { }
    tree_vertices = [vertices[0]]
    for vertex in vertices[1:]:
        parent = tree_vertices[randint(0, len(tree_vertices)-1)]
        descendants.setdefault(parent, set())
        while len(descendants.get(parent)) >= max_descendants:
            tree_vertices.remove(parent)
            parent = tree_vertices[randint(0, len(tree_vertices)-1)]
            descendants.setdefault(parent, set())
        name = random_name()
        while name in descendants.get(parent):
            name = random_name()
        descendants.get(parent).add(name)
        data.append((vertex, \
                     parent, \
                     name, \
                     randint(0, max_size), \
                     randint(0, max_time)))
        tree_vertices.append(vertex)
    data.sort()
    print num_vertices, sort_time
    prev = -1
    for vertex, parent, name, size, time in data:
        assert(prev + 1 == vertex)
        prev = vertex
        print parent, name, size, time
    source, target = sample(range(num_vertices), 2)
    print source, target

if __name__ == "__main__":
    main(sys.argv[1:])
