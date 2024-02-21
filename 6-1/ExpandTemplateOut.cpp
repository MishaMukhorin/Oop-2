//
// Created by Misha on 19.02.2024.
//

#include "ExpandTemplate.h"
#include "iostream"
#include "fstream"


int main(int argc, char* argv[]) {
    if (argc < 4 || argc % 2 != 1) {
        std::cerr << "Usage: " << argv[0] << " <input-file> <output-file> [<param> <value> [<param> <value> ...]]\n";
        return 1;
    }
    std::string const input_file = argv[1];
    std::string const output_file = argv[2];
    std::map<std::string, std::string> params;
    for (int i = 3; i < argc; i += 2) {
        params[argv[i]] = argv[i + 1];
    }
    std::ifstream inputFile(input_file);
    if (!inputFile) {
        std::cerr << "Error: failed to open input file " << input_file << "\n";
        return 1;
    }
    std::ofstream outputFile(output_file);
    if (!outputFile) {
        std::cerr << "Error: failed to open output file " << output_file << "\n";
        return 1;
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        outputFile << ExpandTemplate(line, params) << "\n";
    }
    return 0;
}


