"""solving the problem using backtracking"""

def getMin(numDigits,sumDigits):
    if sumDigits == 0:
        if numDigits == 1:
            return 0
    if sumDigits > 9*numDigits:
        return -1
    sumDigits-=1
    digits = []
    for i in range(numDigits):
        if sumDigits > 9:
            digits.append(9)
            sumDigits-=9
        else:
            digits.append(sumDigits)
            sumDigits = 0
    digits[numDigits-1] += 1
    digits.reverse()
    return int(''.join(map(str,digits)))

def getMax(numDigits,sumDigits):
    if sumDigits == 0:
        if numDigits == 1:
            return 0
    if sumDigits > 9*numDigits:
        return -1
    digits = []
    for i in range(numDigits):
        if sumDigits > 9:
            digits.append(9)
            sumDigits-=9
        else:
            digits.append(sumDigits)
            sumDigits = 0
    return int(''.join(map(str,digits)))

def main():
    n,m = map(int,input().split())
    if m == 0:
        if n == 1:
            print(0,0)
        else:
            print(-1,-1)
    else:
        minn = getMin(n,m)
        maxx = getMax(n,m)
        print(minn,maxx)

if __name__ == "__main__":
    main()