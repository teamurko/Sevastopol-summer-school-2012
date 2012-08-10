import sys
from random import randint, seed, shuffle

def main(args):
    args = [int(x) for x in args]
    seed(args[0])
    num_vertices = randint(args[1], args[2])
    min_value = args[3]
    max_value = args[4]
    vertices = range(num_vertices)
    shuffle(vertices)
    data = [(vertices[0], -1, randint(min_value, max_value))]
    tree_vertices = [vertices[0]]
    vertices = vertices[1:]
    for vertex in vertices:
        data.append((vertex, \
                     tree_vertices[randint(0, len(tree_vertices)-1)], \
                     randint(min_value, max_value)))
        tree_vertices.append(vertex)
    data.sort()
    print num_vertices
    prev = -1
    for vertex, parent, value in data:
        assert(prev + 1 == vertex)
        prev = vertex
        print parent, value

if __name__ == "__main__":
    main(sys.argv[1:])
