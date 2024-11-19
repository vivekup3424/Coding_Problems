import random as rd
head = 0
zero,one,two = 0,0,0
def coin_and_toss(num):
    global head
    global one,two,zero
    for _ in range(num):
        t = rd.randrange(0,2)
        if t == 1:
            head+=1
            one+=1
        elif t==0:
            zero+=1
        else:
            two+=1
sampleSize = (int)(1e5)
coin_and_toss(sampleSize)

print(f"P(head) = {head/sampleSize}")
print(f"one = {one}")
print(f"two = {two}")
print(f"zero = {zero}")
