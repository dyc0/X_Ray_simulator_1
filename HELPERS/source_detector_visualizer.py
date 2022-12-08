from matplotlib import pyplot as plt
from mpl_toolkits import mplot3d
import string
import numpy as np

def read_3d_vectors(filename: string) -> list:
    vectors = []
    with open(filename) as px_f:
        lines = px_f.readlines();
        for line in lines:
            data = line[1:-2]
            numdata = data.split(", ")
            vectors.append([float(numdata[0]), float(numdata[1]), float(numdata[2])])
    return vectors

if __name__ == '__main__':
    pixels = np.array(read_3d_vectors("sd_vis_data/pixels.txt"))
    rays = np.array(read_3d_vectors("sd_vis_data/rays.txt"))

    fig = plt.figure()
    ax = plt.axes(projection ='3d')

    ax.scatter(pixels[:,0], pixels[:,1], pixels[:,2])
    
    t = np.linspace(0, 20, 3)
    for ray in rays:
        x = ray[0]*t
        y = ray[1]*t
        z = ray[2]*t
        ax.plot3D(x, y, z, color='red')

    ax.set_xlim((-1, 2.5))
    plt.show()