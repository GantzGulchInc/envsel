#include "App.h"
#include "ArgumentParser.h"
#include "AppFrame.h"

#include <string>

namespace gg {
namespace envsel {

App::App() :
        m_command{ Command::NONE } {

}

App::~App() {
}

bool App::OnInit() {

    ArgumentParser argParser { "Environment Selector" };

    m_command = argParser.parse(argc, argv);

    switch (m_command) {
    case Command::SELECT:
        runSelect();
        break;
    case Command::EDIT:
        runEdit();
        break;
    case Command::CHECK:
        runCheck();
        break;
    default:
        // Uh-oh, bad things are afoot.
        break;
    }

    return true;

}

bool App::runSelect() {

    AppFrame * frame = new AppFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

bool App::runEdit() {

    AppFrame * frame = new AppFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

bool App::runCheck() {

    AppFrame * frame = new AppFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));
    frame->Show();
    return true;
}

int App::OnRun() {

    if( m_command != Command::NONE ){
        return wxApp::OnRun();
    }

    return 1;
}

} /* namespace envsel */
} /* namespace gg */
