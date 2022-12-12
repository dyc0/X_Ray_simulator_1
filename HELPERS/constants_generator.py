from material_generator import read_attenuation
from spectra_converter import read_spectrum

import getopt
import numpy as np
import os
import string
import sys

def get_map(keys: list, values: list, name:str, type1:str, type2:str, comment:str) -> string:
    dict = ""

    dict += "\t// " + comment + "\n"
    dict += "\tstatic const std::map<" + type1 + ", " + type2 + "> " + name + " = {\n"
    elements = ''
    for e, p in zip(keys, values):
        if type1 not in ("std::string", "string"):
            elements += "\t\t{" + str(e) + ", " + str(p) + "},\n"
        else:
            elements += "\t\t{\"" + str(e) + "\", " + str(p) + "},\n"
    elements = elements[:-2]
    elements += "\n"
    dict += elements
    dict += "\t};\n"

    return dict

def get_list(elements: list, name:str, type:str, comment:str) -> string:
    container = ""

    container += "\t// " + comment + "\n"
    container += "\tstatic const std::vector<" + type + "> " + name + " = {\n"
    elements_str = ''
    for e in elements:
        elements_str += "\t\t" + str(e) + ",\n"
    elements_str = elements_str[:-2]
    elements_str += "\n"
    container += elements_str
    container += "\t};\n"

    return container

if __name__ == '__main__':
    argument_list = sys.argv[1:]
    options = "k:d:f:s:m:t:o:"
    long_options = ["kvp=", "deg=", "filt=", "SpectrumPath=", "MaterialsPath=", "Tolerance=", "OutputFile="]

    tube_kvp = "60"
    tube_deg = "17"
    tube_flt = "1Al"
    spectrum_path = "spectra"
    materials_path = "materials_data/attenuations"
    tolerance = "1e-6"
    output_file = "../LIBRARY/include/constants.hpp"

    mAs = 100
    surface = 0.1*0.2
    
    try:
        arguments, values = getopt.getopt(argument_list, options, long_options)
        for curArg, curVal in arguments:
            if curArg in ("-k", "--kvp"):
                tube_kvp = curVal
            elif curArg in ("-d", "--deg"):
                tube_deg = curVal
            elif curArg in ("-f", "--filter"):
                tube_flt = curVal
            elif curArg in ("-s", "--SpectrumPath"):
                spectrum_path = curVal
            elif curArg in ("-m", "--MaterialsPath"):
                materials_path = curVal
            elif curArg in ("-t", "--Tolerance"):
                tolerance = curVal
            elif curArg in ("-o", "--OutputFile"):
                output_file = curVal

    except getopt.error as err:
        print(str(err))

    spectrum_filename = os.path.join(spectrum_path, "SPECTRA_" + tube_kvp + "kVp_" + \
        tube_deg + "deg_" + tube_flt + ".txt")
    energies, photons = read_spectrum(spectrum_filename)

    materials = {}
    energies_MeV = [e*0.001 for e in energies]
    for filename in os.listdir(materials_path):
        mat_energies, mat_attenuation = read_attenuation(os.path.join(materials_path, filename))
        mat_attenuation_interp = np.interp(energies_MeV, mat_energies, mat_attenuation)
        materials[filename[:-4]] = mat_attenuation_interp

    with open(output_file, 'w') as of:
        of.write("#ifndef CONSTANTS_HPP\n#define CONSTANTS_HPP\n\nnamespace xrc {\n\n")

        tolerance_string = "\tconst static double tolerance = " + tolerance + ";\n\n"
        of.write(tolerance_string)

        source_e = get_list(energies, "energies", "double", "Possible energies of photons")
        of.write(source_e)
        of.write("\n\n")

        #for i in range(len(photons)): photons[i] = photons[i] * energies[i] * mAs * surface
        source_s = get_list(photons, "spectrum", "double", "Photon count per energy value")
        of.write(source_s)
        of.write("\n\n")

        keys_pointers = []
        materials_enum = "enum materials { "
        for key in materials.keys():
            keys_pointers.append("&" + key)
            attenuation = get_list(materials[key], key, "double", key + " material")
            of.write(attenuation)
            of.write("\n")

            materials_enum += key.upper() + ", "
        materials_enum += "VACUUM = -1 };"

        keys = get_map(np.arange(0, len(materials.keys())), keys_pointers, "materials_keys", "int", "const std::vector<double>*", "Map of all materials")
        of.write(keys)

        densities = [1.050, 9.500e-01, 1.050, 1.040, 1.070, 1.040, 1.920, 1.060, 1.050, 1.020]
        densities_str = get_list(densities, "material_densities", "double", "Densities of materials")
        of.write("\n" + densities_str)

        of.write("\n\t" + materials_enum + "\n")
        of.write("\n")


        of.write("} // namespace\n\n#endif")
    
    
    