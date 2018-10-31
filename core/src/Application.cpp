#include "Application.h"
#include "IO.h"
#include "ToString.h"
#include "JsonHelper.h"

#include "easylogging++.h"

#include <iostream>
#include <regex>

using nlohmann::json;

namespace gg {
namespace envsel {

static const char *TAG = "Domain";


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Application
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string Application::F_ID{"id"};
const std::string Application::F_NAME{"name"};
const std::string Application::F_INSTALLATIONS{"installations"};

Application::Application() :
        m_id{""}, m_name{""} {

    CLOG(TRACE, TAG) << "Called";
}

Application::~Application() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string &Application::id() const {
    return m_id;
}

const std::string &Application::name() const {
    return m_name;
}

const ApplicationInstallationList &Application::installations() const {
    return m_installations;
}


ApplicationInstallation * Application::findInstallation(const std::string & id){

    for(auto & appInst : m_installations ) {

        if( appInst->id() == id ) {
            return appInst.get();
        }

    }

    return nullptr;

}

void from_json(const nlohmann::json &json, Application &item) {

    json.at(Application::F_ID).get_to(item.m_id);
    json.at(Application::F_NAME).get_to(item.m_name);

    JsonHelper::from_json(json.at(Application::F_INSTALLATIONS), item.m_installations);
}

void to_json(nlohmann::json &j, const Application &item) {

    j = {
            {Application::F_ID,            item.m_id},
            {Application::F_NAME,          item.m_name},
            {Application::F_INSTALLATIONS, JsonHelper::to_json(item.m_installations)}
    };

}

std::ostream &operator<<(std::ostream &stream, const Application &application) {

    ToString(stream, "Application") //
            .field("m_id", application.m_id) //
            .field("m_name", application.m_name) //
            .field("m_installations", application.m_installations); //

    return stream;
}



}
}
