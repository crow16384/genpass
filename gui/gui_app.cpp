// SPDX-License-Identifier: GPL-3.0-only

#include "main_frame.hpp"
#include <wx/wx.h>

class GenPassApp : public wxApp {
public:
    bool OnInit() override {
        auto* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(GenPassApp);
