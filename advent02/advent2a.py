import os
os.chdir("/home/jannik/Documents/coding_advent/advent2/")
with open("input.txt", "r") as fp:
    intcode = [int(i) for i in fp.readline().split(",")]

print(len(intcode))
print(intcode)
intcode[1] = 12
intcode[2] = 2

pos = 0

while True:
    curr_value = intcode[pos]
    if curr_value == 99:
        break
    if curr_value == 1:
        intcode[intcode[pos+3]] = intcode[intcode[pos+1]] + intcode[intcode[pos+2]]
    if curr_value == 2:
        intcode[intcode[pos+3]] = intcode[intcode[pos+1]] * intcode[intcode[pos+2]]
    pos += 4

print(intcode[0])
