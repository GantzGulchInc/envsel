#include "SelectFrame.h"
#include "SelectionTab.h"
#include "Directives.h"

#include "easylogging++.h"

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

SelectFrame::SelectFrame(Model &model, const wxString &title, const wxPoint &pos, const wxSize &size) :
        wxFrame(NULL, wxID_ANY, title, pos, size), m_model(model) {

    m_panel = new wxPanel(this);

    m_notebook = new wxNotebook(m_panel, wxID_ANY);

    bool first{true};

    for (auto &p : m_model.m_environments.projects()) {

        SelectionTab *tab = new SelectionTab(m_model, m_notebook, wxID_ANY, "Tab1", *p);

        m_tabs.push_back(std::pair<SelectionTab *, Project &>(tab, *p));

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

void SelectFrame::OnExit(wxCommandEvent &UNUSED(event)) {

    LOG(TRACE) << "exiting...: " << m_model.m_exitCode;

    m_model.m_exitCode = ExitReason::EXIT_CANCEL;

    Close(true);
}

void SelectFrame::OnAbout(wxCommandEvent &UNUSED(event)) {
    wxMessageBox("This is a wxWidgets' Hello world sample", "About Hello World", wxOK | wxICON_INFORMATION);
}

void SelectFrame::OnHello(wxCommandEvent &UNUSED(event)) {
    wxLogMessage("Hello world from wxWidgets!");
}

} /* namespace envsel */
} /* namespace gg */
