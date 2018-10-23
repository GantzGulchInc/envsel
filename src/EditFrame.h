//
// Created by gantzm on 10/23/18.
//

#pragma once

#include <wx/wx.h>

#include "Model.h"

namespace gg {
namespace envsel {

class EditFrame : public wxFrame {
public:
    EditFrame(Model & model, const wxString & title, const wxPoint &pos, const wxSize &size);

    virtual ~EditFrame();

private:
    Model & m_model;

    wxPanel *m_panel;
};

}
}


/*
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
 */