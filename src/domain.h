/*
 * domain.h
 *
 *  Created on: Oct 14, 2018
 *      Author: gantzm
 */

#pragma once

#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <memory>

namespace gg {
namespace envsel {


/**
 * ScriptVariable
 */
class ScriptVariable {
public:
    ScriptVariable();
    virtual ~ScriptVariable();

private:
    std::string m_name;
    std::string m_value;

};

/**
 * ApplicationInstallation
 */
class ApplicationInstallation {
public:
    ApplicationInstallation();
    virtual ~ApplicationInstallation();

private:
    std::string m_id;
    std::string m_name;
    std::vector<std::unique_ptr<ScriptVariable>> m_variables;

};

/**
 * Application
 */
class Application {
public:
    Application();
    virtual ~Application();

private:
    std::string m_id;
    std::string m_name;
    std::vector<std::unique_ptr<ApplicationInstallation>> m_installations;
};

/**
 * ScriptOperation
 */
class ScriptOperation {
public:
    ScriptOperation();
    virtual ~ScriptOperation();

private:
    std::string m_operation;
    std::vector<std::string> m_arguments;
};

/**
 * Script
 */
class Script {
public:
    Script();
    virtual ~Script();

private:
    std::string m_id;
    std::string m_name;
    std::string m_ifSet;
    std::vector<std::unique_ptr<ScriptOperation>> m_operations;
};

/**
 * EnvironmentApp
 */
class EnvironmentApp {
public:
    EnvironmentApp();
    virtual ~EnvironmentApp();

private:
    std::string m_applicationId;
    std::string m_applicationInstallationId;
};

/**
 * Environment
 */
class Environment {
public:
    Environment();
    virtual ~Environment();

    friend void operator<<(Environment & environment, const nlohmann::json & jsonValue);

private:
    std::string m_id;
    std::string m_name;
    std::vector<std::unique_ptr<EnvironmentApp>> m_environmentApps;
};

/**
 * Something
 */
class Environments {
public:
    Environments();
    virtual ~Environments();

    friend void operator<<(Environments & environments, const nlohmann::json & jsonValue);

private:
    std::vector<std::unique_ptr<Application>> m_applications;
    std::vector<std::unique_ptr<Script>> m_scripts;
    std::vector<std::unique_ptr<Environment>> m_environments;
};


}
}
