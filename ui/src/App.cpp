#include "App.h"
#include "ArgumentParser.h"
#include "SelectFrame.h"
#include "EditFrame.h"
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

static const char *TAG = "App";

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// App
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

App::App() :
        m_arguments(Arguments::instance()), m_model(Model::instance()) {

}

App::~App() {
}

bool App::OnInit() {

    switch (m_arguments.command()) {
        case SelectedCommand::SELECT:
            runSelect();
            break;
        case SelectedCommand::EDIT:
            runEdit();
            break;
        case SelectedCommand::CHECK:
            runCheck();
            break;
        default:
            return false;
    }

    return true;

}

bool App::runSelect() {

    m_model.m_environments.load(m_arguments.inputFilename());

    SelectFrame *frame = new SelectFrame(m_model, "Select", wxPoint(50, 50), wxSize(800, 600));
    frame->Show();
    return true;
}

bool App::runEdit() {

    m_model.m_environments.load(m_arguments.inputFilename());

    EditFrame *frame = new EditFrame(m_model, "Edit", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

bool App::runCheck() {

    m_model.m_environments.load(m_arguments.inputFilename());

    SelectFrame *frame = new SelectFrame(m_model, "Check", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

int App::OnRun() {


    wxApp::OnRun();

    CLOG(DEBUG, TAG) << "Exiting: " << m_model.m_exitCode;

    return m_model.m_exitCode;

}

} /* namespace envsel */
} /* namespace gg */
