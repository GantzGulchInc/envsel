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


/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ScriptVariable
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ScriptVariable : public NonCopyable {
public:

    ScriptVariable();
    virtual ~ScriptVariable();

    friend void operator<<(ScriptVariable &scriptVariable, const nlohmann::json &jsonValue);
    friend std::ostream &operator<<(std::ostream &stream, const ScriptVariable &scriptVariable);

private:
    std::string m_name;
    std::string m_value;

};

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ApplicationInstallation
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ApplicationInstallation : public NonCopyable {
public:

    ApplicationInstallation();
    virtual ~ApplicationInstallation();

    friend void operator<<(ApplicationInstallation &applicationInstallation, const nlohmann::json &jsonValue);
    friend std::ostream &operator<<(std::ostream &stream, const ApplicationInstallation &applicationInstallation);

private:
    std::string m_id;
    std::string m_name;
    std::vector<std::unique_ptr<ScriptVariable>> m_variables;

};

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Application
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Application : public NonCopyable {
public:

    Application();
    virtual ~Application();

    friend void operator<<(Application &application, const nlohmann::json &jsonValue);
    friend std::ostream &operator<<(std::ostream &stream, const Application &application);

private:
    std::string m_id;
    std::string m_name;
    std::vector<std::unique_ptr<ApplicationInstallation>> m_installations;
};

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ScriptOperation
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class ScriptOperation : public NonCopyable {
public:

    ScriptOperation();
    virtual ~ScriptOperation();

    friend void operator<<(ScriptOperation &scriptOperation, const nlohmann::json &jsonValue);
    friend std::ostream &operator<<(std::ostream &stream, const ScriptOperation &scriptOperation);

private:
    std::string m_operation;
    std::vector<std::string> m_arguments;
};

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Script
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Script : public NonCopyable {
public:

    Script();
    virtual ~Script();

    friend void operator<<(Script &script, const nlohmann::json &jsonValue);
    friend std::ostream &operator<<(std::ostream &stream, const Script &script);

private:
    std::string m_id;
    std::string m_name;
    std::string m_ifSet;
    std::vector<std::unique_ptr<ScriptOperation>> m_operations;
};

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * EnvironmentApp
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class EnvironmentApp : public NonCopyable {
public:

    EnvironmentApp();
    virtual ~EnvironmentApp();

    friend void operator<<(EnvironmentApp &environmentApp, const nlohmann::json &jsonValue);
    friend std::ostream &operator<<(std::ostream &stream, const EnvironmentApp &environmentApp);

private:
    std::string m_applicationId;
    std::string m_applicationInstallationId;
};

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Environment
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Environment : public NonCopyable {
public:

    Environment();
    virtual ~Environment();

    std::string name() const;

    friend void operator<<(Environment &environment, const nlohmann::json &jsonValue);
    friend std::ostream &operator<<(std::ostream &stream, const Environment &environment);

private:
    std::string m_id;
    std::string m_name;
    std::vector<std::unique_ptr<EnvironmentApp>> m_environmentApps;
};

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Environments
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class Environments : public NonCopyable {
public:

    Environments();
    virtual ~Environments();

    std::string filename() const;
    Environments &filename(const std::string &filename);


    friend void operator<<(Environments &environments, const nlohmann::json &jsonValue);
    friend std::ostream &operator<<(std::ostream &stream, const Environments &environments);

private:
    std::string m_filename;
    std::vector<std::unique_ptr<Application>> m_applications;
    std::vector<std::unique_ptr<Script>> m_scripts;
    std::vector<std::unique_ptr<Environment>> m_environments;
};


}
}
