//
// Created by gantzm on 10/19/18.
//

#pragma once

#include "Domain.h"
#include "ArgumentParser.h"

#include "NonCopyable.h"


namespace gg {
namespace envsel {


enum ExitReason {
    EXIT_OK = 0,
    EXIT_CANCEL = 1,
    EXIT_ERROR = 2
};

class Model : public NonCopyable {

public:

    static Model & instance();

    Environments m_environments;

    ExitReason m_exitCode;

private:

    Model();
};

}
}


