from spectra_converter import read_spectrum

import numpy as np
from matplotlib import pyplot as plt
import re
import string

def read_attenuation(in_file: string) -> tuple:
    energies = []
    attenuations = []
    with open(in_file) as in_f:
        lines = in_f.readlines();
        for line in lines:
            values = re.split(' +', line[7:-1])
            values = values[0:3]
            energies.append(float(values[0]))
            attenuations.append(float(values[1]))
    return energies, attenuations


if __name__ == '__main__':
    energies_spectrum, _ = read_spectrum("spectra/SPECTRA_60kVp_17deg_1Al.txt")
    energies, attenuations = read_attenuation("materials_data/adipose.txt")

    energies_spectrum = [e*0.001 for e in energies_spectrum]

    attenuations_interp = np.interp(energies_spectrum, energies, attenuations)

    plt.figure()
    plt.yscale('log')
    plt.xscale('log')
    plt.plot(energies, attenuations, color='r')
    plt.plot(energies_spectrum, attenuations_interp, color='g', linestyle='dashed')
    plt.show()

