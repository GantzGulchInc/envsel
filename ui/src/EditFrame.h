//
// Created by gantzm on 10/23/18.
//

#pragma once

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/treectrl.h>

#include "Model.h"

namespace gg {
namespace envsel {

enum {

    ID_APPLICATION_NEW = 1,
    ID_APPLICATION_DELETE,
    ID_APPLICATION_INSTALLATION_NEW,
    ID_APPLICATION_INSTALLATION_DELETE,
    ID_SCRIPT_NEW,
    ID_SCRIPT_DELETE,
    ID_SCRIPT_COMMAND_NEW,
    ID_SCRIPT_COMMAND_DELETE,
    ID_PROJECT_NEW,
    ID_PROJECT_DELETE,
    ID_PROJECT_APP_NEW,
    ID_PROJECT_APP_DELETE,

    ID_APP_TREE

};

enum TreeClientType {
    ROOT,
    APPLICATIONS,
    APPLICATION,
    APPLICATION_INSTALLATION,
    SCRIPTS,
    SCRIPT,
    SCRIPT_COMMAND,
    PROJECTS,
    PROJECT,
    PROJECT_APP

};

class EditFrame;

/**
 * Client pointer to domain object at node.
 *
 */

typedef std::function<void(wxTreeEvent &event)> RighClickHandler;

class TreeClientPtr : public wxTreeItemData {
public:
    TreeClientPtr(TreeClientType type, void *item, RighClickHandler handler);

    virtual ~TreeClientPtr();

    TreeClientType type();

    void *get();

    void dispatch(wxTreeEvent &event);

    friend std::ostream &operator<<(std::ostream &stream, const TreeClientPtr &treeClientPtr);

private:
    TreeClientType m_type;
    void *m_item;
    RighClickHandler m_handler;
};

/**
 * The Edit Frame.
 *
 */
class EditFrame : public wxFrame {
public:
    EditFrame(Model &model, const wxString &title, const wxPoint &pos, const wxSize &size);

    virtual ~EditFrame();

private:
    Model &m_model;

    wxPanel *m_panel;
    wxSizer *m_panelSizer;
    wxSplitterWindow *m_splitter;

    wxTreeCtrl * m_tree;


    wxTreeCtrl *createTree(wxWindow *parent);

    wxTreeItemId createApplicationsNode(wxTreeCtrl *treeCtrl, wxTreeItemId rootId);

    wxTreeItemId createScriptsNode(wxTreeCtrl *treeCtrl, wxTreeItemId rootId);

    wxTreeItemId createProjectsNode(wxTreeCtrl *treeCtrl, wxTreeItemId rootId);

    void onApplicationNew(wxCommandEvent & event);
    void onApplicationDelete(wxCommandEvent & event);
    void onApplicationInstallationNew(wxCommandEvent & event);
    void onApplicationInstallationDelete(wxCommandEvent & event);
    void onScriptNew(wxCommandEvent & event);
    void onScriptDelete(wxCommandEvent & event);
    void onScriptCommandNew(wxCommandEvent & event);
    void onScriptCommandDelete(wxCommandEvent & event);
    void onProjectNew(wxCommandEvent & event);
    void onProjectDelete(wxCommandEvent & event);
    void onProjectAppNew(wxCommandEvent & event);
    void onProjectAppDelete(wxCommandEvent & event);
    void onTreeSelectionChange(wxTreeEvent &event);

    void onTreeMenu(wxTreeEvent &event);

    void rootPopup(wxTreeEvent &event);
    void applicationsPopup(wxTreeEvent &event);
    void applicationPopup(wxTreeEvent &event);
    void applicationInstallationPopup(wxTreeEvent &event);
    void scriptsPopup(wxTreeEvent &event);
    void scriptPopup(wxTreeEvent &event);
    void scriptCommandPopup(wxTreeEvent &event);
    void projectsPopup(wxTreeEvent &event);
    void projectPopup(wxTreeEvent &event);
    void projectAppPopup(wxTreeEvent &event);

    wxDECLARE_EVENT_TABLE();

};

}
}

