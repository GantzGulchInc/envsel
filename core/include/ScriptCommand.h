#pragma once

#include "AbstractDomain.h"
#include "ScriptVariable.h"
#include "NonCopyable.h"

#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <memory>

namespace gg {
namespace envsel {


/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ScriptCommand
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ScriptCommand : public AbstractDomain {
public:

    static const std::string F_COMMAND;
    static const std::string F_ARGUMENTS;

    ScriptCommand();

    virtual ~ScriptCommand();

    const std::string & command() const;

    const std::vector<std::string> & arguments() const;

    void execute(const VariableDictionary & variables, std::vector<std::string> & output) const;


    friend void from_json(const nlohmann::json & json, ScriptCommand & item);

    friend void to_json(nlohmann::json & j, const ScriptCommand & item);

    friend std::ostream & operator<<(std::ostream & stream, const ScriptCommand & item);

private:
    std::string m_command;
    std::vector<std::string> m_arguments;
};

typedef std::vector<std::unique_ptr<ScriptCommand>> ScriptCommandList;


}
}
