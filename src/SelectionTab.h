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
    SelectionTab(Model & model, wxWindow *parent, wxWindowID winid, const wxString &name, Environment & currentEnvironment);

    virtual ~SelectionTab();

private:
    Model & m_model;

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
