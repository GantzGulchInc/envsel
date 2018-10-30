

#include "App.h"
#include "Model.h"
#include "EnvSelLogging.h"

#include "EnvSelConfig.h"


INITIALIZE_EASYLOGGINGPP

wxIMPLEMENT_APP_NO_MAIN(gg::envsel::App);

wxIMPLEMENT_WX_THEME_SUPPORT

static void parseArguments(int argc, char *argv[]) {

    gg::envsel::Arguments &args{gg::envsel::Arguments::instance()};

    gg::envsel::ArgumentParser argsParser{args, "Project Selector", argc, argv};

    if (!argsParser.parse()) {
        exit(gg::envsel::ExitReason::EXIT_ERROR);
    }

}

static void initLogging() {

    gg::envsel::Arguments &args{gg::envsel::Arguments::instance()};

    gg::envsel::initializeLogging(args.loggingFilename(), false);
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

