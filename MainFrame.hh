#ifndef MAINFRAME_HH
#define MAINFRAME_HH

#include <wx/wx.h>
#include <wx/spinctrl.h>

#include "GamePanel.hh"

class MainFrame : public wxFrame {

public:
    MainFrame(const wxString& title);

private:
    void initGui();
    void onSpinnerChange(wxSpinEvent& event);
    void onToggleRun(wxCommandEvent& event);
    void onStep(wxCommandEvent& event);
    void onRandom(wxCommandEvent& event);
    void onReset(wxCommandEvent& event);

    // IDs for GUI elements
    const int ID_CANVAS = 100;
    const int ID_SPINNER = 101;
    const int ID_RUN = 102;
    const int ID_STEP = 103;
    const int ID_RANDOM = 104;
    const int ID_RESET = 105;

    GamePanel* gamePanel_;
    wxSpinCtrl* spinner_;
};

#endif