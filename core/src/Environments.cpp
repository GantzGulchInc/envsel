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
// Environments
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string Environments::F_APPLICATIONS{"applications"};
const std::string Environments::F_SCRIPTS{"scripts"};
const std::string Environments::F_PROJECTS{"projects"};

Environments::Environments() {
    CLOG(TRACE, TAG) << "Called";
}

Environments::~Environments() {

    CLOG(TRACE, TAG) << "Called";
}

ApplicationList & Environments::applications() {
    return m_applications;
}

Application *Environments::findApplication(const std::string &applicationId) const {

    for (auto &app : m_applications) {

        if (app->id() == applicationId) {
            return app.get();
        }

    }

    return nullptr;
}

ScriptList & Environments::scripts() {
    return m_scripts;
}

ProjectList &Environments::projects() {
    return m_projects;
}


void Environments::load(const std::string &filename) {

    CLOG(TRACE, TAG) << "filename: " << filename;

    CLOG(TRACE, TAG) << "Reading & parsing file...";

    nlohmann::json json = readJsonFile(filename);

    CLOG(TRACE, TAG) << "Converting json...";

    json.get_to(*this);

    CLOG(TRACE, TAG) << "Parsed: " << *this;
}


std::vector<std::string> Environments::executeScripts(const VariableDictionary &variables) {

    std::vector<std::string> results;

    for (auto &script : m_scripts) {
        script->execute(variables, results);
    }

    return results;
}


void from_json(const nlohmann::json &json, Environments &item) {

    CLOG(TRACE, TAG) << "called.";

    JsonHelper::from_json(json.at(Environments::F_PROJECTS), item.m_projects);
    JsonHelper::from_json(json.at(Environments::F_SCRIPTS), item.m_scripts);
    JsonHelper::from_json(json.at(Environments::F_APPLICATIONS), item.m_applications);

    CLOG(TRACE, TAG) << "done.";
}

void to_json(nlohmann::json &j, const Environments &item) {

    j = {
            {Environments::F_PROJECTS, JsonHelper::to_json(item.m_projects)},
            {Environments::F_SCRIPTS,      JsonHelper::to_json(item.m_scripts)},
            {Environments::F_APPLICATIONS, JsonHelper::to_json(item.m_applications)}

    };

}

std::ostream &operator<<(std::ostream &stream, const Environments &environments) {

    CLOG(TRACE,TAG) << "called.";

    ToString(stream, "Environments") //
            .field("m_projects", environments.m_projects) //
            .field("m_scripts", environments.m_scripts) //
            .field("m_applications", environments.m_applications); //

    CLOG(TRACE,TAG) << "done.";

    return stream;
}


}
}
