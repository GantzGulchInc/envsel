
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

    ScriptVariable item;

    json.get_to(item);

    EXPECT_EQ(item.name(), "name1");
    EXPECT_EQ(item.value(), "value1");

}

/**
 * ScriptVariable
 */
TEST_F(DomainTest, ParseScriptVariableJsonEmptyValues) {

    std::string jsonString(R"( { "name": "", "value": "" } )");

    nlohmann::json json = nlohmann::json::parse(jsonString);

    ScriptVariable item;

    json.get_to(item);

    EXPECT_EQ(item.name(), "");
    EXPECT_EQ(item.value(), "");

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

/**
 * Project
 */
TEST_F(DomainTest, ParseProjectJson) {

    std::string jsonString(R"(
{
  "id": "proj-1",
  "name": "Project 1",
  "applications": [
    {
      "applicationId": "jdk",
      "defaultInstallationId": "jdk-11"
    },
    {
      "applicationId": "eclipse",
      "defaultInstallationId": "eclipse-neon"
    }
  ]
}
)");

    nlohmann::json json = nlohmann::json::parse(jsonString);

    Project item;

    json.get_to(item);

    EXPECT_EQ(item.id(), "proj-1");
    EXPECT_EQ(item.name(), "Project 1");

    EXPECT_EQ(item.apps()[0]->applicationId(), "jdk");

    EXPECT_EQ(item.apps()[1]->defaultInstallationId(), "eclipse-neon");
}


/**
 * ProjectApp
 */
TEST_F(DomainTest, ParseProjectAppJson) {

    std::string jsonString(R"(
{
  "applicationId": "jdk",
  "defaultInstallationId": "jdk-11"
}
)");

    nlohmann::json json = nlohmann::json::parse(jsonString);

    ProjectApp item;

    json.get_to(item);

    EXPECT_EQ(item.applicationId(), "jdk");
    EXPECT_EQ(item.defaultInstallationId(), "jdk-11");
}


/**
 * Script
 */
TEST_F(DomainTest, ParseScriptJson) {

    std::string jsonString(R"(
{
  "id": "script-jdk",
  "name": "Script JDK",
  "ifSet": "JAVA_HOME",
  "commands": [
    {
      "command": "print",
      "args": [ "arg1.1", "arg1.2", "arg1.3" ]
    },
    {
      "command": "print",
      "args": [ "arg2.1", "arg2.2", "arg2.3" ]
    }
  ]
}
)");

    nlohmann::json json = nlohmann::json::parse(jsonString);

    Script item;

    json.get_to(item);

    EXPECT_EQ(item.id(), "script-jdk");
    EXPECT_EQ(item.name(), "Script JDK");
    EXPECT_EQ(item.ifSet(), "JAVA_HOME");

    EXPECT_EQ(item.commands()[0]->command(), "print");

    EXPECT_EQ(item.commands()[1]->arguments()[1], "arg2.2");
}



}
}
}