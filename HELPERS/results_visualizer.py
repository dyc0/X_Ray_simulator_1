import numpy as np
from matplotlib import pyplot as plt

if __name__ == '__main__':
    result = np.loadtxt("results.txt")

    plt.imshow(result, cmap='gray')
    plt.show()