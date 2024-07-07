def numWaterBottles( numBottles: int, numExchange: int) -> int:
    count = 0
    leftOver = 0
    while numBottles > 0:
        count +=numBottles
        leftOver += numBottles % numExchange
        numBottles = numBottles//numExchange
        count += leftOver//numExchange
        leftOver = leftOver%numExchange
    count += leftOver//numExchange
    return count        

numBottles = 17
numExchange =3
numWaterBottles(numBottles,numExchange)