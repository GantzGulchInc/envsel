/*
 * ArgumentParser.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: gantzm
 */

#include "ArgumentParser.h"

namespace gg {
namespace envsel {

ArgumentParser::ArgumentParser(const std::string & name) :
        m_app { name },  //
        m_selected { Command::NONE }, //
        m_selectCommand { m_app.add_subcommand("select", "Select an environment.") }, //
        m_editCommand { m_app.add_subcommand("edit", "Edit an environment file.") }, //
        m_checkCommand { m_app.add_subcommand("check", "Check an environment file.") } {

    m_app.require_subcommand(1);

    m_selectCommand->add_option("-f,--filename", m_selectFilename, "Environment file to use.")->required(true)->type_name("FILENAME");
    m_selectCommand->add_option("-o,--output", m_selectOutput, "Script filename to write.")->required(true)->type_name("OUTPUT_FILENAME");
    m_selectCommand->callback([this] () {this->m_selected = Command::SELECT;});

    m_editCommand->add_option("-f,--filename", m_editFilename, "Environment file to edit.")->required(true);
    m_editCommand->callback([this] () {this->m_selected = Command::EDIT;});

    m_checkCommand->add_option("-f,--filename", m_checkFilename, "Environment file to check.")->required(true);
    m_checkCommand->callback([this] () {this->m_selected = Command::CHECK;});

}

ArgumentParser::~ArgumentParser() {

}

Command ArgumentParser::parse(int argc, const char * const *argv) {

    try {

        m_app.parse(argc, argv);

        return m_selected;

    } catch (const CLI::ParseError &e) {

        int exitCode = m_app.exit(e);

        return Command::NONE;
    }

}

} /* namespace envsel */
} /* namespace gg */
