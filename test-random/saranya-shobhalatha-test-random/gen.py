import random


def check(x, y, d):
    if x == y:
        return False
    if (x, y) in d:
        return False
    return True


def getNextEdge(n, maxW, d):
    x = random.randint(0, n - 1)
    y = random.randint(0, n - 1)
    while not check(x, y, d):
        x = random.randint(0, n - 1)
        y = random.randint(0, n - 1)
    return x, y, random.randint(-maxW, maxW)


def main():
    maxZ = 10
    maxN = 1000
    maxW = 1000

    z = random.randint(1, maxZ)
    print(z)

    for _ in range(z):

        n = random.randint(2, maxN)
        m = random.randint(0, 30*n)
        s = random.randint(0, n-1)
        d = set()

        print("{} {} {}".format(n, m, s))

        for _ in range(m):
            x, y, w = getNextEdge(n, maxW, d)
            d.add((x, y))
            print("{} {} {}".format(x, y, w))


if __name__ == "__main__":
    main()
