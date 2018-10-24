/*
 * domain.h
 *
 *  Created on: Oct 14, 2018
 *      Author: gantzm
 */

#pragma once

#include "NonCopyable.h"

#include <nlohmann/json.hpp>
#include <easylogging++.h>

#include <string>
#include <vector>
#include <memory>

namespace gg {
namespace envsel {


typedef std::map<std::string,std::string> VariableDictionary;

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ScriptVariable
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ScriptVariable : public NonCopyable {
public:

    static const std::string F_NAME;
    static const std::string F_VALUE;

    ScriptVariable();

    virtual ~ScriptVariable();

    const std::string &name();

    const std::string &value();

    friend void from_json(const nlohmann::json &json, ScriptVariable &item);

    friend void to_json(nlohmann::json &j, const ScriptVariable &item);

    friend std::ostream &operator<<(std::ostream &stream, const ScriptVariable &scriptVariable);

private:
    std::string m_name;
    std::string m_value;

};

typedef std::vector<std::unique_ptr<ScriptVariable>> ScriptVariableList;

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ApplicationInstallation
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ApplicationInstallation : public NonCopyable {
public:

    static const std::string F_ID;
    static const std::string F_NAME;
    static const std::string F_VARIABLES;


    ApplicationInstallation();

    virtual ~ApplicationInstallation();

    const std::string &id() const;

    const std::string &name() const;

    const ScriptVariableList &variables() const;

    friend void from_json(const nlohmann::json &json, ApplicationInstallation &item);

    friend void to_json(nlohmann::json &j, const ApplicationInstallation &item);

    friend std::ostream &operator<<(std::ostream &stream, const ApplicationInstallation &applicationInstallation);

private:
    std::string m_id;
    std::string m_name;
    ScriptVariableList m_variables;

};

typedef std::vector<std::unique_ptr<ApplicationInstallation>> ApplicationInstallationList;

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Application
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Application : public NonCopyable {
public:

    static const std::string F_ID;
    static const std::string F_NAME;
    static const std::string F_INSTALLATIONS;

    Application();

    virtual ~Application();

    const std::string &id() const;

    const std::string &name() const;

    const ApplicationInstallationList &installations() const;

    ApplicationInstallation * findInstallation(const std::string & id);

    friend void from_json(const nlohmann::json &json, Application &item);

    friend void to_json(nlohmann::json &j, const Application &item);

    friend std::ostream &operator<<(std::ostream &stream, const Application &application);

private:
    std::string m_id;
    std::string m_name;
    ApplicationInstallationList m_installations;
};

typedef std::vector<std::unique_ptr<Application>> ApplicationList;

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ScriptOperation
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ScriptCommand : public NonCopyable {
public:

    static const std::string F_COMMAND;
    static const std::string F_ARGUMENTS;

    ScriptCommand();

    virtual ~ScriptCommand();

    const std::string &operation() const;

    const std::vector<std::string> &arguments() const;

    void execute(const VariableDictionary &variables, std::vector<std::string> &output) const;

    friend void from_json(const nlohmann::json &json, ScriptCommand &item);

    friend void to_json(nlohmann::json &j, const ScriptCommand &item);

    friend std::ostream &operator<<(std::ostream &stream, const ScriptCommand &scriptOperation);

private:
    std::string m_command;
    std::vector<std::string> m_arguments;
};

typedef std::vector<std::unique_ptr<ScriptCommand>> ScriptCommandList;

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Script
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Script : public NonCopyable {
public:

    static const std::string F_ID;
    static const std::string F_NAME;
    static const std::string F_IFSET;
    static const std::string F_COMMANDS;

    Script();

    virtual ~Script();

    const std::string &id() const;

    const std::string &name() const;

    const std::string &ifSet() const;

    const ScriptCommandList &commands() const;

    void execute(const VariableDictionary &variables, std::vector<std::string> &output) const;

    friend void from_json(const nlohmann::json &json, Script &item);

    friend void to_json(nlohmann::json &j, const Script &item);

    friend std::ostream &operator<<(std::ostream &stream, const Script &script);

private:
    std::string m_id;
    std::string m_name;
    std::string m_ifSet;
    ScriptCommandList m_commands;
};

typedef std::vector<std::unique_ptr<Script>> ScriptList;

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * EnvironmentApp
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ProjectApp : public NonCopyable {
public:

    static const std::string F_APPLICATION_ID;
    static const std::string F_DEFAULT_INSTALLATION_ID;

    ProjectApp();

    virtual ~ProjectApp();

    const std::string &applicationId() const;

    const std::string &defaultInstallationId() const;

    const std::string &currentInstalltionId() const;

    ProjectApp & currentInstallationId(const std::string & id);

    friend void from_json(const nlohmann::json &json, ProjectApp &item);

    friend void to_json(nlohmann::json &j, const ProjectApp &item);

    friend std::ostream &operator<<(std::ostream &stream, const ProjectApp &environmentApp);

private:
    std::string m_applicationId;
    std::string m_defaultInstallationId;
    std::string m_currentInstallationId;
};

typedef std::vector<std::unique_ptr<ProjectApp>> ProjectAppList;

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Environment
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Project : public NonCopyable {
public:

    static const std::string F_ID;
    static const std::string F_NAME;
    static const std::string F_APPS;

    Project();

    virtual ~Project();

    const std::string &name() const;

    const ProjectAppList &apps() const;

    friend void from_json(const nlohmann::json &json, Project &item);

    friend void to_json(nlohmann::json &j, const Project &item);

    friend std::ostream &operator<<(std::ostream &stream, const Project &environment);

private:
    std::string m_id;
    std::string m_name;
    ProjectAppList m_projectApps;
};

typedef std::vector<std::unique_ptr<Project>> ProjectList;

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Environments
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Environments : public NonCopyable {
public:


    static const std::string F_APPLICATIONS;
    static const std::string F_SCRIPTS;
    static const std::string F_PROJECTS;

    Environments();

    virtual ~Environments();

    ApplicationList & applications();

    Application *findApplication(const std::string &applicationId) const;

    ScriptList & scripts();

    ProjectList &projects();

    void load(const std::string & filename);

    std::vector<std::string> executeScripts(const VariableDictionary &variables);

    friend void from_json(const nlohmann::json &json, Environments &item);

    friend void to_json(nlohmann::json &j, const Environments &item);

    friend std::ostream &operator<<(std::ostream &stream, const Environments &environments);

private:
    ApplicationList m_applications;
    ScriptList m_scripts;
    ProjectList m_projects;
};


}
}
