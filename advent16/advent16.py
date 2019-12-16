import math as m

with open("input.txt") as input:
    ziffern = [int(i) for i in input.readline().strip()]


#ziffern = [int(i) for i in "80871224585914546619083218645595"]

pattern = [0, 1, 0, -1]

def weighting(step, index):
    return pattern[(index + 1) // (step + 1) % 4]


for i in range(100):
    new_ziffern = []
    for i in range(len(ziffern)):
        new_ziffern.append(sum(ziffern[o] * weighting(i, o) for o in range(len(ziffern))) % 10)
    ziffern = new_ziffern[:]

print(ziffern[:9])
