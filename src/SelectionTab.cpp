//
// Created by gantzm on 10/18/18.
//

#include "SelectionTab.h"

#include "IO.h"

#include <iomanip>
#include <map>

namespace gg {
namespace envsel {


static const char *TAG = "View";

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// SelectionTab
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

SelectionTab::SelectionTab(Model & model, wxWindow *parent, wxWindowID winId, const wxString &name, Environment &currentEnvironment) :
        wxPanel(parent, winId, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER, name), //
        m_model(model), //
        m_currentEnvironment(currentEnvironment) {

    int rows = currentEnvironment.apps().size();

    CLOG(TRACE, TAG) << "SelectinoTab:ctor: outputFilename: " << m_model.m_args.outputFilename();

    m_panelSizer = new wxBoxSizer(wxVERTICAL);
    m_flexGridSizer = new wxFlexGridSizer(rows, 2, 10, 10);
    m_flexGridSizer->AddGrowableCol(1, 1);

    for (auto &envApp : currentEnvironment.apps()) {

        Application *app = m_model.m_environments.findApplication(envApp->applicationId());

        if (app) {

            wxStaticText *label = new wxStaticText(this, wxID_ANY, app->name());

            wxComboBox *comboBox = createComboBox(this, envApp->installationId(), app->installations());

            m_comboBoxes.push_back(comboBox);

            m_flexGridSizer->Add(label);
            m_flexGridSizer->Add(comboBox);

        }
    }

    m_panelSizer->Add(m_flexGridSizer, 1, wxALL | wxEXPAND, 15);

    m_buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    m_panelSizer->Add(m_buttonSizer, 0, wxALL | wxEXPAND, 15);

    m_selectButton = new wxButton(this, wxID_ANY, "Select");
    m_selectButton->Bind(wxEVT_BUTTON, &SelectionTab::onSelect, this, wxID_ANY);

    m_cancelButton = new wxButton(this, wxID_EXIT, "Cancel");

    m_buttonSizer->Add(m_selectButton);
    m_buttonSizer->AddStretchSpacer(1);
    m_buttonSizer->Add(m_cancelButton);


    this->SetSizer(m_panelSizer);
}

SelectionTab::~SelectionTab() {

}


wxComboBox *SelectionTab::createComboBox(wxWindow *parent, const std::string &selectedId, const ApplicationInstallationList &installedApps) {

    wxComboBox *cb = new wxComboBox{parent, wxID_ANY};

    int count{1};
    int selected{0};

    cb->Append("None", (void *) nullptr);

    for (auto &installedApp : installedApps) {

        cb->Append(installedApp->name(), installedApp.get());

        if (installedApp->id() == selectedId) {
            selected = count;
        }

        count += 1;
    }

    cb->SetSelection(selected);

    return cb;
}



void SelectionTab::onSelect(wxCommandEvent &event) {

    CLOG(TRACE, TAG) << "Called.";

    std::map<std::string,std::string> variables;

    for (auto a : m_comboBoxes) {

        ApplicationInstallation *installation = reinterpret_cast<ApplicationInstallation *>(a->GetClientData(a->GetSelection()));

        if (installation) {

            CLOG(TRACE, TAG) << "Selected: " << *installation;

            for(auto & v : installation->variables()) {
                variables[v->name()] = v->value();
            }

        } else {

            CLOG(TRACE, TAG) << "Selected: None";
        }
    }

    CLOG(TRACE, TAG) << "Variables:";

    for(auto e : variables) {
        CLOG(TRACE, TAG) << "    Name: " << std::setw(20) << std::left << e.first << " Value: " << e.second;
    }

    std::vector<std::string> output;

    output = m_model.m_environments.executeScripts( variables );

    CLOG(TRACE, TAG) << "Output:";

    for(auto sl : output) {
        CLOG(TRACE, TAG) << "    : " << sl;
    }

    CLOG(TRACE, TAG) << " ouputFilename: " << m_model.m_args.outputFilename();

    writeOutput(m_model.m_args.outputFilename(), output);

    CLOG(TRACE, TAG) << "Finished writing script.";
}

void SelectionTab::onCancel(wxCommandEvent &event) {

    CLOG(TRACE, TAG) << "Called.";

}

}
}
