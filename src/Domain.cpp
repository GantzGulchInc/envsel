/*
 * domain.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: gantzm
 */

#include "Domain.h"
#include "IO.h"

#include <iostream>

using nlohmann::json;

namespace gg {
namespace envsel {

static const char * TAG = "Domain";

//
// Script Variable
//

ScriptVariable::ScriptVariable() :
        m_name{""}, m_value{""} {

}

ScriptVariable::~ScriptVariable() {

}

//
// Application Installation
//

ApplicationInstallation::ApplicationInstallation() :
        m_id{""}, m_name{""} {

}

ApplicationInstallation::~ApplicationInstallation() {

}

//
// Application
//

Application::Application() :
        m_id{""}, m_name{""} {

}

Application::~Application() {

}

//
// Script Operation
//

ScriptOperation::ScriptOperation() :
        m_operation{""} {

}

ScriptOperation::~ScriptOperation() {

}

//
// Script
//

Script::Script() :
        m_id{""}, m_name{""}, m_ifSet{""} {

}

Script::~Script() {

}

//
// Environment App
//

EnvironmentApp::EnvironmentApp() :
        m_applicationId{""}, m_applicationInstallationId{""} {

}

EnvironmentApp::~EnvironmentApp() {

}

//
// Environment
//

Environment::Environment() :
        m_id{""}, m_name{""} {

}

Environment::~Environment() {

}

std::string Environment::name() const {
    return m_name;
}

void operator<<(Environment &environment, const json &jsonValue) {

    CLOG(TRACE, TAG) << "jsonValue = " << jsonValue;

    environment.m_id = jsonValue[ "id"];
    environment.m_name = jsonValue["name"];
}

std::ostream &operator<<(std::ostream &stream, const Environment &environment) {


    stream << "Environment:[";
    stream << "id=" << environment.m_id;
    stream << ",name=" << environment.m_name;
    stream << "]";

    return stream;


}

//
// Environments
//



Environments::Environments() {
    CLOG(TRACE, TAG) << "ctor()";
}

Environments::~Environments() {

}

std::string Environments::filename() const {
    return m_filename;
}

Environments &Environments::filename(const std::string &filename) {
    m_filename = filename;
    return *this;
}

void operator<<(Environments &environments, const json &jsonValue) {

    json environmentsJson = jsonValue["environments"];

    if (!environmentsJson.is_array()) {
        throw std::domain_error("environments is not an array.");
    }

    for (auto &environmentJson : environmentsJson) {

        std::unique_ptr<Environment> envPtr(new Environment{});

        Environment *env = envPtr.get();

        *(env) << environmentJson;

        environments.m_environments.push_back(std::move(envPtr));
    }

}

std::ostream &operator<<(std::ostream &stream, const Environments &environments) {

    stream << "Environments[";
    stream << "filename=" << environments.m_filename;
    stream << ",environments=[";
    stream << environments.m_environments;
    stream << "]";
    stream << "]";

    return stream;


}


}
}
