/*
 * domain.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: gantzm
 */

#include "domain.h"

#include <iostream>

using nlohmann::json;

namespace gg {
namespace envsel {

//
// Script Variable
//

ScriptVariable::ScriptVariable() :
        m_name { "" }, m_value { "" } {

}

ScriptVariable::~ScriptVariable() {

}

//
// Application Installation
//

ApplicationInstallation::ApplicationInstallation() :
        m_id { "" }, m_name { "" }, m_variables { 5 } {

}

ApplicationInstallation::~ApplicationInstallation() {

}

//
// Application
//

Application::Application() :
        m_id { "" }, m_name { "" }, m_installations { 15 } {

}

Application::~Application() {

}

//
// Script Operation
//

ScriptOperation::ScriptOperation() :
        m_operation { "" }, m_arguments { 5 } {

}

ScriptOperation::~ScriptOperation() {

}

//
// Script
//

Script::Script() :
        m_id { "" }, m_name { "" }, m_ifSet { "" }, m_operations { 5 } {

}

Script::~Script() {

}

//
// Environment App
//

EnvironmentApp::EnvironmentApp() :
        m_applicationId { "" }, m_applicationInstallationId { "" } {

}

EnvironmentApp::~EnvironmentApp() {

}

//
// Environment
//

Environment::Environment() :
        m_id { "" }, m_name { "" }, m_environmentApps { 10 } {

}

Environment::~Environment() {

}

void operator<<(Environment & environment, const json & jsonValue) {

    std::cout << "jsonValue = " << jsonValue << std::endl;

    environment.m_id = jsonValue["id"];
    environment.m_name = jsonValue["name"];
}

//
// Environments
//

Environments::Environments() :
        m_applications { 10 }, m_scripts { 30 }, m_environments { 20 } {

}

Environments::~Environments() {

}

void operator<<(Environments & environments, const json & jsonValue) {

    json environmentArray = jsonValue["environments"];

    if (environmentArray.is_array()) {

        for (auto & environmentJson : environmentArray) {

            std::unique_ptr<Environment> env(new Environment { });

            *(env.get()) << environmentJson;

            environments.m_environments.push_back(std::move(env));
        }
    }

}

}
}
