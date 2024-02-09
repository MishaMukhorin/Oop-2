#include "Dictionary.h"

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <dictionary_file>" << std::endl;
        return 1;
    }
    return !ManageDictionary(argv[1]);
}