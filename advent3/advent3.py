def pts_from_path(path):
    last_point = (0, 0)
    points = []
    for i in path:
        if i[0] == "U":
            for i in range(1, int(i[1:]) + 1):
                points.append((last_point[0] + i, last_point[1]))
            last_point = points[-1]
        elif i[0] == "R":
            for i in range(1, int(i[1:]) + 1):
                points.append((last_point[0], last_point[1] + i))
            last_point = points[-1]
        elif i[0] == "D":
            for i in range(1, int(i[1:]) + 1):
                points.append((last_point[0] - i, last_point[1]))
            last_point = points[-1]
        elif i[0] == "L":
            for i in range(1, int(i[1:]) + 1):
                points.append((last_point[0], last_point[1] - i))
            last_point = points[-1]
    return points

with open("advent3/input.txt", "r") as fp:
    path_a = fp.readline().split(",")
    path_b = fp.readline().split(",")

points_a = pts_from_path(path_a)
points_b = pts_from_path(path_b)

common_points = list(set(points_a) & set(points_b))

print("Distance to nearest common point")
print("by taxicab metric: %s" % min([abs(i[0]) + abs(i[1]) for i in common_points]))
print("by length of path: %s" % min([points_a.index(i) + points_b.index(i) + 2 for i in common_points]))
