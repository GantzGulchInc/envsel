#include "gtest/gtest.h"

#include "Domain.h"
#include "EnvSelLogging.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {

    gg::envsel::initializeLogging("/tmp/envseltest.log", false);

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}