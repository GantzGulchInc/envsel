#include "ProjectApp.h"
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
// Project App
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string ProjectApp::F_APPLICATION_ID{"applicationId"};
const std::string ProjectApp::F_DEFAULT_INSTALLATION_ID{"defaultInstallationId"};


ProjectApp::ProjectApp() :
        AbstractDomain{}, m_applicationId{""}, m_defaultInstallationId{""} {

    CLOG(TRACE, TAG) << "Called";
}

ProjectApp::~ProjectApp() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string &ProjectApp::applicationId() const {

    return m_applicationId;
}


const std::string &ProjectApp::defaultInstallationId() const {
    return m_defaultInstallationId;
}


const std::string &ProjectApp::currentInstalltionId() const {
    return m_currentInstallationId;
}

ProjectApp &ProjectApp::currentInstallationId(const std::string &id) {
    m_currentInstallationId = id;
    return *this;
}

void from_json(const nlohmann::json &json, ProjectApp &item) {

    from_json(json, reinterpret_cast<AbstractDomain&>(item) );

    json.at(ProjectApp::F_APPLICATION_ID).get_to(item.m_applicationId);
    json.at(ProjectApp::F_DEFAULT_INSTALLATION_ID).get_to(item.m_defaultInstallationId);

}

void to_json(nlohmann::json &j, const ProjectApp &item) {

    j = {
            {ProjectApp::F_APPLICATION_ID,          item.m_applicationId},
            {ProjectApp::F_DEFAULT_INSTALLATION_ID, item.m_defaultInstallationId}
    };

    to_json(j, reinterpret_cast<const AbstractDomain&>(item) );
}

std::ostream &operator<<(std::ostream &stream, const ProjectApp &item) {

    ToString(stream, "ProjectApp") //
            .field("m_id", item.id()) //
            .field("m_applicationId", item.m_applicationId) //
            .field("m_defaultInstallationId", item.m_defaultInstallationId) //
            .field("m_currentInstallationId", item.m_currentInstallationId); //

    return stream;
}



}
}
