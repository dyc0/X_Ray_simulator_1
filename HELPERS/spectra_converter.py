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

def save_spectrum(out_filename:string, energies: list, photons: list) -> None:
    with open(out_filename, 'w') as f:
        f.write("#ifndef CONSTANTS_HPP\n")
        f.write("#define CONSTANTS_HPP\n\n")
        f.write("namespace xrc {\n\n")

        energies_string = "".join(["\t\t"+str(e)+",\n" for e in energies])
        energies_string = energies_string[:-2]
        f.write("\tstatic const double energies[] = {\n" + energies_string + "\n\t};\n\n")

        photons_string = "".join(["\t\t"+str(p)+",\n" for p in photons])
        photons_string = photons_string[:-2]
        f.write("\tstatic const double photons[] = {\n" + photons_string + "\n\t};\n\n")

        f.write("} // namespace\n\n")
        f.write("#endif\n")

def save_spectrum_map(out_filename:string, energies: list, photons: list) -> None:
    with open(out_filename, 'w') as f:
        f.write("#ifndef CONSTANTS_HPP\n")
        f.write("#define CONSTANTS_HPP\n\n")
        f.write("namespace xrc {\n\n")

        f.write("\tconst static double tolerance = 1e-6;\n\n")

        f.write("\t// Key is energy, element is No. of photons\n")
        f.write("\tstatic const std::map<std::string, double> spectrum = {\n")
        spectras = ''
        for e, p in zip(energies, photons):
            spectras += "\t\t{\"" + str(e) + "\", " + str(p) + "},\n"
        spectras = spectras[:-2]
        spectras += "\n"
        f.write(spectras)
        f.write("\t};\n")

        f.write("\n} // namespace\n\n")
        f.write("#endif\n")

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
    save_spectrum_map(out_filename, energies, photons)