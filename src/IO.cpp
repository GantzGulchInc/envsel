
#include "IO.h"

#include <fstream>
#include <iostream>

namespace gg {
namespace envsel {

nlohmann::json readJsonFile(const std::string &filename) {

    std::ifstream jsonFile;

    jsonFile.open(filename, std::ifstream::in | std::ifstream::binary);

    if (jsonFile.fail()) {
        throw std::ios_base::failure("Error opening file: " + filename);
    }

    nlohmann::json json;

    jsonFile >> json;

    jsonFile.close();

    return json;
}

std::ostream &operator<<(std::ostream &stream, const std::vector<std::string> & vec) {

    bool addSep = false;

    for (auto &value : vec) {

        if( addSep ){
            stream << ",";
        }else{
            addSep = true;
        }

        stream << value;

    }

    return stream;
}



}
}