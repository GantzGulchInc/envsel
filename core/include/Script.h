#pragma once

#include "ScriptVariable.h"
#include "ScriptCommand.h"
#include "AbstractDomain.h"
#include "NonCopyable.h"

#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <memory>

namespace gg {
namespace envsel {


/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Script
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Script : public AbstractDomain {
public:

    static const std::string F_NAME;
    static const std::string F_IFSET;
    static const std::string F_COMMANDS;

    Script();

    virtual ~Script();

    const std::string & name() const;

    const std::string & ifSet() const;

    ScriptCommandList & commands();

    void execute(const VariableDictionary & variables, std::vector<std::string> & output) const;

    friend void from_json(const nlohmann::json & json, Script & item);

    friend void to_json(nlohmann::json & j, const Script & item);

    friend std::ostream & operator<<(std::ostream & stream, const Script & item);

private:
    std::string m_name;
    std::string m_ifSet;
    ScriptCommandList m_commands;
};

typedef std::vector<std::unique_ptr<Script>> ScriptList;


}
}
