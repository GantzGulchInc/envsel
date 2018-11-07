#include "AbstractDomain.h"
#include "IO.h"
#include "ToString.h"
#include "JsonHelper.h"

#include "easylogging++.h"

using nlohmann::json;

namespace gg {
namespace envsel {

static const char *TAG = "Domain";


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Script
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const std::string AbstractDomain::F_ID{"id"};

AbstractDomain::AbstractDomain() :
        m_id{""} {

}

AbstractDomain::~AbstractDomain() {

}

const std::string &AbstractDomain::id() const {
    return m_id;
}

void AbstractDomain::id(const std::string & id) {
    m_id = id;
}

void from_json(const nlohmann::json &json, AbstractDomain &item) {

    CLOG(TRACE, TAG) << "from_json";

    item.m_id = json.value(AbstractDomain::F_ID, "");

}

void to_json(nlohmann::json &j, const AbstractDomain &item) {

    CLOG(TRACE, TAG) << "begin: to_json";

    j[AbstractDomain::F_ID] = item.m_id;

    CLOG(TRACE, TAG) << "end: to_json";

}



}
}
