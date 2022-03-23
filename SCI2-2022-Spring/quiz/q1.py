import matplotlib.pyplot as plt
import random
import math
from mpl_toolkits import mplot3d
import numpy as np

def make_point():
    return [random.random(), random.random(), random.random()]

points = []

while len(points) < 4:
	candidate = make_point()
	valid = True

	for p in points:
		dist = 0
		for i in range(0, 3):
			dist += (candidate[i] - p[i])**2
		dist = math.sqrt(dist)
		if(dist < 0.5 or dist > 0.6):
			valid = False

	if valid:
		points.append(candidate)

X = []
Y = []
Z = []

for p in points:
	X.append(p[0])
	Y.append(p[1])
	Z.append(p[2])

fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")

ax.scatter(X, Y, Z, c="r")
ax.set_xlabel("x-axis")
ax.set_ylabel("y-axis")
ax.set_zlabel("z-axis")

plt.show()