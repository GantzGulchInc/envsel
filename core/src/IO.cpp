
#include "IO.h"

#include <easylogging++.h>

#include <fstream>
#include <iostream>

namespace gg {
namespace envsel {

const char *TAG = "IO";

nlohmann::json readJsonFile(const std::string &filename) {

    std::ifstream jsonFile;

    jsonFile.open(filename, std::ifstream::in | std::ifstream::binary);

    if (jsonFile.fail()) {
        throw std::ios_base::failure("Error opening file: " + filename);
    }

    CLOG(DEBUG, TAG) << "Parsing file: " << filename;

    nlohmann::json json = nlohmann::json::parse(jsonFile);

    CLOG(DEBUG, TAG) << "Closing file: " << filename;

    jsonFile.close();

    return json;
}


void writeOutput(const std::string &filename, const std::vector<std::string> &lines) {

    CLOG(DEBUG, TAG) << "Writing to: " << filename;

    std::ofstream output;

    output.open(filename, std::ifstream::out);

    if (output.fail()) {
        throw std::ios_base::failure("Error opening file: " + filename);
    }

    for (auto line : lines) {
        CLOG(DEBUG, TAG) << "  w: " << line;
        output << line << std::endl;
    }

    output.flush();

    output.close();

}

std::ostream &operator<<(std::ostream &stream, const std::vector<std::string> &vec) {

    bool addSep = false;

    for (auto &value : vec) {

        if (addSep) {
            stream << ",";
        } else {
            addSep = true;
        }

        stream << value;

    }

    return stream;
}




}
}