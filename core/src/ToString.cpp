#include "ToString.h"

namespace  gg {
namespace envsel {

ToString::ToString(std::ostream &stream, const std::string &className) : m_stream{stream}, fieldCount{0} {

    m_stream << className << "[";
}

ToString::~ToString() {
    m_stream << "]";
}

}
}

