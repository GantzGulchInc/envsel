/*
 * AppFrame.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: gantzm
 */

#include "AppFrame.h"

namespace gg {
namespace envsel {

wxBEGIN_EVENT_TABLE(AppFrame, wxFrame)
                EVT_MENU(ID_Hello, AppFrame::OnHello)
                EVT_MENU(wxID_EXIT, AppFrame::OnExit)
                EVT_MENU(wxID_ABOUT, AppFrame::OnAbout)
wxEND_EVENT_TABLE()

AppFrame::AppFrame(const wxString &title, const wxPoint &pos, const wxSize &size) :
        wxFrame(NULL, wxID_ANY, title, pos, size) {

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;

    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome!");
}

AppFrame::~AppFrame() {
}

void AppFrame::OnExit(wxCommandEvent &event) {
    Close(true);
}

void AppFrame::OnAbout(wxCommandEvent &event) {
    wxMessageBox("This is a wxWidgets' Hello world sample", "About Hello World", wxOK | wxICON_INFORMATION);
}

void AppFrame::OnHello(wxCommandEvent &event) {
    wxLogMessage
        ("Hello world from wxWidgets!");
}

} /* namespace envsel */
} /* namespace gg */
