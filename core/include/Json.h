#pragma once

#include <nlohmann/json.hpp>

#include <string>
#include <memory>

namespace gg {
namespace envsel {


template<class T>
void from_json(const nlohmann::json & json, std::vector<std::unique_ptr<T>> & vec) {

    for (auto & eJson : json) {

        auto ptr = std::make_unique<T>();

        eJson.get_to<T>(*ptr);

        vec.push_back(std::move(ptr));
    }

}


template<class T>
nlohmann::json to_json(const std::vector<std::unique_ptr<T>> & vec) {

    nlohmann::json json = nlohmann::json::array();

    for (auto & item : vec) {
        json.push_back(nlohmann::json(*item));
    }

    return json;
}

}
}
