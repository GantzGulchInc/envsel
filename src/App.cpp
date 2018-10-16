#include "App.h"
#include "ArgumentParser.h"
#include "AppFrame.h"
#include "Domain.h"
#include "IO.h"

#include <nlohmann/json.hpp>
#include <easylogging++.h>

#include <string>
#include <iostream>
#include <fstream>

namespace gg {
namespace envsel {

static const char * TAG = "App";

App::App() :
        m_parsedArgs{false} {

}

App::~App() {
}

bool App::OnInit() {

    try {

        SelectFunc selFunc = std::bind(&App::runSelect, this, std::placeholders::_1, std::placeholders::_2);
        EditFunc editFunc = std::bind(&App::runEdit, this, std::placeholders::_1);
        CheckFunc checkFunc = std::bind(&App::runCheck, this, std::placeholders::_1);

        ArgumentParser argParser{"Environment Selector", argc, argv, selFunc, editFunc, checkFunc};

        argParser.parse();
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return true;

}


void App::loadEnvironments(const std::string &filename) {

    CLOG(TRACE, TAG) << "loadEnvironments: filename: " << filename;

    CLOG(TRACE, TAG) << "Reading file...";

    nlohmann::json json = readJsonFile(filename);

    CLOG(TRACE, TAG) << "Parsing json...";

    m_envs << json;

    m_envs.filename(filename);

    CLOG(TRACE, TAG) << "Parsed: " << m_envs;
}

bool App::runSelect(const std::string &filename, const std::string &output) {

    loadEnvironments(filename);

    m_parsedArgs = true;

    AppFrame *frame = new AppFrame("Select", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

bool App::runEdit(const std::string &filename) {

    loadEnvironments(filename);

    m_parsedArgs = true;

    AppFrame *frame = new AppFrame("Edit", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

bool App::runCheck(const std::string &filename) {

    loadEnvironments(filename);

    m_parsedArgs = true;

    AppFrame *frame = new AppFrame("Check", wxPoint(50, 50), wxSize(450, 340));
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
