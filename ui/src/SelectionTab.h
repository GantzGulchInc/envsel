//
// Created by gantzm on 10/18/18.
//

#pragma once


#include "Domain.h"
#include "Model.h"

#include "ArgumentParser.h"

#include <wx/wx.h>

namespace gg {
namespace envsel {

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * SelectionTab
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class SelectionTab : public wxPanel {

public:
    SelectionTab(Model & model, wxWindow *parent, wxWindowID winid, const wxString &name, Project & currentEnvironment);

    virtual ~SelectionTab();

private:
    Arguments & m_args;
    Model & m_model;

    Project & m_currentEnvironment;

    wxSizer * m_panelSizer;
    wxFlexGridSizer * m_flexGridSizer;
    wxSizer * m_buttonSizer;

    wxButton * m_selectButton;
    wxButton * m_cancelButton;

    std::vector<wxComboBox *> m_comboBoxes;

    wxComboBox * createComboBox(wxWindow *parent, ProjectApp * envApp, const ApplicationInstallationList & installedApps);

    void onSelect(wxCommandEvent &event);
    void onCancel(wxCommandEvent &event);
    void onChange(wxCommandEvent &event);
};

}
}
