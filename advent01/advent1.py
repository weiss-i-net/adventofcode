with open("advent1_input.txt", "r") as fp:
    advent1_input = fp.readlines()
    advent1_input = [int(x.strip()) for x in advent1_input]

def fuel(mass):
    extra_fuel = mass // 3 - 2
    if extra_fuel <= 0:
        return 0
    return extra_fuel + fuel(extra_fuel)

mass_sum = sum([fuel(i) for i in advent1_input])

print(mass_sum)
