
#include "DomainTest.h"

#include "Domain.h"

#include <nlohmann/json.hpp>

#include <string>

namespace gg {
namespace envsel {
namespace test {

/**
 * ScriptVariable
 */
TEST_F(DomainTest, ParseScriptVariableJson) {

    std::string jsonString(R"( { "name": "name1", "value": "value1" } )");

    nlohmann::json json = nlohmann::json::parse(jsonString);

    ScriptVariable sv;

    json.get_to(sv);

    EXPECT_EQ(sv.name(), "name1");
    EXPECT_EQ(sv.value(), "value1");

}

/**
 * ScriptVariable
 */
TEST_F(DomainTest, ParseScriptVariableJsonEmptyValues) {

    std::string jsonString(R"( { "name": "", "value": "" } )");

    nlohmann::json json = nlohmann::json::parse(jsonString);

    ScriptVariable sv;

    json.get_to(sv);

    EXPECT_EQ(sv.name(), "");
    EXPECT_EQ(sv.value(), "");

}

/**
 * Application
 */
TEST_F(DomainTest, ParseApplicationJson) {

    std::string jsonString(R"(
{
  "id": "jdk",
  "name": "Java Development Kit",
  "installations": [
    {
      "id": "jdk-11",
      "name": "JDK 11",
      "variables": [
        {
          "name": "variable 11a",
          "value": "value 11a"
        },
        {
          "name": "variable 11b",
          "value": "value 11b"
        }
      ]
    },
    {
      "id": "jdk-10",
      "name": "JDK 10",
      "variables": [
        {
          "name": "variable 10a",
          "value": "value 10a"
        },
        {
          "name": "variable 10b",
          "value": "value 10b"
        }
      ]
    }
  ]
}
)");

    nlohmann::json json = nlohmann::json::parse(jsonString);

    Application item;

    json.get_to(item);

    EXPECT_EQ(item.id(), "jdk");
    EXPECT_EQ(item.name(), "Java Development Kit");

    EXPECT_EQ(item.installations()[0]->id(), "jdk-11");

    EXPECT_EQ(item.installations()[1]->id(), "jdk-10");
}

/**
 * ApplicationInstallation
 */
TEST_F(DomainTest, ParseApplicationInstallationJson) {

    std::string jsonString(R"(
{
  "id": "jdk-11",
  "name": "JDK 11",
  "variables": [
    {
      "name": "variable 11a",
      "value": "value 11a"
    },
    {
      "name": "variable 11b",
      "value": "value 11b"
    }
  ]
}
)");

    nlohmann::json json = nlohmann::json::parse(jsonString);

    ApplicationInstallation item;

    json.get_to(item);

    EXPECT_EQ(item.id(), "jdk-11");
    EXPECT_EQ(item.name(), "JDK 11");

    EXPECT_EQ(item.variables()[0]->name(), "variable 11a");

    EXPECT_EQ(item.variables()[1]->value(), "value 11b");
}




}
}
}