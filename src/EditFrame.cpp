//
// Created by gantzm on 10/23/18.
//

#include "EditFrame.h"


namespace gg {
namespace envsel {

EditFrame::EditFrame(gg::envsel::Model &model, const wxString &title, const wxPoint &pos, const wxSize &size) :
        wxFrame(NULL, wxID_ANY, title, pos, size), m_model(model) {

    m_panel = new wxPanel(this);

}

EditFrame::~EditFrame() {

}


}
}



