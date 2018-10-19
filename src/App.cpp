#include "App.h"
#include "ArgumentParser.h"
#include "SelectFrame.h"
#include "Domain.h"
#include "Model.h"
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
        m_parsedArgs{false}, m_model(Model::instance()) {

}

App::~App() {
}

bool App::OnInit() {

    try {

        SelectFunc selFunc = std::bind(&App::runSelect, this, std::placeholders::_1);
        EditFunc editFunc = std::bind(&App::runEdit, this, std::placeholders::_1);
        CheckFunc checkFunc = std::bind(&App::runCheck, this, std::placeholders::_1);

        m_argumentsParser = new ArgumentParser{m_model.m_args, "Environment Selector", argc, argv, selFunc, editFunc, checkFunc};

        m_argumentsParser->parse();

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return true;

}

bool App::runSelect(const Arguments & args) {

    m_model.m_environments.load(args.inputFilename());

    CLOG(TRACE,TAG) << "runSelect: " << args.outputFilename();

    m_parsedArgs = true;

    SelectFrame *frame = new SelectFrame(m_model, "Select", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

bool App::runEdit(const Arguments & args) {

    m_model.m_environments.load(args.inputFilename());

    m_parsedArgs = true;

    SelectFrame *frame = new SelectFrame(m_model, "Edit", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

bool App::runCheck(const Arguments & args) {

    m_model.m_environments.load(args.inputFilename());

    m_parsedArgs = true;

    SelectFrame *frame = new SelectFrame(m_model, "Check", wxPoint(50, 50), wxSize(450, 340));
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
