//
// Created by gantzm on 10/24/18.
//

#include "EditApplicationPanel.h"

namespace gg {
namespace envsel {


EditApplicationPanel::EditApplicationPanel(wxWindow *parent, Application *application) :
        wxPanel{parent, wxID_ANY},
        m_application{application} {

    int rows = 10;

    m_panelSizer = new wxBoxSizer(wxVERTICAL);
    m_flexGridSizer = new wxFlexGridSizer(rows, 2, 10, 10);
    m_flexGridSizer->AddGrowableCol(1, 1);

    wxStaticText *idLabel = new wxStaticText(this, wxID_ANY, "ID:");
    wxTextCtrl *idText = new wxTextCtrl(this, wxID_ANY);
    idText->SetValue(m_application->id());

    m_flexGridSizer->Add(idLabel);
    m_flexGridSizer->Add(idText);

    wxStaticText *nameLabel = new wxStaticText(this, wxID_ANY, "Name:");
    wxTextCtrl *nameText = new wxTextCtrl(this, wxID_ANY);
    nameText->SetValue(m_application->name());

    m_flexGridSizer->Add(nameLabel);
    m_flexGridSizer->Add(nameText);

    m_panelSizer->Add(m_flexGridSizer, 1, wxALL | wxEXPAND, 15);

    SetSizer(m_panelSizer);
}

EditApplicationPanel::~EditApplicationPanel() {

}


}
}