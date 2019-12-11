with open("advent2/input.txt", "r") as fp:
    intcode_in = [int(i) for i in fp.readline().split(",")]


for verb in range(100):
    for noun in range(100):

        intcode = intcode_in[:]
        intcode[1] = noun
        intcode[2] = verb

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

        if intcode[0] == 19690720:
            print(100 * noun + verb)
            break
