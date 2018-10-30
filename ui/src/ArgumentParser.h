/*
 * ArgumentParser.h
 *
 *  Created on: Oct 13, 2018
 *      Author: gantzm
 */

#pragma once

#include "NonCopyable.h"

#include "CLI/CLI.hpp"

#include <string>
#include <functional>

namespace gg {
namespace envsel {

// Forward declaration.

enum SelectedCommand {

    NONE = 0,
    SELECT,
    EDIT,
    CHECK
};

class ArgumentParser;

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Arguments
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Arguments : NonCopyable {
public:

    static Arguments & instance();

    virtual ~Arguments();

    bool wasParsed();

    const std::string & loggingFilename();

    bool logggingConsole();

    SelectedCommand command();

    Arguments &command(SelectedCommand command);

    Arguments &inputFilename(const std::string &inputFilename);

    const std::string &inputFilename() const;

    Arguments &outputFilename(const std::string &outputFilename);

    const std::string &outputFilename() const;

    friend ArgumentParser;

private:
    std::string m_logggingFilename;
    bool m_loggingConsole;
    SelectedCommand m_command;
    std::string m_inputFilename;
    std::string m_outputFilename;

    Arguments();
};

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

