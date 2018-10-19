/*
 * domain.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: gantzm
 */

#include "Domain.h"
#include "IO.h"
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

ScriptVariable::ScriptVariable() :
        m_name{""}, m_value{""} {

    CLOG(TRACE, TAG) << "Called";
}

ScriptVariable::~ScriptVariable() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string & ScriptVariable::name(){
    return  m_name;
}

const std::string & ScriptVariable::value() {
    return m_value;
}


void from_json(const nlohmann::json &json, ScriptVariable &item) {

    json.at("name").get_to(item.m_name);
    json.at("value").get_to(item.m_value);

}


void to_json(nlohmann::json &j, const ScriptVariable &item) {

    j = {
            {"name",  item.m_name},
            {"value", item.m_value}
    };
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

const std::string &ApplicationInstallation::id() const {
    return m_id;
}

const std::string &ApplicationInstallation::name() const {
    return m_name;
}

const ScriptVariableList & ApplicationInstallation::variables() const {
    return m_variables;
}

void from_json(const nlohmann::json &json, ApplicationInstallation &item) {

    json.at("id").get_to(item.m_id);
    json.at("name").get_to(item.m_name);

    JsonHelper::from_json(json.at("variables"), item.m_variables);
}

void to_json(nlohmann::json &j, const ApplicationInstallation &item) {

    j = {
            {"id",        item.m_id},
            {"name",      item.m_name},
            {"variables", JsonHelper::to_json(item.m_variables)}
    };
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

    json.at("id").get_to(item.m_id);
    json.at("name").get_to(item.m_name);

    JsonHelper::from_json(json.at("installed"), item.m_installations);
}

void to_json(nlohmann::json &j, const Application &item) {

    j = {
            {"id",        item.m_id},
            {"name",      item.m_name},
            {"installed", JsonHelper::to_json(item.m_installations)}
    };

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


const std::string & ScriptOperation::operation() const {
    return m_operation;
}

const std::vector<std::string> & ScriptOperation::arguments() const {
    return m_arguments;
}

static std::string expandVariables(std::string value, const std::map<std::string, std::string> &variables ) {

    const std::regex r{R"(#\{([^}]+)\})"};

    std::smatch match;

    while( std::regex_search(value, match, r) ){

        auto const expr = match[0];
        auto const name = match[1].str();

        CLOG(TRACE, TAG) << "doing it:";
        CLOG(TRACE, TAG) << "   expr: " << expr;
        CLOG(TRACE, TAG) << "   name: " << name;

        std::string r = variables.count( name ) ? variables.at(name) : "";

        value.replace(expr.first, expr.second, r);

    }

    return value;

}

void ScriptOperation::execute(const std::map<std::string, std::string> &variables, std::vector<std::string> &output) const {

    if( m_operation == "print" ) {

        for(auto arg : m_arguments){

            auto v = expandVariables(arg, variables);

            output.push_back(v);
        }

    }else{

        // Uh oh.
    }

}


void from_json(const nlohmann::json &json, ScriptOperation &item) {

    json.at("op").get_to(item.m_operation);
    json.at("args").get_to(item.m_arguments);

}

void to_json(nlohmann::json &j, const ScriptOperation &item) {

    j = {
            {"op",   item.m_operation},
            {"args", item.m_arguments}
    };
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

const std::string & Script::id() const {
    return m_id;
}

const std::string & Script::name() const {
    return m_name;
}

const std::string & Script::ifSet() const {
    return m_ifSet;
}

const ScriptOperationList & Script::operations() const {
    return m_operations;
}

void Script::execute(const std::map<std::string, std::string> &variables, std::vector<std::string> &output) const {

    if( m_ifSet.length() > 0 && variables.count(m_ifSet) == 0 ) {
        return;
    }

    for(auto & op : m_operations) {

        op->execute(variables, output);

    }


}

void from_json(const nlohmann::json &json, Script &item) {

    CLOG(TRACE, TAG) << "Parsing a script.";

    json.at("id").get_to(item.m_id);
    json.at("name").get_to(item.m_name);
    json.at("ifSet").get_to(item.m_ifSet);

    JsonHelper::from_json(json.at("instructions"), item.m_operations);
}

void to_json(nlohmann::json &j, const Script &item) {

    j = {
            {"id",           item.m_id},
            {"name",         item.m_name},
            {"ifSet",        item.m_ifSet},
            {"instructions", JsonHelper::to_json(item.m_operations)}
    };

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

const std::string &EnvironmentApp::applicationId() const {

    return m_applicationId;
}


const std::string &EnvironmentApp::installationId() const {
    return m_applicationInstallationId;
}

void from_json(const nlohmann::json &json, EnvironmentApp &item) {

    json.at("id").get_to(item.m_applicationId);
    json.at("default").get_to(item.m_applicationInstallationId);

}

void to_json(nlohmann::json &j, const EnvironmentApp &item) {

    j = {
            {"id",      item.m_applicationId},
            {"default", item.m_applicationInstallationId}
    };

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

const std::string &Environment::name() const {
    return m_name;
}

const EnvironmentAppList &Environment::apps() const {
    return m_environmentApps;
}

void from_json(const nlohmann::json &json, Environment &item) {

    json.at("id").get_to(item.m_id);
    json.at("name").get_to(item.m_name);

    JsonHelper::from_json(json.at("apps"), item.m_environmentApps);
}

void to_json(nlohmann::json &j, const Environment &item) {

    j = {
            {"id",   item.m_id},
            {"name", item.m_name},
            {"apps", JsonHelper::to_json(item.m_environmentApps)}
    };

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

const std::string &Environments::filename() const {
    return m_filename;
}

Environments &Environments::filename(const std::string &filename) {
    m_filename = filename;
    return *this;
}

Application *Environments::findApplication(const std::string &applicationId) const {

    for (auto &app : m_applications) {

        if (app->id() == applicationId) {
            return app.get();
        }

    }

    return nullptr;
}


const EnvironmentList &Environments::environments() const {
    return m_environments;
}



std::vector<std::string> Environments::executeScripts(const std::map<std::string, std::string> &variables) {

    std::vector<std::string> results;

    for( auto & script : m_scripts ) {
        script->execute(variables, results);
    }

    return results;
}


void from_json(const nlohmann::json &json, Environments &item) {

    CLOG(TRACE, TAG) << "called.";

    JsonHelper::from_json(json.at("environments"), item.m_environments);
    JsonHelper::from_json(json.at("scripts"), item.m_scripts);
    JsonHelper::from_json(json.at("applications"), item.m_applications);

}

void to_json(nlohmann::json &j, const Environments &item) {

    j = {
            {"environments", JsonHelper::to_json(item.m_environments)},
            {"scripts",      JsonHelper::to_json(item.m_scripts)},
            {"applications", JsonHelper::to_json(item.m_applications)}

    };

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
