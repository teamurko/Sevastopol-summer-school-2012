#python3
#!/usr/bin/env python
import sys

def main(argv):
    num_tests = int(argv[0])
    last_value = int(argv[1])
    print(num_tests)
    for value in range(last_value - num_tests + 1, last_value + 1):
        print(value)

if __name__ == "__main__":
    main(sys.argv[1:])
