#include "Project.h"
#include "IO.h"
#include "ToString.h"
#include "Json.h"

#include "easylogging++.h"

#include <regex>

using nlohmann::json;

namespace gg {
namespace envsel {

static const char * TAG = "Domain";




// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Project
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string Project::F_NAME{"name"};
const std::string Project::F_APPS{"applications"};

Project::Project() :
        AbstractDomain{}, m_name{""} {

    CLOG(TRACE, TAG) << "Called";
}

Project::~Project() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string & Project::name() const {
    return m_name;
}

const ProjectAppList & Project::apps() const {
    return m_projectApps;
}

void from_json(const nlohmann::json & json, Project & item) {

    from_json(json, reinterpret_cast<AbstractDomain&>(item) );

    json.at(Project::F_NAME).get_to(item.m_name);
    json.at(Project::F_APPS).get_to(item.m_projectApps);
}

void to_json(nlohmann::json & j, const Project & item) {

    j = {
            {Project::F_NAME, item.m_name},
            {Project::F_APPS, to_json(item.m_projectApps)}
    };

    to_json(j, reinterpret_cast<const AbstractDomain&>(item) );
}

std::ostream & operator<<(std::ostream & stream, const Project & item) {

    ToString(stream, "Project") //
            .field("m_id", item.id()) //
            .field("m_name", item.m_name) //
            .field("m_projectApps", item.m_projectApps); //

    return stream;
}


}
}
