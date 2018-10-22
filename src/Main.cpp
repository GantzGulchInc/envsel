
#include <easylogging++.h>

#include "App.h"
#include "EnvSelConfig.h"


INITIALIZE_EASYLOGGINGPP

wxIMPLEMENT_APP_NO_MAIN(gg::envsel::App);
wxIMPLEMENT_WX_THEME_SUPPORT

int main(int argc, char *argv[])  {

    std::cout << "EnvSel: " << EnvSel_VERSION_MAJOR << "." << EnvSel_VERSION_MINOR << "." << EnvSel_VERSION_BUGFIX << std::endl;

    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.setGlobally(el::ConfigurationType::Format, "%datetime [%levshort] %fbase:%line %func: %msg");
    defaultConf.setGlobally(el::ConfigurationType::Filename, "/tmp/envsel.log");
    defaultConf.set(el::Level::Trace,el::ConfigurationType::Enabled, "false");


    el::Loggers::setDefaultConfigurations(defaultConf, true);

    el::Loggers::getLogger("Domain");
    el::Loggers::getLogger("App");
    el::Loggers::getLogger("View");
    el::Loggers::getLogger("IO");

    wxEntryStart( argc, argv );
    
    wxTheApp->CallOnInit();

    return wxTheApp->OnRun();
}

