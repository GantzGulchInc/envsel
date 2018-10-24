/*
 * ArgumentParser.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: gantzm
 */

#include "ArgumentParser.h"

#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

namespace gg {
namespace envsel {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Arguments
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Arguments &Arguments::instance() {

    static Arguments instance;

    return instance;
}

Arguments::Arguments() :
        m_enableLogging{false}, m_command{SelectedCommand::NONE}, m_inputFilename{""}, m_outputFilename{""} {

}

Arguments::~Arguments() {

}

bool Arguments::wasParsed() {
    return m_command != SelectedCommand ::NONE;
}

bool Arguments::loggingEnabled() {
    return m_enableLogging;
}


SelectedCommand Arguments::command() {
    return m_command;
}

Arguments &Arguments::command(SelectedCommand command) {

    m_command = command;

    return *this;
}

Arguments &Arguments::inputFilename(const std::string &inputFilename) {

    m_inputFilename = inputFilename;

    return *this;
}

const std::string &Arguments::inputFilename() const {
    return m_inputFilename;
}

Arguments &Arguments::outputFilename(const std::string &outputFilename) {

    m_outputFilename = outputFilename;

    return *this;
}

const std::string &Arguments::outputFilename() const {
    return m_outputFilename;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// ArgumentParser
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

ArgumentParser::ArgumentParser(Arguments &args, const std::string &name, int argc, const char *const *argv) :
        m_arguments{ args }, //
        m_app{name},  //
        m_argc{argc}, //
        m_argv{argv} {

    m_arguments.inputFilename(getHomeDirectory() + "/.environments.json");

    m_app.require_subcommand(1);

    m_app.add_flag("-l,--logging", m_arguments.m_enableLogging, "Enable logging");

    createSelectCommand();

    createEditCommand();

    createCheckCommand();

}

ArgumentParser::~ArgumentParser() {

}

bool ArgumentParser::parse() {

    try {

        m_app.parse(m_argc, m_argv);

        return true;

    } catch (const CLI::ParseError &e) {

        m_app.exit(e);

        return false;

    }

}

CLI::App *ArgumentParser::createSelectCommand() {

    CLI::App *selectCommand = m_app.add_subcommand("select", "Select an environment.");

    selectCommand->add_option("-f,--filename", m_arguments.m_inputFilename, "Project file to use.")->type_name("FILENAME");
    selectCommand->add_option("-o,--output", m_arguments.m_outputFilename, "Script filename to write.")->required(true)->type_name("OUTPUT_FILENAME");

    selectCommand->callback([this]() {
        this->m_arguments.command(SelectedCommand::SELECT);
    });

    return selectCommand;
}

CLI::App *ArgumentParser::createEditCommand() {

    CLI::App *editCommand = m_app.add_subcommand("edit", "Edit an environment file.");

    editCommand->add_option("-f,--filename", m_arguments.m_inputFilename, "Project file to edit.");

    editCommand->callback([this]() {
        this->m_arguments.command(SelectedCommand::EDIT);
    });

    return editCommand;
}

CLI::App *ArgumentParser::createCheckCommand() {

    CLI::App *checkCommand = m_app.add_subcommand("check", "Check an environment file.");

    checkCommand->add_option("-f,--filename", m_arguments.m_inputFilename, "Project file to check.")->required(true);

    checkCommand->callback([this]() {
        this->m_arguments.command(SelectedCommand::CHECK);
    });

    return checkCommand;
}

std::string ArgumentParser::getHomeDirectory() {

    char *userHome = getenv("HOME");

    if (userHome == nullptr) {

        userHome = getpwuid(getuid())->pw_dir;

    }

    return std::string(userHome);
}

} /* namespace envsel */
} /* namespace gg */
