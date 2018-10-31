#pragma once

#include "Application.h"
#include "Script.h"
#include "Project.h"

#include "NonCopyable.h"

#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <memory>

namespace gg {
namespace envsel {


/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Environments
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Environments : public NonCopyable {
public:

    static const std::string F_APPLICATIONS;
    static const std::string F_SCRIPTS;
    static const std::string F_PROJECTS;

    Environments();

    virtual ~Environments();

    ApplicationList & applications();

    Application * findApplication(const std::string & applicationId) const;

    ScriptList & scripts();

    ProjectList & projects();

    void load(const std::string & filename);

    std::vector<std::string> executeScripts(const VariableDictionary & variables);

    friend void from_json(const nlohmann::json & json, Environments & item);

    friend void to_json(nlohmann::json & j, const Environments & item);

    friend std::ostream & operator<<(std::ostream & stream, const Environments & environments);

private:
    ApplicationList m_applications;
    ScriptList m_scripts;
    ProjectList m_projects;
};


}
}
