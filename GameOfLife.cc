#include "GameOfLife.hh"
#include "MainFrame.hh"

IMPLEMENT_APP(GameOfLife)

bool
GameOfLife::OnInit() {

    MainFrame *mainFrame = new MainFrame(wxT("The Game Of Life"));
    mainFrame->Show(true);

    return true;
}