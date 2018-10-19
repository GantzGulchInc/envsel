/*
 * AppFrame.h
 *
 *  Created on: Oct 12, 2018
 *      Author: gantzm
 */

#pragma once

#include "Domain.h"
#include "Model.h"
#include "ArgumentParser.h"

#include "SelectionTab.h"

#include <wx/wx.h>

#include <wx/notebook.h>
#include <vector>
#include <utility>

namespace gg {
namespace envsel {

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * SelectFrame
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class SelectFrame : public wxFrame {
public:
    SelectFrame(Model & model, const wxString &title, const wxPoint &pos, const wxSize &size);

    virtual ~SelectFrame();

private:
    Model & m_model;

    wxPanel *m_panel;
    wxNotebook *m_notebook;
    wxSizer *m_notebookSizer;

    std::vector<std::pair<SelectionTab *, Environment &>> m_tabs;

    void OnHello(wxCommandEvent &event);

    void OnExit(wxCommandEvent &event);

    void OnAbout(wxCommandEvent &event);

wxDECLARE_EVENT_TABLE();
};

enum {
    ID_Hello = 1
};


} /* namespace envsel */
} /* namespace gg */

