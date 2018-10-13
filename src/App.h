/*
 * App.h
 *
 *  Created on: Oct 12, 2018
 *      Author: gantzm
 */

#include <wx/wx.h>

#ifndef APP_H_
#define APP_H_

namespace gg {
namespace envsel {

class App: public wxApp {
public:
    App();
    virtual ~App();
    virtual bool OnInit();
};

} /* namespace envsel */
} /* namespace gg */

#endif /* APP_H_ */
