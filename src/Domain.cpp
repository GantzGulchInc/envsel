/*
 * domain.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: gantzm
 */

#include "Domain.h"
#include "IO.h"
#include "ToString.h"
#include "JsonHelper.h"

#include <iostream>
#include <regex>

using nlohmann::json;

namespace gg {
namespace envsel {

static const char *TAG = "Domain";

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Script Variable
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string ScriptVariable::F_NAME{"name"};
const std::string ScriptVariable::F_VALUE{"value"};


ScriptVariable::ScriptVariable() :
        m_name{""}, m_value{""} {

    CLOG(TRACE, TAG) << "Called";
}

ScriptVariable::~ScriptVariable() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string &ScriptVariable::name() {
    return m_name;
}

const std::string &ScriptVariable::value() {
    return m_value;
}


void from_json(const nlohmann::json &json, ScriptVariable &item) {

    json.at(ScriptVariable::F_NAME).get_to(item.m_name);
    json.at(ScriptVariable::F_VALUE).get_to(item.m_value);

}


void to_json(nlohmann::json &j, const ScriptVariable &item) {

    j = {
            {ScriptVariable::F_NAME,  item.m_name},
            {ScriptVariable::F_VALUE, item.m_value}
    };
}

std::ostream &operator<<(std::ostream &stream, const ScriptVariable &scriptVariable) {


    ToString(stream, "ScriptVariable") //
            .field("m_name", scriptVariable.m_name) //
            .field("m_value", scriptVariable.m_value); //

    return stream;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Application Installation
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string ApplicationInstallation::F_ID{"id"};
const std::string ApplicationInstallation::F_NAME{"name"};
const std::string ApplicationInstallation::F_VARIABLES{"variables"};

ApplicationInstallation::ApplicationInstallation() :
        m_id{""}, m_name{""} {

    CLOG(TRACE, TAG) << "Called";
}

ApplicationInstallation::~ApplicationInstallation() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string &ApplicationInstallation::id() const {
    return m_id;
}

const std::string &ApplicationInstallation::name() const {
    return m_name;
}

const ScriptVariableList &ApplicationInstallation::variables() const {
    return m_variables;
}

void from_json(const nlohmann::json &json, ApplicationInstallation &item) {

    json.at(ApplicationInstallation::F_ID).get_to(item.m_id);
    json.at(ApplicationInstallation::F_NAME).get_to(item.m_name);

    JsonHelper::from_json(json.at(ApplicationInstallation::F_VARIABLES), item.m_variables);
}

void to_json(nlohmann::json &j, const ApplicationInstallation &item) {

    j = {
            {ApplicationInstallation::F_ID,        item.m_id},
            {ApplicationInstallation::F_NAME,      item.m_name},
            {ApplicationInstallation::F_VARIABLES, JsonHelper::to_json(item.m_variables)}
    };
}

std::ostream &operator<<(std::ostream &stream, const ApplicationInstallation &applicationInstallation) {


    ToString(stream, "ApplicationInstallation") //
            .field("m_id", applicationInstallation.m_id) //
            .field("m_name", applicationInstallation.m_name) //
            .field("m_variables", applicationInstallation.m_variables); //

    return stream;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Application
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string Application::F_ID{"id"};
const std::string Application::F_NAME{"name"};
const std::string Application::F_INSTALLATIONS{"installations"};

Application::Application() :
        m_id{""}, m_name{""} {

    CLOG(TRACE, TAG) << "Called";
}

Application::~Application() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string &Application::id() const {
    return m_id;
}

const std::string &Application::name() const {
    return m_name;
}

const ApplicationInstallationList &Application::installations() const {
    return m_installations;
}

void from_json(const nlohmann::json &json, Application &item) {

    json.at(Application::F_ID).get_to(item.m_id);
    json.at(Application::F_NAME).get_to(item.m_name);

    JsonHelper::from_json(json.at(Application::F_INSTALLATIONS), item.m_installations);
}

void to_json(nlohmann::json &j, const Application &item) {

    j = {
            {Application::F_ID,            item.m_id},
            {Application::F_NAME,          item.m_name},
            {Application::F_INSTALLATIONS, JsonHelper::to_json(item.m_installations)}
    };

}

std::ostream &operator<<(std::ostream &stream, const Application &application) {

    ToString(stream, "Application") //
            .field("m_id", application.m_id) //
            .field("m_name", application.m_name) //
            .field("m_installations", application.m_installations); //

    return stream;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Script Operation
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string ScriptCommand::F_COMMAND{"command"};
const std::string ScriptCommand::F_ARGUMENTS{"args"};

ScriptCommand::ScriptCommand() :
        m_command{""} {

    CLOG(TRACE, TAG) << "Called";
}

ScriptCommand::~ScriptCommand() {

    CLOG(TRACE, TAG) << "Called";
}


const std::string &ScriptCommand::operation() const {
    return m_command;
}

const std::vector<std::string> &ScriptCommand::arguments() const {
    return m_arguments;
}

static std::string expandVariables(std::string value, const VariableDictionary &variables) {

    const std::regex r{R"(#\{([^}]+)\})"};

    std::smatch match;

    while (std::regex_search(value, match, r)) {

        auto const expr = match[0];
        auto const name = match[1].str();

        std::string r = variables.count(name) ? variables.at(name) : "";

        value.replace(expr.first, expr.second, r);

    }

    return value;

}

void ScriptCommand::execute(const VariableDictionary &variables, std::vector<std::string> &output) const {

    if (m_command == "print") {

        for (auto arg : m_arguments) {

            auto v = expandVariables(arg, variables);

            output.push_back(v);
        }

    } else {

        // Uh oh.
    }

}


void from_json(const nlohmann::json &json, ScriptCommand &item) {

    json.at(ScriptCommand::F_COMMAND).get_to(item.m_command);
    json.at(ScriptCommand::F_ARGUMENTS).get_to(item.m_arguments);

}

void to_json(nlohmann::json &j, const ScriptCommand &item) {

    j = {
            {ScriptCommand::F_COMMAND,   item.m_command},
            {ScriptCommand::F_ARGUMENTS, item.m_arguments}
    };
}

std::ostream &operator<<(std::ostream &stream, const ScriptCommand &scriptOperation) {

    ToString(stream, "ScriptCommand") //
            .field("m_command", scriptOperation.m_command) //
            .field("m_arguments", scriptOperation.m_arguments); //

    return stream;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Script
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string Script::F_ID{"id"};
const std::string Script::F_NAME{"name"};
const std::string Script::F_IFSET{"ifSet"};
const std::string Script::F_COMMANDS{"commands"};

Script::Script() :
        m_id{""}, m_name{""}, m_ifSet{""} {

    CLOG(TRACE, TAG) << "Called";
}

Script::~Script() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string &Script::id() const {
    return m_id;
}

const std::string &Script::name() const {
    return m_name;
}

const std::string &Script::ifSet() const {
    return m_ifSet;
}

const ScriptCommandList &Script::commands() const {
    return m_commands;
}

void Script::execute(const VariableDictionary &variables, std::vector<std::string> &output) const {

    if (m_ifSet.length() > 0 && variables.count(m_ifSet) == 0) {
        return;
    }

    for (auto &op : m_commands) {

        op->execute(variables, output);

    }


}

void from_json(const nlohmann::json &json, Script &item) {

    json.at(Script::F_ID).get_to(item.m_id);
    json.at(Script::F_NAME).get_to(item.m_name);
    json.at(Script::F_IFSET).get_to(item.m_ifSet);

    JsonHelper::from_json(json.at(Script::F_COMMANDS), item.m_commands);
}

void to_json(nlohmann::json &j, const Script &item) {

    j = {
            {Script::F_ID,       item.m_id},
            {Script::F_NAME,     item.m_name},
            {Script::F_IFSET,    item.m_ifSet},
            {Script::F_COMMANDS, JsonHelper::to_json(item.m_commands)}
    };

}

std::ostream &operator<<(std::ostream &stream, const Script &script) {

    ToString(stream, "Script") //
            .field("m_id", script.m_id) //
            .field("m_name", script.m_name) //
            .field("m_ifSet", script.m_ifSet) //
            .field("m_commands", script.m_commands); //

    return stream;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Environment App
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string EnvironmentApp::F_APPLICATION_ID{"applicationId"};
const std::string EnvironmentApp::F_DEFAULT_INSTALLATION_ID{"defaultInstallationId"};


EnvironmentApp::EnvironmentApp() :
        m_applicationId{""}, m_defaultInstallationId{""} {

    CLOG(TRACE, TAG) << "Called";
}

EnvironmentApp::~EnvironmentApp() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string &EnvironmentApp::applicationId() const {

    return m_applicationId;
}


const std::string &EnvironmentApp::defaultInstallationId() const {
    return m_defaultInstallationId;
}


const std::string &EnvironmentApp::currentInstalltionId() const {
    return m_currentInstallationId;
}

EnvironmentApp &EnvironmentApp::currentInstallationId(const std::string &id) {
    m_currentInstallationId = id;
    return *this;
}

void from_json(const nlohmann::json &json, EnvironmentApp &item) {

    json.at(EnvironmentApp::F_APPLICATION_ID).get_to(item.m_applicationId);
    json.at(EnvironmentApp::F_DEFAULT_INSTALLATION_ID).get_to(item.m_defaultInstallationId);

}

void to_json(nlohmann::json &j, const EnvironmentApp &item) {

    j = {
            {EnvironmentApp::F_APPLICATION_ID,          item.m_applicationId},
            {EnvironmentApp::F_DEFAULT_INSTALLATION_ID, item.m_defaultInstallationId}
    };

}

std::ostream &operator<<(std::ostream &stream, const EnvironmentApp &environmentApp) {

    ToString(stream, "EnvironmentApp") //
            .field("m_applicationId", environmentApp.m_applicationId) //
            .field("m_defaultInstallationId", environmentApp.m_defaultInstallationId) //
            .field("m_currentInstallationId", environmentApp.m_currentInstallationId); //

    return stream;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Environment
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string Environment::F_ID{"id"};
const std::string Environment::F_NAME{"name"};
const std::string Environment::F_APPS{"applications"};

Environment::Environment() :
        m_id{""}, m_name{""} {

    CLOG(TRACE, TAG) << "Called";
}

Environment::~Environment() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string &Environment::name() const {
    return m_name;
}

const EnvironmentAppList &Environment::apps() const {
    return m_environmentApps;
}

void from_json(const nlohmann::json &json, Environment &item) {

    json.at(Environment::F_ID).get_to(item.m_id);
    json.at(Environment::F_NAME).get_to(item.m_name);

    JsonHelper::from_json(json.at(Environment::F_APPS), item.m_environmentApps);
}

void to_json(nlohmann::json &j, const Environment &item) {

    j = {
            {Environment::F_ID,   item.m_id},
            {Environment::F_NAME, item.m_name},
            {Environment::F_APPS, JsonHelper::to_json(item.m_environmentApps)}
    };

}

std::ostream &operator<<(std::ostream &stream, const Environment &environment) {

    ToString(stream, "Environment") //
            .field<>("m_id", environment.m_id) //
            .field("m_name", environment.m_name) //
            .field("m_environmentApps", environment.m_environmentApps); //

    return stream;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Environments
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string Environments::F_APPLICATIONS{"applications"};
const std::string Environments::F_SCRIPTS{"scripts"};
const std::string Environments::F_ENVIRONMENTS{"environments"};

Environments::Environments() {
    CLOG(TRACE, TAG) << "Called";
}

Environments::~Environments() {

    CLOG(TRACE, TAG) << "Called";
}

ApplicationList & Environments::applications() {
    return m_applications;
}

Application *Environments::findApplication(const std::string &applicationId) const {

    for (auto &app : m_applications) {

        if (app->id() == applicationId) {
            return app.get();
        }

    }

    return nullptr;
}

ScriptList & Environments::scripts() {
    return m_scripts;
}

EnvironmentList &Environments::environments() {
    return m_environments;
}


void Environments::load(const std::string &filename) {

    CLOG(TRACE, TAG) << "filename: " << filename;

    CLOG(TRACE, TAG) << "Reading & parsing file...";

    nlohmann::json json = readJsonFile(filename);

    CLOG(TRACE, TAG) << "Converting json...";

    json.get_to(*this);

    CLOG(TRACE, TAG) << "Parsed: " << *this;
}


std::vector<std::string> Environments::executeScripts(const VariableDictionary &variables) {

    std::vector<std::string> results;

    for (auto &script : m_scripts) {
        script->execute(variables, results);
    }

    return results;
}


void from_json(const nlohmann::json &json, Environments &item) {

    CLOG(TRACE, TAG) << "called.";

    JsonHelper::from_json(json.at(Environments::F_ENVIRONMENTS), item.m_environments);
    JsonHelper::from_json(json.at(Environments::F_SCRIPTS), item.m_scripts);
    JsonHelper::from_json(json.at(Environments::F_APPLICATIONS), item.m_applications);

    CLOG(TRACE, TAG) << "done.";
}

void to_json(nlohmann::json &j, const Environments &item) {

    j = {
            {Environments::F_ENVIRONMENTS, JsonHelper::to_json(item.m_environments)},
            {Environments::F_SCRIPTS,      JsonHelper::to_json(item.m_scripts)},
            {Environments::F_APPLICATIONS, JsonHelper::to_json(item.m_applications)}

    };

}

std::ostream &operator<<(std::ostream &stream, const Environments &environments) {

    CLOG(TRACE,TAG) << "called.";

    ToString(stream, "Environments") //
            .field("m_environments", environments.m_environments) //
            .field("m_scripts", environments.m_scripts) //
            .field("m_applications", environments.m_applications); //

    CLOG(TRACE,TAG) << "done.";

    return stream;
}


}
}
