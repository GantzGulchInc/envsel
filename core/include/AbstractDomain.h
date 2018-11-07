#pragma once

#include "NonCopyable.h"

#include <nlohmann/json.hpp>

#include <string>

namespace gg {
namespace envsel {


/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Application
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class AbstractDomain : public NonCopyable {
public:

    static const std::string F_ID;

    AbstractDomain();

    virtual ~AbstractDomain();

    const std::string & id() const;

    void id(const std::string & id);

    friend void from_json(const nlohmann::json & json, AbstractDomain & item);

    friend void to_json(nlohmann::json & j, const AbstractDomain & item);


private:
    std::string m_id;
};


}
}
