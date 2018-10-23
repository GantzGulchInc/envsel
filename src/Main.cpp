
#include <easylogging++.h>

#include "App.h"
#include "Model.h"

#include "EnvSelConfig.h"


INITIALIZE_EASYLOGGINGPP

wxIMPLEMENT_APP_NO_MAIN(gg::envsel::App);

wxIMPLEMENT_WX_THEME_SUPPORT

static void parseArguments(int argc, char *argv[]) {

    gg::envsel::Arguments & args{gg::envsel::Arguments::instance()};

    gg::envsel::ArgumentParser argsParser{args, "Environment Selector", argc, argv};

    if (!argsParser.parse()) {
        exit(gg::envsel::ExitReason::EXIT_ERROR);
    }

}

static void initLogging() {

    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.setGlobally(el::ConfigurationType::Format, "%datetime [%levshort] %fbase:%line %func: %msg");
    defaultConf.setGlobally(el::ConfigurationType::Filename, "/tmp/envsel.log");
    defaultConf.set(el::Level::Trace, el::ConfigurationType::Enabled, "false");


    el::Loggers::setDefaultConfigurations(defaultConf, true);

    el::Loggers::getLogger("Domain");
    el::Loggers::getLogger("App");
    el::Loggers::getLogger("View");
    el::Loggers::getLogger("IO");

}

static int runApp(int argc, char *argv[]) {

    wxEntryStart(argc, argv);

    wxTheApp->CallOnInit();

    return wxTheApp->OnRun();

}

int main(int argc, char *argv[]) {

    std::cout << "EnvSel: " << EnvSel_VERSION_MAJOR << "." << EnvSel_VERSION_MINOR << "." << EnvSel_VERSION_BUGFIX << std::endl;

    parseArguments(argc, argv);

    initLogging();

    return runApp(argc, argv);
}

