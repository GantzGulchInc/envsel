#include "ScriptVariable.h"

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
// Script Variable
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string ScriptVariable::F_NAME{"name"};
const std::string ScriptVariable::F_VALUE{"value"};


ScriptVariable::ScriptVariable() :
        m_name{""}, m_value{""} {

    CLOG(TRACE, TAG) << "Called";
}

ScriptVariable::~ScriptVariable() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string &ScriptVariable::name() {
    return m_name;
}

const std::string &ScriptVariable::value() {
    return m_value;
}


void from_json(const nlohmann::json &json, ScriptVariable &item) {

    from_json(json, reinterpret_cast<AbstractDomain&>(item) );

    json.at(ScriptVariable::F_NAME).get_to(item.m_name);
    json.at(ScriptVariable::F_VALUE).get_to(item.m_value);

}


void to_json(nlohmann::json &j, const ScriptVariable &item) {

    j = {
            {ScriptVariable::F_NAME,  item.m_name},
            {ScriptVariable::F_VALUE, item.m_value}
    };

    to_json(j, reinterpret_cast<const AbstractDomain&>(item) );
}

std::ostream &operator<<(std::ostream &stream, const ScriptVariable &item) {


    ToString(stream, "ScriptVariable") //
            .field("m_id", item.id()) //
            .field("m_name", item.m_name) //
            .field("m_value", item.m_value); //

    return stream;
}



}
}
