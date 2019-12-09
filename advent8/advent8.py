with open("input.txt", "r") as fp:
    path_a = fp.readline().strip()

data = [int(i) for i in path_a]

rows = 6
cols = 25
num_pixel = rows * cols

layers = []

for o in range(len(data) // num_pixel):
    layers.append([])
    for i in range(num_pixel):
        layers[o].append(data[o * num_pixel + i])

num_Os = []

for layer in layers:
    num_Os.append(layer.count(0))

#a)
print(layers[5].count(1) * layers[5].count(2))

image = []

for i in range(rows):
    image.append([])
    for o in range(cols):
        image[i].append(layers[0][i * cols + o])




not_done = True
layer = 0
while not_done:
    not_done = False #Test
    layer += 1
    for i in range(rows):
        for o in range(cols):
            if image[i][o] == 2:
                image[i][o] = layers[layer][i * cols + o]
                not_done = True


for i in image:
    for o in i:
        print(u"\U0001F44C" if o == 1 else "  ", end="")
    print()
