#include "App.h"
#include "ArgumentParser.h"
#include "AppFrame.h"
#include "domain.h"

#include <nlohmann/json.hpp>

#include <string>
#include <iostream>
#include <fstream>

namespace gg {
namespace envsel {

App::App() :
        m_parsedArgs { false } {

}

App::~App() {
}

bool App::OnInit() {

    SelectFunc selFunc = std::bind(&App::runSelect, this, std::placeholders::_1, std::placeholders::_2);
    EditFunc editFunc = std::bind(&App::runEdit, this, std::placeholders::_1);
    CheckFunc checkFunc = std::bind(&App::runCheck, this, std::placeholders::_1);

    ArgumentParser argParser { "Environment Selector", argc, argv, selFunc, editFunc, checkFunc };

    argParser.parse();

    return true;

}

bool App::runSelect(const std::string & filename, const std::string & output) {

    std::cout << "funSelect: filename: " << filename << std::endl;

    try {
        std::ifstream jsonFile;
        jsonFile.open("environments.json");

        nlohmann::json json;

        std::cout << "Reading file..." << std::endl;

        jsonFile >> json;

        jsonFile.close();

        Environments envs;

        std::cout << "Parsing json..." << std::endl;

        envs << json;

    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }

    m_parsedArgs = true;

    AppFrame * frame = new AppFrame("Select", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

bool App::runEdit(const std::string & filename) {

    m_parsedArgs = true;

    AppFrame * frame = new AppFrame("Edit", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

bool App::runCheck(const std::string & filename) {

    m_parsedArgs = true;

    AppFrame * frame = new AppFrame("Check", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

int App::OnRun() {

    if (m_parsedArgs) {
        return wxApp::OnRun();
    }

    return 1;
}

} /* namespace envsel */
} /* namespace gg */
