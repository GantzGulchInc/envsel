
#include "ScriptVariableTest.h"

#include "../src/Domain.h"

#include <nlohmann/json.hpp>

#include <string>

namespace gg {
namespace envsel {

ScriptVariableTest::ScriptVariableTest() {

}

ScriptVariableTest::~ScriptVariableTest() {

}


TEST_F(ScriptVariableTest, ParseSimpleJson) {

    std::string jsonString(R"( { "name": "name1", "value": "value1" } )");

    nlohmann::json json = nlohmann::json::parse(jsonString);

    ScriptVariable sv;

    json.get_to(sv);

    EXPECT_EQ(sv.name(), "name1");
    EXPECT_EQ(sv.value(), "value1");

}

TEST_F(ScriptVariableTest, ParseEmptyFieldsJson) {

    std::string jsonString(R"( { "name": "", "value": "" } )");

    nlohmann::json json = nlohmann::json::parse(jsonString);

    ScriptVariable sv;

    json.get_to(sv);

    EXPECT_EQ(sv.name(), "");
    EXPECT_EQ(sv.value(), "");

}

}
}