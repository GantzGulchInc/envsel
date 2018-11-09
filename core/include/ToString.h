#pragma once

#include "IO.h"

#include <string>
#include <iostream>
#include <vector>

namespace gg {
namespace envsel {

class ToString {

public:
    ToString(std::ostream & stream, const std::string & className) : m_stream{stream}, fieldCount{0} {
        m_stream << className << "[";
    }


    ~ToString() {
        m_stream << "]";
    }

    template<class T>
    ToString & field(const std::string & fieldName, const T & value) {

        if (fieldCount > 0) {
            m_stream << ",";
        }

        m_stream << fieldName << "=" << value;

        fieldCount += 1;

        return *this;
    }

    template<class T>
    ToString & field(const std::string & fieldName, const std::vector<T> & value) {

        if (fieldCount > 0) {
            m_stream << ",";
        }

        m_stream << fieldName << "=[" << value << "]";

        fieldCount += 1;

        return *this;
    }

private:
    std::ostream & m_stream;
    std::uint16_t fieldCount;
};


}
}