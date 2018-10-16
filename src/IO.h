//
// Created by gantzm on 10/15/18.
//

#pragma once

#include <nlohmann/json.hpp>

#include <string>
#include <iostream>

namespace gg {
namespace envsel {

nlohmann::json readJsonFile(const std::string &filename);

template <class T>
std::ostream &operator<<(std::ostream &stream, const std::vector<std::unique_ptr<T>> & vec) {

    bool addSep = false;

    for (auto &value : vec) {

        if( addSep ){
            stream << ",";
        }else{
            addSep = true;
        }

        stream << *value;

    }

    return stream;
}



}
}
