from anytree import Node, RenderTree, AsciiStyle, Walker, exporter
import sys
sys.setrecursionlimit(1000)

orbits = []

with open("advent6/input.txt", "r") as input:
    lines = input.readlines()
    for i in lines:
        orbits.append(i.strip())

tree = [Node("COM")]

def addChilds(dad):
    for i in orbits:
        if i[:3] == dad.name:
            curr = Node(i[4:], parent=dad)
            tree.append(curr)
            addChilds(curr)

addChilds(tree[0])

sum = 0
for i in tree:
    sum += i.depth
print(sum)

for i in range(len(tree)):
    if tree[i].name in ["YOU", "SAN"]:
        print(i, tree[i])

wa = Walker().walk(tree[306].parent, tree[801].parent)
print(len(wa[0]) + len(wa[2]))

exporter.DotExporter(tree[0]).to_picture("tree.png")
