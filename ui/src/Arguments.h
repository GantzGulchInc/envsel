/*
 * ArgumentParser.h
 *
 *  Created on: Oct 13, 2018
 *      Author: gantzm
 */

#pragma once

#include "NonCopyable.h"

#include <string>

namespace gg {
namespace envsel {

enum SelectedCommand {

    NONE = 0,
    SELECT,
    EDIT,
    CHECK
};

// Forward declaration.
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

    friend std::ostream &operator<<(std::ostream &stream, const Arguments &arguments);

private:
    std::string m_logggingFilename;
    bool m_loggingConsole;
    SelectedCommand m_command;
    std::string m_inputFilename;
    std::string m_outputFilename;

    Arguments();
};

} /* namespace envsel */
} /* namespace gg */

