
#include "EnvSelLogging.h"

#include <easylogging++.h>

namespace gg {
namespace envsel {

void initializeLogging(const std::string &filename, bool enableConsoleLogging) {

    el::Configurations defaultConf;
    defaultConf.setToDefault();

    defaultConf.setGlobally(el::ConfigurationType::Format, "%datetime [%levshort] %fbase:%line %func: %msg");

    if( filename.length() > 0 ){
        defaultConf.setGlobally(el::ConfigurationType::Filename, filename);
    }

    if( enableConsoleLogging ) {
        defaultConf.setGlobally(el::ConfigurationType::ToStandardOutput, "true");
    }else{
        defaultConf.setGlobally(el::ConfigurationType::ToStandardOutput, "false");
    }

    el::Loggers::setDefaultConfigurations(defaultConf, true);

    el::Loggers::getLogger("Domain");
    el::Loggers::getLogger("App");
    el::Loggers::getLogger("View");
    el::Loggers::getLogger("Edit");
    el::Loggers::getLogger("IO");

}

}
}