
#include <string>
#include <iostream>
#include <vector>

#pragma once

namespace gg {
namespace envsel {


class ToString {

public:
    ToString(std::ostream &stream, const std::string &className);

    virtual ~ToString();

    template<class T>
    ToString &field(const std::string &fieldName, const T &value) {

        if (fieldCount > 0) {
            m_stream << ",";
        }

        m_stream << fieldName << "=" << value;

        fieldCount += 1;
    }

    template<class T>
    ToString &field(const std::string &fieldName, const std::vector<T> &value) {

        if (fieldCount > 0) {
            m_stream << ",";
        }

        m_stream << fieldName << "=[" << value << "]";

        fieldCount += 1;
    }

private:
    std::ostream &m_stream;
    std::uint16_t fieldCount;
};


}
}