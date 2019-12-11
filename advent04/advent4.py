
l = [str(i) for i in range(372304, 847060)]
#l = ["111133", "111333"]


for i in range(len(l)):
    not_rising = False
    no_doubles = True
    for o in range(1, len(l[i])):
        if l[i][o] == l[i][o-1]:
            if o == len(l[i])-1:
                if l[i][o] != l[i][o-2]:
                    no_doubles = False
            elif l[i][o] != l[i][o+1] and l[i][o] != l[i][o-2]:
                no_doubles = False
        if l[i][o-1] > l[i][o]:
            not_rising = True
    if not_rising or no_doubles:
        l[i] = ""

print(len([i for i in l if i != ""]))
