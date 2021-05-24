#ifndef GAMEPANEL_HH
#define GAMEPANEL_HH

#include <wx/wx.h>

#include "Grid.hh"


class GamePanel : public wxPanel {

public:

    GamePanel(wxPanel *parent, int id );

    void setSize(int size);
    void toggleRun();
    void randomGrid();
    void resetGame();
    void runStep();

private:
    void onMouseClick(wxMouseEvent& event);
    void onPaint(wxPaintEvent& event);  
    void onSize(wxSizeEvent& event);
    void onTimer(wxCommandEvent& event);

    wxTimer* timer_;
    Grid grid_;
};

#endif