//
// Created by gantzm on 10/19/18.
//

#include "Model.h"

namespace gg {
namespace envsel {

Model::Model() : m_exitCode{ ExitReason::EXIT_CANCEL } {

}

Model &Model::instance() {

    static Model instance;

    return instance;
}

}
}
