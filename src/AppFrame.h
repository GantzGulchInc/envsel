/*
 * AppFrame.h
 *
 *  Created on: Oct 12, 2018
 *      Author: gantzm
 */

#include <wx/wx.h>

#ifndef APPFRAME_H_
#define APPFRAME_H_

namespace gg {
namespace envsel {

class AppFrame : public wxFrame {
public:
    AppFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~AppFrame();
private:
    void OnHello(wxCommandEvent & event);
    void OnExit(wxCommandEvent & event);
    void OnAbout(wxCommandEvent & event);

    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_Hello = 1
};


} /* namespace envsel */
} /* namespace gg */

#endif /* APPFRAME_H_ */
