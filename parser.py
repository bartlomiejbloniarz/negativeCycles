
def main():
    print(1)
    with open('test_raw.in') as file:
        for line in file:
            t = line.split()
            if t[0] == 'p':
                print(t[2], t[3])
            elif t[0] == 'n':
                print(int(t[1])-1)
            elif t[0] == 'a':
                print(int(t[1])-1, int(t[2])-1, t[3])


if __name__ == "__main__":
    main()