/*
 * AppFrame.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: gantzm
 */

#include "SelectionTab.h"

#include "SelectFrame.h"

namespace gg {
namespace envsel {

wxBEGIN_EVENT_TABLE(SelectFrame, wxFrame)
                EVT_MENU(ID_Hello, SelectFrame::OnHello)
                EVT_MENU(wxID_EXIT, SelectFrame::OnExit)
                EVT_BUTTON(wxID_EXIT, SelectFrame::OnExit)
                EVT_MENU(wxID_ABOUT, SelectFrame::OnAbout)
wxEND_EVENT_TABLE()

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// SelectFrame
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

SelectFrame::SelectFrame(const Arguments & args, Environments &environments, const wxString &title, const wxPoint &pos, const wxSize &size) :
        wxFrame(NULL, wxID_ANY, title, pos, size), m_args(args), m_environments(environments) {

    m_panel = new wxPanel(this);

    m_notebook = new wxNotebook(m_panel, wxID_ANY);

    bool first{true};

    for (auto &p : environments.environments()) {

        SelectionTab *tab = new SelectionTab(m_notebook, wxID_ANY, "Tab1", m_environments, *p);

        m_tabs.push_back(std::pair<SelectionTab *, Environment &>(tab, *p));

        m_notebook->AddPage(tab, p->name(), first);

        first = false;
    }

    m_notebookSizer = new wxBoxSizer(wxHORIZONTAL);
    m_notebookSizer->Add(m_notebook, 1, wxEXPAND);

    m_panel->SetSizer(m_notebookSizer);
}

/*
 wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
            const wxString& name = wxPanelNameStr)
 */

//    wxMenu *menuFile = new wxMenu;
//    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
//    menuFile->AppendSeparator();
//    menuFile->Append(wxID_EXIT);
//
//    wxMenu *menuHelp = new wxMenu;
//    menuHelp->Append(wxID_ABOUT);
//
//    wxMenuBar *menuBar = new wxMenuBar;
//
//    menuBar->Append(menuFile, "&File");
//    menuBar->Append(menuHelp, "&Help");
//
//    SetMenuBar(menuBar);
//
//    CreateStatusBar();
//    SetStatusText("Welcome!");
//}

SelectFrame::~SelectFrame() {
}

void SelectFrame::OnExit(wxCommandEvent &event) {
    Close(true);
}

void SelectFrame::OnAbout(wxCommandEvent &event) {
    wxMessageBox("This is a wxWidgets' Hello world sample", "About Hello World", wxOK | wxICON_INFORMATION);
}

void SelectFrame::OnHello(wxCommandEvent &event) {
    wxLogMessage("Hello world from wxWidgets!");
}

} /* namespace envsel */
} /* namespace gg */
