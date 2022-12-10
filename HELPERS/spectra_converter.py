import string
import sys

def read_spectrum(in_filename: string) -> tuple:
    energies = []
    photons = []

    with open(in_filename) as f:
        lines = f.readlines()

        for line in lines[18:]:
            substrs = line.split("  ")
            energies.append(float(substrs[0]))
            photons.append(float(substrs[1][:-1]))
        
    return energies, photons

def get_spectrum(energies: list, photons: list) -> string:
    spectrum_list = ""

    energies_string = "".join(["\t\t"+str(e)+",\n" for e in energies])
    energies_string = energies_string[:-2]
    spectrum_list += "\tstatic const double energies[] = {\n" + energies_string + "\n\t};\n\n"

    photons_string = "".join(["\t\t"+str(p)+",\n" for p in photons])
    photons_string = photons_string[:-2]
    spectrum_list += "\tstatic const double photons[] = {\n" + photons_string + "\n\t};\n\n"

    return spectrum_list


if __name__ == "__main__":
    if len(sys.argv) == 1:
        in_filename = "spectra/SPECTRA_60kVp_17deg_1Al.txt"
        out_filename = "../LIBRARY/include/constants.hpp"
    elif len(sys.argv) == 3:
        in_filename  = sys.argv[1]
        out_filename = "../LIBRARY/include/" + sys.argv[2]
    elif len(sys.argv) > 3:
        in_filename  = sys.argv[1]
        out_filename = sys.argv[3] + sys.argv[2]

    energies, photons = read_spectrum(in_filename)
    print(get_spectrum(energies, photons))