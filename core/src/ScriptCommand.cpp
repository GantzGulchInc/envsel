#include "ScriptCommand.h"
#include "IO.h"
#include "ToString.h"
#include "Json.h"

#include "easylogging++.h"

#include <iostream>
#include <regex>

using nlohmann::json;

namespace gg {
namespace envsel {

static const char *TAG = "Domain";

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Script Command
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string ScriptCommand::F_COMMAND{"command"};
const std::string ScriptCommand::F_ARGUMENTS{"args"};

ScriptCommand::ScriptCommand() :
        AbstractDomain{}, m_command{""} {

    CLOG(TRACE, TAG) << "Called";
}

ScriptCommand::~ScriptCommand() {

    CLOG(TRACE, TAG) << "Called";
}


const std::string &ScriptCommand::command() const {
    return m_command;
}

const std::vector<std::string> &ScriptCommand::arguments() const {
    return m_arguments;
}

static std::string expandVariables(std::string value, const VariableDictionary &variables) {

    const std::regex r{R"(#\{([^}]+)\})"};

    std::smatch match;

    while (std::regex_search(value, match, r)) {

        auto const expr = match[0];
        auto const name = match[1].str();

        std::string r = variables.count(name) ? variables.at(name) : "";

        value.replace(expr.first, expr.second, r);

    }

    return value;

}

void ScriptCommand::execute(const VariableDictionary &variables, std::vector<std::string> &output) const {

    if (m_command == "print") {

        for (auto arg : m_arguments) {

            auto v = expandVariables(arg, variables);

            output.push_back(v);
        }

    } else {

        // Uh oh.
    }

}


void from_json(const nlohmann::json &json, ScriptCommand &item) {

    from_json(json, reinterpret_cast<AbstractDomain&>(item) );

    json.at(ScriptCommand::F_COMMAND).get_to(item.m_command);
    json.at(ScriptCommand::F_ARGUMENTS).get_to(item.m_arguments);

}

void to_json(nlohmann::json &j, const ScriptCommand &item) {

    j = {
            {ScriptCommand::F_COMMAND,   item.m_command},
            {ScriptCommand::F_ARGUMENTS, item.m_arguments}
    };

    to_json(j, reinterpret_cast<const AbstractDomain&>(item) );
}

std::ostream &operator<<(std::ostream &stream, const ScriptCommand &scriptOperation) {

    ToString(stream, "ScriptCommand") //
            .field("m_id", scriptOperation.id()) //
            .field("m_command", scriptOperation.m_command) //
            .field("m_arguments", scriptOperation.m_arguments); //

    return stream;
}



}
}
