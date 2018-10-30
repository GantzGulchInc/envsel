#include "Domain.h"
#include "IO.h"
#include "ToString.h"
#include "JsonHelper.h"

#include <iostream>
#include <regex>

using nlohmann::json;

namespace gg {
namespace envsel {

static const char *TAG = "Domain";


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Application Installation
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string ApplicationInstallation::F_ID{"id"};
const std::string ApplicationInstallation::F_NAME{"name"};
const std::string ApplicationInstallation::F_VARIABLES{"variables"};

ApplicationInstallation::ApplicationInstallation() :
        m_id{""}, m_name{""} {

    CLOG(TRACE, TAG) << "Called";
}

ApplicationInstallation::~ApplicationInstallation() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string &ApplicationInstallation::id() const {
    return m_id;
}

const std::string &ApplicationInstallation::name() const {
    return m_name;
}

const ScriptVariableList &ApplicationInstallation::variables() const {
    return m_variables;
}

void from_json(const nlohmann::json &json, ApplicationInstallation &item) {

    json.at(ApplicationInstallation::F_ID).get_to(item.m_id);
    json.at(ApplicationInstallation::F_NAME).get_to(item.m_name);

    JsonHelper::from_json(json.at(ApplicationInstallation::F_VARIABLES), item.m_variables);
}

void to_json(nlohmann::json &j, const ApplicationInstallation &item) {

    j = {
            {ApplicationInstallation::F_ID,        item.m_id},
            {ApplicationInstallation::F_NAME,      item.m_name},
            {ApplicationInstallation::F_VARIABLES, JsonHelper::to_json(item.m_variables)}
    };
}

std::ostream &operator<<(std::ostream &stream, const ApplicationInstallation &applicationInstallation) {


    ToString(stream, "ApplicationInstallation") //
            .field("m_id", applicationInstallation.m_id) //
            .field("m_name", applicationInstallation.m_name) //
            .field("m_variables", applicationInstallation.m_variables); //

    return stream;
}



}
}
