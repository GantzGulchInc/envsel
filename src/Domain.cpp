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

static const char *TAG = "Domain";

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Script Variable
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

ScriptVariable::ScriptVariable() :
        m_name{""}, m_value{""} {

    CLOG(TRACE, TAG) << "Called";
}

ScriptVariable::~ScriptVariable() {

    CLOG(TRACE, TAG) << "Called";
}

void operator<<(ScriptVariable &scriptVariable, const nlohmann::json &jsonValue) {

    CLOG(TRACE, TAG) << "jsonValue = " << jsonValue;

    scriptVariable.m_name = jsonValue.at("name");
    scriptVariable.m_value = jsonValue.at("value");

}

std::ostream &operator<<(std::ostream &stream, const ScriptVariable &scriptVariable) {

    stream << "ScriptVariable:[" //
           << "name=" << scriptVariable.m_name //
           << ",value=" << scriptVariable.m_value //
           << "]";

    return stream;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Application Installation
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

ApplicationInstallation::ApplicationInstallation() :
        m_id{""}, m_name{""} {

    CLOG(TRACE, TAG) << "Called";
}

ApplicationInstallation::~ApplicationInstallation() {

    CLOG(TRACE, TAG) << "Called";
}

void operator<<(ApplicationInstallation &applicationInstallation, const nlohmann::json &jsonValue) {

    CLOG(TRACE, TAG) << "jsonValue = " << jsonValue;

    applicationInstallation.m_id = jsonValue.at("id");
    applicationInstallation.m_name = jsonValue.at("name");

    json scriptVariablesJson = jsonValue.at("variables");

    if (!scriptVariablesJson.is_array()) {
        throw std::domain_error("variables is not an array.");
    }

    for (auto &variableJson : scriptVariablesJson) {

        std::unique_ptr<ScriptVariable> ptr(new ScriptVariable{});

        *ptr << variableJson;

        applicationInstallation.m_variables.push_back(std::move(ptr));
    }
}

std::ostream &operator<<(std::ostream &stream, const ApplicationInstallation &applicationInstallation) {

    stream << "ApplicationInstallation:[" //
           << "id=" << applicationInstallation.m_id //
           << ",name=" << applicationInstallation.m_name //
           << ",variables=[" << applicationInstallation.m_variables << "]" //
           << "]";

    return stream;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Application
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Application::Application() :
        m_id{""}, m_name{""} {

    CLOG(TRACE, TAG) << "Called";
}

Application::~Application() {

    CLOG(TRACE, TAG) << "Called";
}

void operator<<(Application &application, const nlohmann::json &jsonValue) {

    CLOG(TRACE, TAG) << "jsonValue = " << jsonValue;

    application.m_id = jsonValue.at("id");
    application.m_name = jsonValue.at("name");

    json installationJson = jsonValue.at("installed");

    if (!installationJson.is_array()) {
        throw std::domain_error("installed is not an array.");
    }

    for (auto &instJson : installationJson) {

        std::unique_ptr<ApplicationInstallation> ptr(new ApplicationInstallation{});

        *ptr << instJson;

        application.m_installations.push_back(std::move(ptr));
    }
}

std::ostream &operator<<(std::ostream &stream, const Application &application) {

    stream << "Application:[" //
           << "id=" << application.m_id //
           << ",name=" << application.m_name //
           << ",installations=[" << application.m_installations << "]" //
           << "]";

    return stream;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Script Operation
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

ScriptOperation::ScriptOperation() :
        m_operation{""} {

    CLOG(TRACE, TAG) << "Called";
}

ScriptOperation::~ScriptOperation() {

    CLOG(TRACE, TAG) << "Called";
}


void operator<<(ScriptOperation &scriptOperation, const nlohmann::json &jsonValue) {

    CLOG(TRACE, TAG) << "jsonValue = " << jsonValue;

    scriptOperation.m_operation = jsonValue.at("op");

    for (auto &argJson : jsonValue.at("args")) {
        std::string arg = argJson;
        scriptOperation.m_arguments.push_back(arg);
    }
}

std::ostream &operator<<(std::ostream &stream, const ScriptOperation &scriptOperation) {

    stream << "ScriptOperation:[" //
           << "op=" << scriptOperation.m_operation //
           << "args=[" << scriptOperation.m_arguments << "]" //
           << "]";

    return stream;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Script
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Script::Script() :
        m_id{""}, m_name{""}, m_ifSet{""} {

    CLOG(TRACE, TAG) << "Called";
}

Script::~Script() {

    CLOG(TRACE, TAG) << "Called";
}

void operator<<(Script &script, const nlohmann::json &jsonValue) {

    CLOG(TRACE, TAG) << "jsonValue = " << jsonValue;

    script.m_id = jsonValue.at("id");
    script.m_name = jsonValue.at("name");
    script.m_ifSet = jsonValue.at("ifSet");

    json opsJson = jsonValue.at("instructions");

    if (!opsJson.is_array()) {
        throw std::domain_error("instructions is not an array.");
    }

    for (auto &opJson : opsJson) {

        std::unique_ptr<ScriptOperation> ptr(new ScriptOperation{});

        *ptr << opJson;

        script.m_operations.push_back(std::move(ptr));
    }


}

std::ostream &operator<<(std::ostream &stream, const Script &script) {

    stream << "Script:[" //
           << "id=" << script.m_id //
           << ",name=" << script.m_name //
           << ",ifSet=" << script.m_ifSet //
           << ",operations=[" << script.m_operations << "]" //
           << "]";

    return stream;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Environment App
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

EnvironmentApp::EnvironmentApp() :
        m_applicationId{""}, m_applicationInstallationId{""} {

    CLOG(TRACE, TAG) << "Called";
}

EnvironmentApp::~EnvironmentApp() {

    CLOG(TRACE, TAG) << "Called";
}

void operator<<(EnvironmentApp &environmentApp, const nlohmann::json &jsonValue) {

    CLOG(TRACE, TAG) << "jsonValue = " << jsonValue;

    environmentApp.m_applicationId = jsonValue.at("id");
    environmentApp.m_applicationInstallationId = jsonValue.at("default");


}

void operator<<(nlohmann::json &jsonValue, const EnvironmentApp &environmentApp) {

    jsonValue["id"] = environmentApp.m_applicationId;
    jsonValue["default"] = environmentApp.m_applicationInstallationId;

}

std::ostream &operator<<(std::ostream &stream, const EnvironmentApp &environmentApp) {

    stream << "EnvironmentApp:["
           << "applicationId=" << environmentApp.m_applicationId //
           << ",installationId=" << environmentApp.m_applicationInstallationId //
           << "]";

    return stream;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Environment
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Environment::Environment() :
        m_id{""}, m_name{""} {

    CLOG(TRACE, TAG) << "Called";
}

Environment::~Environment() {

    CLOG(TRACE, TAG) << "Called";
}

std::string Environment::name() const {
    return m_name;
}

void operator<<(Environment &environment, const json &jsonValue) {

    CLOG(TRACE, TAG) << "jsonValue = " << jsonValue;

    environment.m_id = jsonValue.at("id");
    environment.m_name = jsonValue.at("name");


    json appsJson = jsonValue.at("apps");

    if (!appsJson.is_array()) {
        throw std::domain_error("apps is not an array.");
    }

    for (auto &appJson : appsJson) {

        std::unique_ptr<EnvironmentApp> ptr(new EnvironmentApp{});

        EnvironmentApp *app = ptr.get();

        *(app) << appJson;

        environment.m_environmentApps.push_back(std::move(ptr));
    }


}

void operator<<(nlohmann::json &jsonValue, const Environment &environment) {

    jsonValue["id"] = environment.m_id;
    jsonValue["name"] = environment.m_name;


    jsonValue["apps"] = nlohmann::json::array();

    nlohmann::json &appsArray = jsonValue.at("apps");

    for (auto &app : environment.m_environmentApps) {

        nlohmann::json appJson;

        appJson << *app;

        appsArray.push_back(appJson);
    }
}

std::ostream &operator<<(std::ostream &stream, const Environment &environment) {

    stream << "Environment:["
           << "id=" << environment.m_id
           << ",name=" << environment.m_name
           << ",apps=[" << environment.m_environmentApps << "]" <<
           "]";

    return stream;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Environments
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -



Environments::Environments() {
    CLOG(TRACE, TAG) << "Called";
}

Environments::~Environments() {

    CLOG(TRACE, TAG) << "Called";
}

std::string Environments::filename() const {
    return m_filename;
}

Environments &Environments::filename(const std::string &filename) {
    m_filename = filename;
    return *this;
}

void operator<<(Environments &environments, const json &jsonValue) {

    //
    // Environments
    //
    const json & environmentsJson = jsonValue.at("environments");

    if (!environmentsJson.is_array()) {
        throw std::domain_error("environments is not an array.");
    }

    for (auto &environmentJson : environmentsJson) {

        std::unique_ptr<Environment> ptr(new Environment{});
        *ptr << environmentJson;
        environments.m_environments.push_back(std::move(ptr));
    }

    //
    // Scripts
    //
    const json & scriptsJson = jsonValue.at("scripts");

    if (!scriptsJson.is_array()) {
        throw std::domain_error("scripts is not an array.");
    }

    for (auto &scriptJson : scriptsJson) {

        std::unique_ptr<Script> ptr(new Script{});
        *ptr << scriptJson;
        environments.m_scripts.push_back(std::move(ptr));
    }

    //
    // Applications
    //
    const json & applicationsJson = jsonValue.at("applications");

    if (!applicationsJson.is_array()) {
        throw std::domain_error("applications is not an array.");
    }

    for (auto &applicationJson : applicationsJson) {

        std::unique_ptr<Application> ptr(new Application{});
        *ptr << applicationJson;
        environments.m_applications.push_back(std::move(ptr));
    }

}

void operator<<(nlohmann::json &jsonValue, const Environments &environments) {


    jsonValue["environments"] = nlohmann::json::array();

    nlohmann::json &envArray = jsonValue.at("environments");

    for (auto &env : environments.m_environments) {

        nlohmann::json envJson;

        envJson << *env;

        envArray.push_back(envJson);
    }

    nlohmann::json scriptArray = nlohmann::json::array();
    jsonValue["scripts"] = scriptArray;

    nlohmann::json appArray = nlohmann::json::array();
    jsonValue["applications"] = appArray;

}

std::ostream &operator<<(std::ostream &stream, const Environments &environments) {

    stream << "Environments[" //
           << "filename=" << environments.m_filename //
           << ",environments=[" << environments.m_environments << "]" //
           << ",scripts=[" << environments.m_scripts << "]" //
           << ",applications=[" << environments.m_applications << "]" << //
           "]";

    return stream;
}


}
}
