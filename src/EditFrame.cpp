//
// Created by gantzm on 10/23/18.
//

#include "EditFrame.h"

#include <wx/wx.h>
#include <wx/treectrl.h>

namespace gg {
namespace envsel {

static wxTreeCtrl *createTree(wxWindow *parent, gg::envsel::Model &m_model) {

    wxTreeCtrl *treeCtrl = new wxTreeCtrl(parent, wxID_ANY);

    wxTreeItemId rootId = treeCtrl->AddRoot("Root");

    wxTreeItemId appsId = treeCtrl->AppendItem(rootId, "Applications");

    for (auto &app : m_model.m_environments.applications()) {

        TreeClientPtr<Application> *p = new TreeClientPtr<Application>{app.get()};

        wxTreeItemId appId = treeCtrl->AppendItem(appsId, app->name(), -1, -1, p);

    }

    wxTreeItemId scriptsId = treeCtrl->AppendItem(rootId, "Scripts");

    for (auto &script : m_model.m_environments.scripts()) {

        TreeClientPtr<Script> *p = new TreeClientPtr<Script>{script.get()};

        wxTreeItemId scriptId = treeCtrl->AppendItem(scriptsId, script->name(), -1, -1, p);
    }

    wxTreeItemId projectsId = treeCtrl->AppendItem(rootId, "Projects");

    for (auto &project : m_model.m_environments.projects()) {

        TreeClientPtr<Project> *p = new TreeClientPtr<Project>{project.get()};

        wxTreeItemId envId = treeCtrl->AppendItem(projectsId, project->name(), -1, -1, p);

        for (auto &projectApp : project->apps()) {

            TreeClientPtr<ProjectApp> *p2 = new TreeClientPtr<ProjectApp>(projectApp.get());

            Application *app = m_model.m_environments.findApplication(projectApp->applicationId());

            if (app) {

                ApplicationInstallation *applicationInstallation = app->findInstallation(projectApp->defaultInstallationId());

                if (applicationInstallation) {

                    wxTreeItemId projAppId = treeCtrl->AppendItem(envId, app->name() + " / " + applicationInstallation->name(), -1, -1, p2);

                }
            }
        }
    }

    return treeCtrl;

}

wxPanel *createPanel(wxWindow *parent) {

    wxPanel *p = new wxPanel(parent, wxID_ANY);

    return p;
}

EditFrame::EditFrame(gg::envsel::Model &model, const wxString &title, const wxPoint &pos, const wxSize &size) :
        wxFrame(NULL, wxID_ANY, title, pos, size), m_model(model) {

    // m_panel = new wxPanel(this);

    m_panelSizer = new wxBoxSizer(wxVERTICAL);

    m_splitter = new wxSplitterWindow(this, wxID_ANY);
    m_splitter->SetSashGravity(0.5);
    m_splitter->SetMinimumPaneSize(50);
    m_panelSizer->Add(m_splitter, 1, wxEXPAND, 0);


    wxPanel *leftPanel = new wxPanel(m_splitter, wxID_ANY);
    wxSizer *leftPanelSizer = new wxBoxSizer(wxVERTICAL);
    wxTreeCtrl *treeCtrl = createTree(leftPanel, m_model);
    treeCtrl->ExpandAll();
    leftPanelSizer->Add(treeCtrl, 1, wxEXPAND, 0);
    leftPanel->SetSizer(leftPanelSizer);

    wxPanel *rightPanel = new wxPanel(m_splitter, wxID_ANY);
    wxSizer *rightPanelSizer = new wxBoxSizer(wxVERTICAL);
    wxTextCtrl *text = new wxTextCtrl(rightPanel, wxID_ANY);
    rightPanelSizer->Add(text, 1, wxEXPAND, 0);
    rightPanel->SetSizer(rightPanelSizer);

    m_splitter->SplitVertically(leftPanel, rightPanel);

    this->SetSizer(m_panelSizer);
    m_panelSizer->SetSizeHints(this);

    this->SetSize(600, 400);
}

EditFrame::~EditFrame() {

}


}
}



