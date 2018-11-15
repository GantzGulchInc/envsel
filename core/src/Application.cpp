#include "Application.h"
#include "IO.h"
#include "ToString.h"
#include "Json.h"

#include "easylogging++.h"

#include <iostream>
#include <regex>
#include <algorithm>

using nlohmann::json;

namespace gg {
namespace envsel {

static const char *TAG = "Domain";


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Application
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string Application::F_NAME{"name"};
const std::string Application::F_INSTALLATIONS{"installations"};

Application::Application() :
    AbstractDomain{}, m_name{""} {

    CLOG(TRACE, TAG) << "Called";
}

Application::~Application() {

    CLOG(TRACE, TAG) << "Called";
}

const std::string &Application::name() const {
    return m_name;
}

const ApplicationInstallationList &Application::installations() const {
    return m_installations;
}


ApplicationInstallation * Application::findInstallation(const std::string & id){

    auto i = std::find_if(std::begin(m_installations), std::end(m_installations), ApplicationInstallationIdPredicate(id) );

    if( i != std::end(m_installations) ) {
        return i->get();
    }

    return nullptr;
}

void from_json(const nlohmann::json &json, Application &item) {

    from_json(json, reinterpret_cast<AbstractDomain&>(item) );

    json.at(Application::F_NAME).get_to(item.m_name);
    json.at(Application::F_INSTALLATIONS).get_to(item.m_installations);
}

void to_json(nlohmann::json &j, const Application &item) {

    j = {
            {Application::F_NAME,          item.m_name},
            {Application::F_INSTALLATIONS, to_json(item.m_installations)}
    };

    to_json(j, reinterpret_cast<const AbstractDomain&>(item) );
}

std::ostream &operator<<(std::ostream &stream, const Application &item) {

    ToString(stream, "Application") //
            .field("m_id", item.id()) //
            .field("m_name", item.m_name) //
            .field("m_installations", item.m_installations); //

    return stream;
}



}
}
