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
    bool m_parsedArgs;

    Model & m_model;

    ArgumentParser * m_argumentsParser;

    bool runSelect(const Arguments & args);

    bool runEdit(const Arguments & args);

    bool runCheck(const Arguments & args);
};

} /* namespace envsel */
} /* namespace gg */

