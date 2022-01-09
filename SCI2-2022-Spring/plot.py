import sys
import math
import numpy as np
import matplotlib.pyplot as plt

n_val = list(map(int, sys.stdin.readline().split()))
p_val = list(map(float, sys.stdin.readline().split()))

plt.plot(n_val, p_val, label = 'Simulated')
plt.plot(n_val, r_val, label = 'Real')
plt.legend()
plt.show()