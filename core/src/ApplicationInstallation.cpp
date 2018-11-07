#include "Domain.h"
#include "ToString.h"
#include "JsonHelper.h"

#include "easylogging++.h"

using nlohmann::json;

namespace gg {
namespace envsel {

static const char * TAG = "Domain";


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Application Installation
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string ApplicationInstallation::F_NAME{"name"};
const std::string ApplicationInstallation::F_VARIABLES{"variables"};

ApplicationInstallation::ApplicationInstallation() :
        AbstractDomain{}, m_name{""} {

    CLOG(TRACE, TAG) << "Called";
}

ApplicationInstallation::~ApplicationInstallation() {

    CLOG(TRACE, TAG) << "Called";
}


const std::string & ApplicationInstallation::name() const {
    return m_name;
}

ScriptVariableList & ApplicationInstallation::variables() {
    return m_variables;
}

void ApplicationInstallation::addVariables(VariableDictionary & dictionary) const {

    for (auto & variable : m_variables) {

        dictionary[variable->name()] = variable->value();

    }

}

void from_json(const nlohmann::json & json, ApplicationInstallation & item) {

    from_json(json, reinterpret_cast<AbstractDomain&>(item) );

    json.at(ApplicationInstallation::F_NAME).get_to(item.m_name);

    JsonHelper::from_json(json.at(ApplicationInstallation::F_VARIABLES), item.m_variables);
}

void to_json(nlohmann::json & j, const ApplicationInstallation & item) {

    j = {
            {ApplicationInstallation::F_NAME,      item.m_name},
            {ApplicationInstallation::F_VARIABLES, JsonHelper::to_json(item.m_variables)}
    };

    to_json(j, reinterpret_cast<const AbstractDomain&>(item) );
}

std::ostream & operator<<(std::ostream & stream, const ApplicationInstallation & applicationInstallation) {


    ToString(stream, "ApplicationInstallation") //
            .field("m_id", applicationInstallation.id()) //
            .field("m_name", applicationInstallation.m_name) //
            .field("m_variables", applicationInstallation.m_variables); //

    return stream;
}


}
}
