/*
 * ArgumentParser.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: gantzm
 */

#include "ArgumentParser.h"

#include <iostream>

namespace gg {
namespace envsel {

ArgumentParser::ArgumentParser(const std::string &name, int argc, const char *const *argv, SelectFunc selFunc, EditFunc editFunc, CheckFunc checkFunc) :
        m_app{name},  //
        m_argc{argc}, //
        m_argv{argv}, //
        m_selFunc{selFunc}, //
        m_editFunc{editFunc}, m_checkFunc{checkFunc}, //
        m_selectCommand{nullptr}, //
        m_editCommand{nullptr}, //
        m_checkCommand{nullptr} {

    m_app.require_subcommand(1);

    m_selectCommand = m_app.add_subcommand("select", "Select an environment.");
    m_selectCommand->add_option("-f,--filename", m_selectFilename, "Environment file to use.")->required(true)->type_name("FILENAME");
    m_selectCommand->add_option("-o,--output", m_selectOutput, "Script filename to write.")->required(true)->type_name("OUTPUT_FILENAME");
    m_selectCommand->callback([this]() {
        this->m_selFunc(m_selectFilename, m_selectOutput);
    });

    m_editCommand = m_app.add_subcommand("edit", "Edit an environment file.");
    m_editCommand->add_option("-f,--filename", m_editFilename, "Environment file to edit.")->required(true);
    m_editCommand->callback([this]() {
        this->m_editFunc(m_editFilename);
    });

    m_checkCommand = m_app.add_subcommand("check", "Check an environment file.");
    m_checkCommand->add_option("-f,--filename", m_checkFilename, "Environment file to check.")->required(true);
    m_checkCommand->callback([this]() {
        this->m_checkFunc(m_checkFilename);
    });

}

ArgumentParser::~ArgumentParser() {

}

void ArgumentParser::parse() {

    try {

        m_app.parse(m_argc, m_argv);

    } catch (const CLI::ParseError &e) {

        int exitCode = m_app.exit(e);

    }

}

} /* namespace envsel */
} /* namespace gg */
