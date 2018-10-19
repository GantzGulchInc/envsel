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

    Arguments m_args;

    Environments m_environments;

private:

    Model();
};

}
}


