/*
 * App.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: gantzm
 */

#include "App.h"
#include "AppFrame.h"

namespace gg {
namespace envsel {

App::App() {

}

App::~App() {
}

bool App::OnInit() {

    // TODO: MLG: Read command line arguments and decide with Frame to show:
    //
    //      Select
    //      Edit
    //      Check
    //

    AppFrame * frame = new AppFrame( "Hello World", wxPoint(50,50), wxSize(450,340) );
    frame->Show();
    return true;

}


} /* namespace envsel */
} /* namespace gg */
