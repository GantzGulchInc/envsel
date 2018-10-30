#pragma once

#include "NonCopyable.h"

#include <nlohmann/json.hpp>
#include <easylogging++.h>

#include <string>
#include <vector>
#include <memory>

namespace gg {
namespace envsel {


/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ScriptOperation
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ScriptCommand : public NonCopyable {
public:

    static const std::string F_COMMAND;
    static const std::string F_ARGUMENTS;

    ScriptCommand();

    virtual ~ScriptCommand();

    const std::string &operation() const;

    const std::vector<std::string> &arguments() const;

    void execute(const VariableDictionary &variables, std::vector<std::string> &output) const;

    friend void from_json(const nlohmann::json &json, ScriptCommand &item);

    friend void to_json(nlohmann::json &j, const ScriptCommand &item);

    friend std::ostream &operator<<(std::ostream &stream, const ScriptCommand &scriptOperation);

private:
    std::string m_command;
    std::vector<std::string> m_arguments;
};

typedef std::vector<std::unique_ptr<ScriptCommand>> ScriptCommandList;



}
}
