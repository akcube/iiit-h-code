import numpy as np
import matplotlib.pyplot as plt
import sys
def read_file(filename):
    depth = []
    with open(filename, "r") as f:
        lines = f.readlines()
        for line in lines:
            depth.append([float(i) for i in line.strip(" \n").split(" ")])
    return np.array(depth)
if __name__ == "__main__":
    m = np.array([10, 50, 100, 1000])
    n = np.array([10, 50, 100, 1000])
    depth = read_file(sys.argv[1])
    X, Y = np.meshgrid(m, n)
    Z = depth.T
    fig = plt.figure()
    ax = plt.axes(projection = '3d')
    # ax.contour3D(X, Y, Z, 50, cmap=’binary’)
    ax.set_xlabel('m')
    ax.set_ylabel('N')
    ax.set_zlabel('Average Depth')
    ax.plot_surface(X, Y, Z, cmap = 'viridis', edgecolor = 'green')
    ax.set_title('3D plot of Average Depth')
    plt.show()