#include "Script.h"
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
// Script
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string Script::F_NAME{"name"};
const std::string Script::F_IFSET{"ifSet"};
const std::string Script::F_COMMANDS{"commands"};

Script::Script() :
        AbstractDomain{}, m_name{""}, m_ifSet{""} {

    CLOG(TRACE, TAG) << "Called";
}

Script::~Script() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string &Script::name() const {
    return m_name;
}

const std::string &Script::ifSet() const {
    return m_ifSet;
}

ScriptCommandList &Script::commands() {
    return m_commands;
}

void Script::execute(const VariableDictionary &variables, std::vector<std::string> &output) const {

    if (m_ifSet.length() > 0 && variables.count(m_ifSet) == 0) {
        return;
    }

    for (auto &op : m_commands) {

        op->execute(variables, output);

    }


}

void from_json(const nlohmann::json &json, Script &item) {

    from_json(json, reinterpret_cast<AbstractDomain&>(item) );

    json.at(Script::F_NAME).get_to(item.m_name);
    json.at(Script::F_IFSET).get_to(item.m_ifSet);
    json.at(Script::F_COMMANDS).get_to(item.m_commands);

}

void to_json(nlohmann::json &j, const Script &item) {

    j = {
            {Script::F_NAME,     item.m_name},
            {Script::F_IFSET,    item.m_ifSet},
            {Script::F_COMMANDS, to_json(item.m_commands)}
    };

    to_json(j, reinterpret_cast<const AbstractDomain&>(item) );

}

std::ostream &operator<<(std::ostream &stream, const Script &item) {

    ToString(stream, "Script") //
            .field("m_id", item.id()) //
            .field("m_name", item.m_name) //
            .field("m_ifSet", item.m_ifSet) //
            .field("m_commands", item.m_commands); //

    return stream;
}




}
}
