/*
 * ArgumentParser.h
 *
 *  Created on: Oct 13, 2018
 *      Author: gantzm
 */

#pragma once

#include "CLI/CLI.hpp"

#include <string>

namespace gg {
namespace envsel {

enum Command {
    NONE = 0,
    SELECT,
    EDIT,
    CHECK
};

/**
 * Argument Parser
 */
class ArgumentParser {
public:
    ArgumentParser(const std::string & name);
    virtual ~ArgumentParser();

    Command parse(int argc, const char *const *argv);

private:
    CLI::App m_app;

    Command m_selected;

    CLI::App * m_selectCommand;
    std::string m_selectFilename;
    std::string m_selectOutput;

    CLI::App * m_editCommand;
    std::string m_editFilename;

    CLI::App * m_checkCommand;
    std::string m_checkFilename;

};

} /* namespace envsel */
} /* namespace gg */

