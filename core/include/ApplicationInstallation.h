#pragma once

#include "ScriptVariable.h"
#include "AbstractDomain.h"
#include "NonCopyable.h"

#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <memory>

namespace gg {
namespace envsel {


/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ApplicationInstallation
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ApplicationInstallation : public AbstractDomain {
public:

    static const std::string F_NAME;
    static const std::string F_VARIABLES;

    ApplicationInstallation();

    virtual ~ApplicationInstallation();

    const std::string & name() const;

    ScriptVariableList & variables();

    void addVariables(VariableDictionary & dictionary) const;


    friend void from_json(const nlohmann::json & json, ApplicationInstallation & item);

    friend void to_json(nlohmann::json & j, const ApplicationInstallation & item);

    friend std::ostream & operator<<(std::ostream & stream, const ApplicationInstallation & item);

private:
    std::string m_name;
    ScriptVariableList m_variables;

};

typedef std::vector<std::unique_ptr<ApplicationInstallation>> ApplicationInstallationList;


}
}
