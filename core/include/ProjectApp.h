#pragma once

#include "AbstractDomain.h"
#include "NonCopyable.h"

#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <memory>

namespace gg {
namespace envsel {

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * EnvironmentApp
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ProjectApp : public AbstractDomain {
public:

    static const std::string F_APPLICATION_ID;
    static const std::string F_DEFAULT_INSTALLATION_ID;

    ProjectApp();

    virtual ~ProjectApp();

    const std::string & applicationId() const;

    const std::string & defaultInstallationId() const;

    const std::string & currentInstalltionId() const;

    ProjectApp & currentInstallationId(const std::string & id);

    friend void from_json(const nlohmann::json & json, ProjectApp & item);

    friend void to_json(nlohmann::json & j, const ProjectApp & item);

    friend std::ostream & operator<<(std::ostream & stream, const ProjectApp & environmentApp);

private:
    std::string m_applicationId;
    std::string m_defaultInstallationId;
    std::string m_currentInstallationId;
};

typedef std::vector<std::unique_ptr<ProjectApp>> ProjectAppList;


}
}
