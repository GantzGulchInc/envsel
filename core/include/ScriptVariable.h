#pragma once

#include "AbstractDomain.h"
#include "NonCopyable.h"

#include <nlohmann/json.hpp>

#include <string>
#include <memory>

namespace gg {
namespace envsel {


typedef std::map<std::string, std::string> VariableDictionary;

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ScriptVariable
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ScriptVariable : public AbstractDomain {
public:

    static const std::string F_NAME;
    static const std::string F_VALUE;

    ScriptVariable();

    virtual ~ScriptVariable();

    const std::string & name();

    const std::string & value();

    friend void from_json(const nlohmann::json & json, ScriptVariable & item);

    friend void to_json(nlohmann::json & j, const ScriptVariable & item);

    friend std::ostream & operator<<(std::ostream & stream, const ScriptVariable & item);

private:
    std::string m_name;
    std::string m_value;

};

typedef std::vector<std::unique_ptr<ScriptVariable>> ScriptVariableList;


}
}
