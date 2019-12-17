import math as m

with open("input.txt") as input:
    ziffern = [int(i) for i in input.readline().strip()]


#ziffern = [int(i) for i in "80871224585914546619083218645595"]
def brute_force (ziffern):
    pattern = [0, 1, 0, -1]

    len=len(ziffern)

    for i in range(100):
        new_ziffern = []
        for i in range(len):
            sum = 0
            for o in range(len):
                sum += ziffern[o] * pattern[(o + 1) // (i + 1) % 4]
            ziffern[i] = sum % 10
    return (ziffern[:8])

def second_half (ziffern):
    leng = sum(ziffern[i]*10**(6-i) for i in range(7))
    ziffern = ziffern[:leng-1:-1]
    for z in range(100):
        for i in range(1, len(ziffern) - 1):
            ziffern[i] = (ziffern[i-1] + ziffern[i]) % 10
    return ziffern[:-9:-1]

test = [1,2,3,4,5,6]
print(test[3::-1])
#print(''.join(map(str,second_half(ziffern * 10000))))
