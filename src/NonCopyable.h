//
// Created by gantzm on 10/16/18.
//

#pragma once

namespace gg {
namespace envsel {

class NonCopyable {
public:

    NonCopyable(){};

    ~NonCopyable(){};

    // No copy constructor
    NonCopyable(const NonCopyable &) = delete;

    // No move constructor
    NonCopyable(NonCopyable &&) = delete;

    // No copy assignment
    NonCopyable &operator=(const NonCopyable &) = delete;

    // No move assignment
    NonCopyable &operator=(NonCopyable &&) = delete;

};

}
}