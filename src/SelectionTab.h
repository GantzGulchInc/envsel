//
// Created by gantzm on 10/18/18.
//

#pragma once

#include "Domain.h"

#include "ArgumentParser.h"

#include <wx/wx.h>

namespace gg {
namespace envsel {

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * SelectionTab
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class SelectionTab : public wxPanel {

public:
    SelectionTab(const Arguments & args, wxWindow *parent, wxWindowID winid, const wxString &name, Environments & environments, Environment & currentEnvironment);

    virtual ~SelectionTab();

private:
    const Arguments & m_args;
    Environments & m_environments;
    Environment & m_currentEnvironment;

    wxSizer * m_panelSizer;
    wxFlexGridSizer * m_flexGridSizer;
    wxSizer * m_buttonSizer;

    wxButton * m_selectButton;
    wxButton * m_cancelButton;

    std::vector<wxComboBox *> m_comboBoxes;

    wxComboBox * createComboBox(wxWindow *parent, const std::string & selectedId, const ApplicationInstallationList & installedApps);

    void onSelect(wxCommandEvent &event);
    void onCancel(wxCommandEvent &event);
};

}
}
