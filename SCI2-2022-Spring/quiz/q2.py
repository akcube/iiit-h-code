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

sigma = 3.4
epsilon = 0.238

def lennard_jones(p1, p2, sigma, epsilon):
	dist = 0
	for i in range(0, 3):
		dist += (p1[i]*10 - p2[i]*10)**2
	dist = math.sqrt(dist)
	value = 4*epsilon*((sigma/dist)**12 - (sigma/dist)**6)
	return value

ans = 0
for i in range(0, 4):
	for j in range(0, 4):
		if i != j:
			value = lennard_jones(points[i], points[j], sigma, epsilon)
			ans += value
			print("Points {}, {}: {}".format(i, j, value))

print("Sum: {}".format(ans))
