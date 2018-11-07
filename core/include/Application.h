#pragma once

#include "AbstractDomain.h"
#include "ApplicationInstallation.h"
#include "NonCopyable.h"

#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <memory>

namespace gg {
namespace envsel {


/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Application
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Application : public AbstractDomain {
public:

    static const std::string F_NAME;
    static const std::string F_INSTALLATIONS;

    Application();

    virtual ~Application();

    const std::string & name() const;

    const ApplicationInstallationList & installations() const;

    ApplicationInstallation * findInstallation(const std::string & id);


    friend void from_json(const nlohmann::json & json, Application & item);

    friend void to_json(nlohmann::json & j, const Application & item);

    friend std::ostream & operator<<(std::ostream & stream, const Application & application);

private:
    std::string m_name;
    ApplicationInstallationList m_installations;
};

typedef std::vector<std::unique_ptr<Application>> ApplicationList;


}
}
