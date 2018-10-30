//
// Created by gantzm on 10/24/18.
//

#pragma once

#include <wx/wx.h>

#include "Domain.h"

namespace gg {
namespace envsel {

class EditApplicationPanel : public wxPanel {

public:

    EditApplicationPanel(wxWindow * parent, Application * application);

    ~EditApplicationPanel();

private:
    Application * m_application;
    wxSizer * m_panelSizer;
    wxFlexGridSizer * m_flexGridSizer;

};

}
}

