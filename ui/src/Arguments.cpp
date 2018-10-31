#include "Arguments.h"

#include "ToString.h"

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
        m_logggingFilename{""}, m_loggingConsole{false}, m_command{SelectedCommand::NONE}, m_inputFilename{""}, m_outputFilename{""} {

}

Arguments::~Arguments() {

}

bool Arguments::wasParsed() {
    return m_command != SelectedCommand::NONE;
}

const std::string &Arguments::loggingFilename() {

    return m_logggingFilename;
}

bool Arguments::logggingConsole() {
    return m_loggingConsole;
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

std::ostream &operator<<(std::ostream &stream, const Arguments &arguments) {

    ToString(stream, "Arguments") //
            .field("m_logggingFilename", arguments.m_logggingFilename) //
            .field("m_loggingConsole", arguments.m_loggingConsole) //
            .field("m_command", arguments.m_command) //
            .field("m_inputFilename", arguments.m_inputFilename) //
            .field("m_outputFilename", arguments.m_outputFilename); //

    return stream;
}

} /* namespace envsel */
} /* namespace gg */
