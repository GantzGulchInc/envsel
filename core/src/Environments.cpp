#include "Environments.h"
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
// Environments
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string Environments::F_APPLICATIONS{"applications"};
const std::string Environments::F_SCRIPTS{"scripts"};
const std::string Environments::F_PROJECTS{"projects"};

Environments::Environments() : AbstractDomain{} {
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

    from_json(json, reinterpret_cast<AbstractDomain&>(item) );

    json.at(Environments::F_PROJECTS).get_to(item.m_projects);
    json.at(Environments::F_SCRIPTS).get_to(item.m_scripts);
    json.at(Environments::F_APPLICATIONS).get_to(item.m_applications);

    CLOG(TRACE, TAG) << "done.";
}

void to_json(nlohmann::json &j, const Environments &item) {

    j = {
            {Environments::F_PROJECTS, to_json(item.m_projects)},
            {Environments::F_SCRIPTS,      to_json(item.m_scripts)},
            {Environments::F_APPLICATIONS, to_json(item.m_applications)}

    };

    to_json(j, reinterpret_cast<const AbstractDomain&>(item) );

}

std::ostream &operator<<(std::ostream &stream, const Environments &item) {

    CLOG(TRACE,TAG) << "called.";

    ToString(stream, "Environments") //
            .field("m_id", item.id()) //
            .field("m_projects", item.m_projects) //
            .field("m_scripts", item.m_scripts) //
            .field("m_applications", item.m_applications); //

    CLOG(TRACE,TAG) << "done.";

    return stream;
}


}
}
