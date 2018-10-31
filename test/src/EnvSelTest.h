#pragma once

#include "gtest/gtest.h"

namespace gg {
namespace envsel {
namespace test {

class EnvSelTest : public ::testing::Test {

public:

    EnvSelTest();

    virtual ~EnvSelTest();

protected:

    virtual void SetUp();

    virtual void TearDown();
};

}
}
}
