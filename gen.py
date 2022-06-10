import random
import math


def check(x, y, d):
    if x == y:
        return False
    if (x, y) in d:
        return False
    return True


def getNextEdge(n, minW, maxW, d):
    x = random.randint(0, n - 1)
    y = random.randint(0, n - 1)
    while not check(x, y, d):
        x = random.randint(0, n - 1)
        y = random.randint(0, n - 1)
    return x, y, random.randint(minW, maxW)


def main():
    maxZ = 1
    minN = 10000
    maxN = 10000
    minM = 20000
    maxM = 20000
    minW = -8000
    maxW = 32000

    z = random.randint(1, maxZ)
    print(z)

    for _ in range(z):

        n = random.randint(minN, maxN)
        m = random.randint(minM, maxM)
        s = random.randint(0, n-1)
        d = set()

        print("{} {} {}".format(n, m, s))

        for _ in range(m):
            x, y, w = getNextEdge(n, minW, maxW, d)
            d.add((x, y))
            print("{} {} {}".format(x, y, w))


if __name__ == "__main__":
    main()
