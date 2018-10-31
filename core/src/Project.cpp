#include "Project.h"
#include "IO.h"
#include "ToString.h"
#include "JsonHelper.h"

#include "easylogging++.h"

#include <iostream>
#include <regex>

using nlohmann::json;

namespace gg {
namespace envsel {

static const char *TAG = "Domain";




// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Project
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string Project::F_ID{"id"};
const std::string Project::F_NAME{"name"};
const std::string Project::F_APPS{"applications"};

Project::Project() :
        m_id{""}, m_name{""} {

    CLOG(TRACE, TAG) << "Called";
}

Project::~Project() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string &Project::name() const {
    return m_name;
}

const ProjectAppList &Project::apps() const {
    return m_projectApps;
}

void from_json(const nlohmann::json &json, Project &item) {

    json.at(Project::F_ID).get_to(item.m_id);
    json.at(Project::F_NAME).get_to(item.m_name);

    JsonHelper::from_json(json.at(Project::F_APPS), item.m_projectApps);
}

void to_json(nlohmann::json &j, const Project &item) {

    j = {
            {Project::F_ID,   item.m_id},
            {Project::F_NAME, item.m_name},
            {Project::F_APPS, JsonHelper::to_json(item.m_projectApps)}
    };

}

std::ostream &operator<<(std::ostream &stream, const Project &environment) {

    ToString(stream, "Project") //
            .field<>("m_id", environment.m_id) //
            .field("m_name", environment.m_name) //
            .field("m_projectApps", environment.m_projectApps); //

    return stream;
}



}
}
