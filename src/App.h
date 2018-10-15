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
    bool m_parsedArgs;

    bool runSelect(const std::string & filename, const std::string & output);
    bool runEdit(const std::string & filename);
    bool runCheck(const std::string & filename);
};

} /* namespace envsel */
} /* namespace gg */

