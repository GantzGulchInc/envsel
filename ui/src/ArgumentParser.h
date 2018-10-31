#pragma once

#include "Arguments.h"

#include "NonCopyable.h"

#include "CLI/CLI.hpp"

#include <string>
#include <functional>

namespace gg {
namespace envsel {

typedef std::function<void(const Arguments &args)> SelectFunc;
typedef std::function<void(const Arguments &args)> EditFunc;
typedef std::function<void(const Arguments &args)> CheckFunc;

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ArgumentParser
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ArgumentParser  : public NonCopyable {
public:
    ArgumentParser(Arguments & args, const std::string &name, int argc, const char *const *argv);

    virtual ~ArgumentParser();

    bool parse();

private:
    Arguments & m_arguments;
    CLI::App m_app;
    int m_argc;
    const char *const *m_argv;

    CLI::App * createSelectCommand();
    CLI::App * createEditCommand();
    CLI::App * createCheckCommand();

    std::string getHomeDirectory();
};


} /* namespace envsel */
} /* namespace gg */

