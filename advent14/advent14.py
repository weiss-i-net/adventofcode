dict = {}

with open("input.txt", "r") as input:
    lines = input.readlines()
    for i in lines:
        l = i.strip().split(" ")
        l.remove("=>");
        dict[l[-1]] = ([(l[i+1].strip(","), int(l[i])) for i in range(0, len(l)-2, 2)], int(l[-2]))

dict["ORE"] = ([], 1)

test = { "F" : ([("AB", 2), ("BC", 3), ("CA", 4)], 1),
         "AB" : ([("A", 3), ("B", 4)], 1),
         "BC" : ([("B", 5), ("C", 7)], 1),
         "CA" : ([("C", 4), ("A", 1)], 1),
         "A" : ([("ORE", 9)], 2),
         "B" : ([("ORE", 8)], 3),
         "C" : ([("ORE", 7)], 5),
         "ORE" : ([], 1)
         }


chem = dict
chemcopy = chem.copy()
ordered = []
while len(chemcopy) > 0:
    for key, value in chemcopy.items():
        if all(i[0] in ordered for i in value[0]):
            chemcopy.pop(key)
            ordered.append(key)

itemlist = ["FUEL"]
itemcount = [1]

for item in ordered[::-1]:
    for i in chem[item][0]:
        if i[0] in itemlist:
            itemcount[itemlist.index(i[0])] += -(-itemcount[itemlist.index(item)] // chem[item][-1]) * i[-1]
        else:
            itemlist.append(i[0])
            itemcount.append(-(-itemcount[itemlist.index(item)] // chem[item][-1]) * i[-1])

# a
print(itemcount[-1])

# b binary search by hand: 4906796
