/*
 * App.h
 *
 *  Created on: Oct 12, 2018
 *      Author: gantzm
 */

#pragma once

#include "ArgumentParser.h"
#include "Domain.h"
#include "Model.h"

#include <wx/wx.h>

namespace gg {
namespace envsel {

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * App
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class App : public wxApp {
public:
    App();

    virtual ~App();

    virtual bool OnInit();

    virtual int OnRun();

private:

    Arguments &m_arguments;

    Model &m_model;

    bool runSelect();

    bool runEdit();

    bool runCheck();
};

} /* namespace envsel */
} /* namespace gg */

