
#include <easylogging++.h>

#include "App.h"

INITIALIZE_EASYLOGGINGPP;

wxIMPLEMENT_APP_NO_MAIN(gg::envsel::App);
wxIMPLEMENT_WX_THEME_SUPPORT;

int main(int argc, char *argv[])  {

    el::Loggers::getLogger("Domain");
    el::Loggers::getLogger("App");

    wxEntryStart( argc, argv );
    wxTheApp->CallOnInit();
    wxTheApp->OnRun();

    return 0;
}

// wxIMPLEMENT_APP(gg::envsel::App);

