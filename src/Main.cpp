
#include <easylogging++.h>

#include "App.h"

INITIALIZE_EASYLOGGINGPP;

wxIMPLEMENT_APP_NO_MAIN(gg::envsel::App);
wxIMPLEMENT_WX_THEME_SUPPORT;

int main(int argc, char *argv[])  {

    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.setGlobally(el::ConfigurationType::Format, "%datetime [%levshort] %fbase:%line %func: %msg");

    el::Loggers::setDefaultConfigurations(defaultConf, true);

    el::Loggers::getLogger("Domain");
    el::Loggers::getLogger("App");
    el::Loggers::getLogger("View");
    el::Loggers::getLogger("IO");

    wxEntryStart( argc, argv );
    
    wxTheApp->CallOnInit();

    return wxTheApp->OnRun();
}

