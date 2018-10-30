#pragma once

#include "ProjectApp.h"
#include "NonCopyable.h"

#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <memory>

namespace gg {
namespace envsel {

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Environment
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Project : public NonCopyable {
public:

    static const std::string F_ID;
    static const std::string F_NAME;
    static const std::string F_APPS;

    Project();

    virtual ~Project();

    const std::string &name() const;

    const ProjectAppList &apps() const;

    friend void from_json(const nlohmann::json &json, Project &item);

    friend void to_json(nlohmann::json &j, const Project &item);

    friend std::ostream &operator<<(std::ostream &stream, const Project &environment);

private:
    std::string m_id;
    std::string m_name;
    ProjectAppList m_projectApps;
};

typedef std::vector<std::unique_ptr<Project>> ProjectList;

}
}
