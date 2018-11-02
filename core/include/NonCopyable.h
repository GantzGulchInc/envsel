#pragma once

namespace gg {
namespace envsel {

class NonCopyable {
public:

    NonCopyable() {};

    virtual ~NonCopyable() {};

    // No copy constructor
    NonCopyable(const NonCopyable &) = delete;

    // No move constructor
    NonCopyable(NonCopyable &&) = delete;

    // No copy assignment
    NonCopyable & operator=(const NonCopyable &) = delete;

    // No move assignment
    NonCopyable & operator=(NonCopyable &&) = delete;

};

}
}
