//
// Created by gantzm on 10/19/18.
//

#pragma once

#include "Domain.h"
#include "ArgumentParser.h"

#include "NonCopyable.h"


namespace gg {
namespace envsel {


class Model : public NonCopyable {

public:

    static Model & instance();

    static const int EXIT_OK = 0;
    static const int EXIT_CANCEL = 1;
    static const int EXIT_ERROR = 2;

    Arguments m_args;

    Environments m_environments;

    int m_exitCode;

private:

    Model();
};

}
}


