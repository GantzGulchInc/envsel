#include "gtest/gtest.h"

#include "Domain.h"
#include "EnvSelLogging.h"

class DomainTest : public ::testing::Test {

protected:

    DomainTest() {


    }

    ~DomainTest() override {

    }

    void SetUp() override {

    }

    void TearDown() override {

    }


};

TEST_F(DomainTest, ParseJson) {

    EXPECT_EQ(5, 5);

}

TEST_F(DomainTest, FormatJson) {

    EXPECT_EQ(5, 5);

}

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {

    gg::envsel::initializeLogging(false, true);

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}