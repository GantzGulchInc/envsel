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
        m_model(Model::instance()) {

}

App::~App() {
}

bool App::OnInit() {

    try {

        SelectFunc selFunc = std::bind(&App::runSelect, this);
        EditFunc editFunc = std::bind(&App::runEdit, this);
        CheckFunc checkFunc = std::bind(&App::runCheck, this);

        m_argumentsParser = new ArgumentParser{m_model.m_args, "Environment Selector", argc, argv, selFunc, editFunc, checkFunc};

        m_argumentsParser->parse();

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return true;

}

bool App::runSelect() {

    m_model.m_environments.load(m_model.m_args.inputFilename());

    SelectFrame *frame = new SelectFrame(m_model, "Select", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

bool App::runEdit() {

    m_model.m_environments.load(m_model.m_args.inputFilename());

    SelectFrame *frame = new SelectFrame(m_model, "Edit", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

bool App::runCheck() {

    m_model.m_environments.load(m_model.m_args.inputFilename());

    SelectFrame *frame = new SelectFrame(m_model, "Check", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

int App::OnRun() {

    if (m_model.m_args.wasParsed()) {

        wxApp::OnRun();

        CLOG(TRACE, TAG) << "Exiting: " << m_model.m_exitCode;

        return m_model.m_exitCode;
    }

    return ExitReason::EXIT_ERROR;
}

} /* namespace envsel */
} /* namespace gg */
