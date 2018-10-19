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

class ArgumentParser;

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Arguments
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Arguments : public NonCopyable {
public:
    Arguments();

    virtual ~Arguments();

    Arguments &inputFilename(const std::string &inputFilename);

    const std::string &inputFilename() const;

    Arguments &outputFilename(const std::string &outputFilename);

    const std::string &outputFilename() const;

    friend ArgumentParser;

private:

    std::string m_inputFilename;
    std::string m_outputFilename;

};

typedef std::function<void(const Arguments &args)> SelectFunc;
typedef std::function<void(const Arguments &args)> EditFunc;
typedef std::function<void(const Arguments &args)> CheckFunc;

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ArgumentParser
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ArgumentParser  : public NonCopyable {
public:
    ArgumentParser(Arguments & args, const std::string &name, int argc, const char *const *argv, SelectFunc selFunc, EditFunc editFunc, CheckFunc checkFunc);

    virtual ~ArgumentParser();

    void parse();

private:
    CLI::App m_app;

    int m_argc;
    const char *const *m_argv;

    SelectFunc m_selFunc;
    EditFunc m_editFunc;
    CheckFunc m_checkFunc;

    Arguments & m_arguments;
};

} /* namespace envsel */
} /* namespace gg */

