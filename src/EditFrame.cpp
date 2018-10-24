//
// Created by gantzm on 10/23/18.
//

#include "EditFrame.h"

#include <wx/wx.h>
#include <wx/treectrl.h>

namespace gg {
namespace envsel {

static const char *TAG = "Edit";

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// TreeClientPtr
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

TreeClientPtr::TreeClientPtr(TreeClientType type, void *item, RighClickHandler handler)
        : wxTreeItemData(), m_type{type}, m_item{item}, m_handler{ handler } {

}

TreeClientPtr::~TreeClientPtr() {

}

TreeClientType TreeClientPtr::type() {
    return m_type;
}

void *TreeClientPtr::get() {
    return m_item;
}

void TreeClientPtr::dispatch(wxTreeEvent &event) {

    m_handler(event);

}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// EditFrame
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

wxBEGIN_EVENT_TABLE(EditFrame, wxFrame)

                EVT_MENU(ID_APPLICATION_NEW, EditFrame::onApplicationNew)
                EVT_MENU(ID_APPLICATION_DELETE, EditFrame::onApplicationDelete)
                EVT_TREE_ITEM_RIGHT_CLICK(ID_APP_TREE, EditFrame::onTreeMenu)
                EVT_MENU(ID_APPLICATION_INSTALLATION_NEW, EditFrame::onApplicationInstallationNew)
                EVT_MENU(ID_APPLICATION_INSTALLATION_DELETE, EditFrame::onApplicationInstallationDelete)
                EVT_MENU(ID_SCRIPT_NEW, EditFrame::onScriptNew)
                EVT_MENU(ID_SCRIPT_DELETE, EditFrame::onScriptDelete)
                EVT_MENU(ID_SCRIPT_COMMAND_NEW, EditFrame::onScriptCommandNew)
                EVT_MENU(ID_SCRIPT_COMMAND_DELETE, EditFrame::onScriptCommandDelete)
                EVT_MENU(ID_PROJECT_NEW, EditFrame::onProjectNew)
                EVT_MENU(ID_PROJECT_DELETE, EditFrame::onProjectDelete)
                EVT_MENU(ID_PROJECT_APP_NEW, EditFrame::onProjectAppNew)
                EVT_MENU(ID_PROJECT_APP_DELETE, EditFrame::onProjectAppDelete)

                //EVT_TREE_ITEM_MENU(ID_APP_TREE, EditFrame::onTreeMenu)

wxEND_EVENT_TABLE()

void EditFrame::onApplicationNew(wxCommandEvent &event) {
    CLOG(TRACE, TAG) << "Called: " << event.GetId();
}

void EditFrame::onApplicationDelete(wxCommandEvent &event) {
    CLOG(TRACE, TAG) << "Called: " << event.GetId();
}

void EditFrame::onApplicationInstallationNew(wxCommandEvent &event) {
    CLOG(TRACE, TAG) << "Called: " << event.GetId();
}

void EditFrame::onApplicationInstallationDelete(wxCommandEvent &event) {
    CLOG(TRACE, TAG) << "Called: " << event.GetId();
}

void EditFrame::onScriptNew(wxCommandEvent & event) {
    CLOG(TRACE, TAG) << "Called: " << event.GetId();
}

void EditFrame::onScriptDelete(wxCommandEvent & event) {
    CLOG(TRACE, TAG) << "Called: " << event.GetId();
}

void EditFrame::onScriptCommandNew(wxCommandEvent & event) {
    CLOG(TRACE, TAG) << "Called: " << event.GetId();
}

void EditFrame::onScriptCommandDelete(wxCommandEvent & event) {
    CLOG(TRACE, TAG) << "Called: " << event.GetId();
}

void EditFrame::onProjectNew(wxCommandEvent & event) {
    CLOG(TRACE, TAG) << "Called: " << event.GetId();
}

void EditFrame::onProjectDelete(wxCommandEvent & event) {
    CLOG(TRACE, TAG) << "Called: " << event.GetId();
}

void EditFrame::onProjectAppNew(wxCommandEvent & event) {
    CLOG(TRACE, TAG) << "Called: " << event.GetId();
}

void EditFrame::onProjectAppDelete(wxCommandEvent & event) {
    CLOG(TRACE, TAG) << "Called: " << event.GetId();
}


wxTreeItemId EditFrame::createApplicationsNode(wxTreeCtrl *treeCtrl, wxTreeItemId rootId) {

    ApplicationList &appList = m_model.m_environments.applications();

    TreeClientPtr *appListPtr = new TreeClientPtr(TreeClientType::APPLICATIONS, &appList, std::bind(&EditFrame::applicationsPopup, this, std::placeholders::_1) );

    wxTreeItemId appListItemId = treeCtrl->AppendItem(rootId, "Applications", -1, -1, appListPtr);

    for (auto &app : appList) {

        TreeClientPtr *appPtr = new TreeClientPtr{TreeClientType::APPLICATION, app.get(), std::bind(&EditFrame::applicationPopup, this, std::placeholders::_1)};

        wxTreeItemId appItemId = treeCtrl->AppendItem(appListItemId, app->name(), -1, -1, appPtr);

        for (auto &installation : app->installations()) {

            TreeClientPtr *installationPtr = new TreeClientPtr{TreeClientType::APPLICATION_INSTALLATION, installation.get(), std::bind(&EditFrame::applicationInstallationPopup, this, std::placeholders::_1)};

            treeCtrl->AppendItem(appItemId, installation->name(), -1, -1, installationPtr);


        }

    }

    treeCtrl->Expand(appListItemId);

    return appListItemId;

}


wxTreeItemId EditFrame::createScriptsNode(wxTreeCtrl *treeCtrl, wxTreeItemId rootId) {

    ScriptList &scriptList = m_model.m_environments.scripts();

    TreeClientPtr *scriptsPtr = new TreeClientPtr(TreeClientType::SCRIPTS, &scriptList, std::bind(&EditFrame::scriptsPopup, this, std::placeholders::_1));

    wxTreeItemId scriptsId = treeCtrl->AppendItem(rootId, "Scripts", -1, -1, scriptsPtr);

    for (auto &script : scriptList) {

        TreeClientPtr *scriptPtr = new TreeClientPtr{TreeClientType::SCRIPT, script.get(), std::bind(&EditFrame::scriptPopup, this, std::placeholders::_1)};

        wxTreeItemId scriptId = treeCtrl->AppendItem(scriptsId, script->name(), -1, -1, scriptPtr);

        for (auto &command : script->commands()) {

            TreeClientPtr *commandPtr = new TreeClientPtr{TreeClientType::SCRIPT_COMMAND, command.get(), std::bind(&EditFrame::scriptCommandPopup, this, std::placeholders::_1)};

            treeCtrl->AppendItem(scriptId, command->operation(), -1, -1, commandPtr);


        }

    }

    treeCtrl->Expand(scriptsId);

    return scriptsId;
}

wxTreeItemId EditFrame::createProjectsNode(wxTreeCtrl *treeCtrl, wxTreeItemId rootId) {

    ProjectList &projectList = m_model.m_environments.projects();

    TreeClientPtr *projectsPtr = new TreeClientPtr(TreeClientType::PROJECTS, &projectList, std::bind(&EditFrame::projectsPopup, this, std::placeholders::_1));

    wxTreeItemId projectsId = treeCtrl->AppendItem(rootId, "Projects", -1, -1, projectsPtr);

    for (auto &project : projectList) {

        TreeClientPtr *projectPtr = new TreeClientPtr{TreeClientType::PROJECT, project.get(), std::bind(&EditFrame::projectPopup, this, std::placeholders::_1)};

        wxTreeItemId projectId = treeCtrl->AppendItem(projectsId, project->name(), -1, -1, projectPtr);

        for (auto &projectApp : project->apps()) {

            TreeClientPtr *projectAppPtr = new TreeClientPtr(TreeClientType::PROJECT_APP, projectApp.get(), std::bind(&EditFrame::projectAppPopup, this, std::placeholders::_1));

            Application *app = m_model.m_environments.findApplication(projectApp->applicationId());

            if (app) {

                ApplicationInstallation *applicationInstallation = app->findInstallation(projectApp->defaultInstallationId());

                if (applicationInstallation) {

                    treeCtrl->AppendItem(projectId, app->name() + " / " + applicationInstallation->name(), -1, -1, projectAppPtr);

                }
            }
        }
    }

    treeCtrl->Expand(projectsId);


    return projectsId;
}


wxTreeCtrl *EditFrame::createTree(wxWindow *parent) {

    wxTreeCtrl *treeCtrl = new wxTreeCtrl(parent, ID_APP_TREE);

    TreeClientPtr *rootPtr = new TreeClientPtr(TreeClientType::ROOT, &m_model.m_environments, std::bind(&EditFrame::rootPopup, this, std::placeholders::_1));

    wxTreeItemId rootId = treeCtrl->AddRoot("Root", -1, -1, rootPtr);

    createApplicationsNode(treeCtrl, rootId);

    createScriptsNode(treeCtrl, rootId);

    createProjectsNode(treeCtrl, rootId);

    treeCtrl->Expand(rootId);

    treeCtrl->Bind(wxEVT_TREE_ITEM_RIGHT_CLICK, &EditFrame::onTreeMenu, this);

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

    m_tree = createTree(leftPanel);

    leftPanelSizer->Add(m_tree, 1, wxEXPAND, 0);
    leftPanel->SetSizer(leftPanelSizer);

    wxPanel *rightPanel = new wxPanel(m_splitter, wxID_ANY);
    wxSizer *rightPanelSizer = new wxBoxSizer(wxVERTICAL);
    wxTextCtrl *text = new wxTextCtrl(rightPanel, wxID_ANY);
    rightPanelSizer->Add(text, 1, wxEXPAND, 0);
    rightPanel->SetSizer(rightPanelSizer);

    m_splitter->SplitVertically(leftPanel, rightPanel);

    this->SetSizer(m_panelSizer);
    //m_panelSizer->SetSizeHints(this);

    this->SetSize(600, 400);
}

EditFrame::~EditFrame() {

}

void EditFrame::onTreeMenu(wxTreeEvent &event) {

    CLOG(TRACE, TAG) << "Id: " << event.GetId();

    TreeClientPtr *clientPtr = reinterpret_cast<TreeClientPtr *>( m_tree->GetItemData(event.GetItem()));

    clientPtr->dispatch(event);

}

void EditFrame::rootPopup(wxTreeEvent &event) {

    CLOG(TRACE, TAG) << event.GetId();

}

void EditFrame::applicationsPopup(wxTreeEvent &event) {

    CLOG(TRACE, TAG) << event.GetId();

    wxMenu menu{};

    menu.Append(ID_APPLICATION_NEW, "New Application", "New Application");

    PopupMenu(&menu);
}

void EditFrame::applicationPopup(wxTreeEvent &event) {

    CLOG(TRACE, TAG) << event.GetId();

    wxMenu menu{};

    menu.Append(ID_APPLICATION_INSTALLATION_NEW, "New Installation", "New Installation");
    menu.Append(ID_APPLICATION_DELETE, "Delete Application", "Delete Application");

    PopupMenu(&menu);
}

void EditFrame::applicationInstallationPopup(wxTreeEvent &event) {

    CLOG(TRACE, TAG) << event.GetId();

    wxMenu menu{};

    menu.Append(ID_APPLICATION_INSTALLATION_DELETE, "Delete Installation", "Delete Installation");

    PopupMenu(&menu);

}

void EditFrame::scriptsPopup(wxTreeEvent &event) {

    CLOG(TRACE, TAG) << event.GetId();

    wxMenu menu{};

    menu.Append(ID_SCRIPT_NEW, "New Script", "New Script");

    PopupMenu(&menu);
}

void EditFrame::scriptPopup(wxTreeEvent &event) {

    CLOG(TRACE, TAG) << event.GetId();

    wxMenu menu{};

    menu.Append(ID_SCRIPT_COMMAND_NEW, "New Command", "New Command");
    menu.Append(ID_SCRIPT_DELETE, "Delete Script", "Delete Script");

    PopupMenu(&menu);
}

void EditFrame::scriptCommandPopup(wxTreeEvent &event) {

    CLOG(TRACE, TAG) << event.GetId();

    wxMenu menu{};

    menu.Append(ID_SCRIPT_COMMAND_DELETE, "Delete Command", "Delete Command");

    PopupMenu(&menu);
}

void EditFrame::projectsPopup(wxTreeEvent &event) {

    CLOG(TRACE, TAG) << event.GetId();

    wxMenu menu{};

    menu.Append(ID_PROJECT_NEW, "New Project", "New Project");

    PopupMenu(&menu);
}

void EditFrame::projectPopup(wxTreeEvent &event) {

    CLOG(TRACE, TAG) << event.GetId();

    wxMenu menu{};

    menu.Append(ID_PROJECT_APP_NEW, "New Project App", "New Project App");
    menu.Append(ID_PROJECT_DELETE, "Delete Project", "Delete Project");

    PopupMenu(&menu);
}

void EditFrame::projectAppPopup(wxTreeEvent &event) {

    CLOG(TRACE, TAG) << event.GetId();

    wxMenu menu{};

    menu.Append(ID_PROJECT_APP_DELETE, "Delete Project App", "Delete Project App");

    PopupMenu(&menu);
}


}
}



