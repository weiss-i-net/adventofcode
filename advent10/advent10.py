import cmath
import numpy as np
from collections import defaultdict

ast = defaultdict(dict)

x = 0
for line in open("input.txt", "r").readlines():
    y = 0
    for char in line:
        if char == '#':
            ast[x][y] = []
        y += 1
    x += 1

max_ast = 0
max_ast_i = (0, 0)

for x in ast.keys():
    for y in ast[x].keys():
        for _x in ast.keys():
            for _y in ast[_x].keys():
                if _x != x or _y != y:
                    ast[x][y].append(np.angle(complex(_x-x, _y-y)))
        uni = np.unique(ast[x][y], axis=0)
        if len(uni) > max_ast:
            max_ast = len(uni)
            max_ast_i = (x, y)

print(max_ast_i, max_ast)

lookup = {}
for x in ast.keys():
    for y in ast[x].keys():
        if x != 22 or y != 17:
            ang = np.angle(complex(17-y, 22-x)) - np.pi/2
            ang = ang + 2*np.pi if ang < 0 else ang
            lookup.update({(x, y) : ang})


angl = list(lookup.values())
angl.sort()

i = 0
for shots in range(199):
    if angl.pop(i) == angl[i]:
        i += angl.count(angl[i])

print([key for key, value in lookup.items() if value == angl[i]])
