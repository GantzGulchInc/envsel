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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Arguments
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Arguments::Arguments() :
        m_wasParsed(false),  m_inputFilename(""), m_outputFilename("") {


}

Arguments::~Arguments() {

}

bool Arguments::wasParsed() {
    return m_wasParsed;
}

Arguments &Arguments::inputFilename(const std::string &inputFilename) {
    m_inputFilename = inputFilename;
}

const std::string &Arguments::inputFilename() const {
    return m_inputFilename;
}

Arguments &Arguments::outputFilename(const std::string &outputFilename) {
    m_outputFilename = outputFilename;
}

const std::string &Arguments::outputFilename() const {
    return m_outputFilename;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// ArgumentParser
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

ArgumentParser::ArgumentParser(Arguments & args, const std::string &name, int argc, const char *const *argv, SelectFunc selFunc, EditFunc editFunc, CheckFunc checkFunc) :
        m_arguments(args), //
        m_app{name},  //
        m_argc{argc}, //
        m_argv{argv}, //
        m_selFunc{selFunc}, //
        m_editFunc{editFunc}, //
        m_checkFunc{checkFunc} {

    m_app.require_subcommand(1);

    createSelectCommand();

    createEditCommand();

    createCheckCommand();

}

ArgumentParser::~ArgumentParser() {

}

CLI::App * ArgumentParser::createSelectCommand() {

    CLI::App * selectCommand = m_app.add_subcommand("select", "Select an environment.");

    selectCommand->add_option("-f,--filename", m_arguments.m_inputFilename, "Environment file to use.")->required(true)->type_name("FILENAME");
    selectCommand->add_option("-o,--output", m_arguments.m_outputFilename, "Script filename to write.")->required(true)->type_name("OUTPUT_FILENAME");

    selectCommand->callback([this]() {
        this->m_arguments.m_wasParsed = true;
        this->m_selFunc(this->m_arguments);
    });

    return selectCommand;
}

CLI::App * ArgumentParser::createEditCommand(){

    CLI::App *editCommand = m_app.add_subcommand("edit", "Edit an environment file.");

    editCommand->add_option("-f,--filename", m_arguments.m_inputFilename, "Environment file to edit.")->required(true);

    editCommand->callback([this]() {
        this->m_arguments.m_wasParsed = true;
        this->m_editFunc(this->m_arguments);
    });

    return editCommand;
}

CLI::App * ArgumentParser::createCheckCommand(){

    CLI::App *checkCommand = m_app.add_subcommand("check", "Check an environment file.");

    checkCommand->add_option("-f,--filename", m_arguments.m_inputFilename, "Environment file to check.")->required(true);

    checkCommand->callback([this]() {
        this->m_arguments.m_wasParsed = true;
        this->m_checkFunc(this->m_arguments);
    });

    return checkCommand;
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
