/*
 * ArgumentParser.h
 *
 *  Created on: Oct 13, 2018
 *      Author: gantzm
 */

#pragma once

#include "CLI/CLI.hpp"

#include <string>
#include <functional>

namespace gg {
namespace envsel {

typedef std::function<void(const std::string &filename, const std::string &output)> SelectFunc;
typedef std::function<void(const std::string &filename)> EditFunc;
typedef std::function<void(const std::string &filename)> CheckFunc;

/**
 * Argument Parser
 */
class ArgumentParser {
public:
    ArgumentParser(const std::string &name, int argc, const char *const *argv, SelectFunc selFunc, EditFunc editFunc, CheckFunc checkFunc);

    virtual ~ArgumentParser();

    void parse();

private:
    CLI::App m_app;

    int m_argc;
    const char *const *m_argv;

    SelectFunc m_selFunc;
    EditFunc m_editFunc;
    CheckFunc m_checkFunc;

    CLI::App *m_selectCommand;
    std::string m_selectFilename;
    std::string m_selectOutput;

    CLI::App *m_editCommand;
    std::string m_editFilename;

    CLI::App *m_checkCommand;
    std::string m_checkFilename;

};

} /* namespace envsel */
} /* namespace gg */

