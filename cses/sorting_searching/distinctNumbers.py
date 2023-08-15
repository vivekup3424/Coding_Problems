def main():
    n = int(input())
    s = set()
    for i in range(n):
        temp = int(input())
        s.add(temp)
    print(len(s))

if __name__=="__main__":
    main()