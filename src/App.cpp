#include "App.h"
#include "ArgumentParser.h"
#include "SelectFrame.h"
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

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// App
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

App::App() :
        m_parsedArgs{false} {

}

App::~App() {
}

bool App::OnInit() {

    try {

        SelectFunc selFunc = std::bind(&App::runSelect, this, std::placeholders::_1);
        EditFunc editFunc = std::bind(&App::runEdit, this, std::placeholders::_1);
        CheckFunc checkFunc = std::bind(&App::runCheck, this, std::placeholders::_1);

        m_argumentsParser = new ArgumentParser{"Environment Selector", argc, argv, selFunc, editFunc, checkFunc};

        m_argumentsParser->parse();

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return true;

}


void App::loadEnvironments(const std::string &filename) {

    m_envs.load(filename);

    nlohmann::json outputJson = m_envs;

    CLOG(TRACE, TAG) << "Output Json: " << std::endl << outputJson.dump(4);

}

bool App::runSelect(const Arguments & args) {

    loadEnvironments(args.inputFilename());

    CLOG(TRACE,TAG) << "runSelect: " << args.outputFilename();

    m_parsedArgs = true;

    SelectFrame *frame = new SelectFrame(args, m_envs, "Select", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

bool App::runEdit(const Arguments & args) {

    loadEnvironments(args.inputFilename());

    m_parsedArgs = true;

    SelectFrame *frame = new SelectFrame(args, m_envs, "Edit", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

bool App::runCheck(const Arguments & args) {

    loadEnvironments(args.inputFilename());

    m_parsedArgs = true;

    SelectFrame *frame = new SelectFrame(args, m_envs, "Check", wxPoint(50, 50), wxSize(450, 340));
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
