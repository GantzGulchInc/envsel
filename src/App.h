/*
 * App.h
 *
 *  Created on: Oct 12, 2018
 *      Author: gantzm
 */

#pragma once

#include "ArgumentParser.h"

#include <wx/wx.h>

namespace gg {
namespace envsel {

class App: public wxApp {
public:
    App();
    virtual ~App();
    virtual bool OnInit();
    virtual int OnRun();

private:
    Command m_command;

    bool runSelect();
    bool runEdit();
    bool runCheck();
};

} /* namespace envsel */
} /* namespace gg */

