#include <wx/wx.h>
#include <iostream>

#include "GamePanel.hh"
#include "MainFrame.hh"

/**
 * Game canvas for drawing grid and hadling user clicks.
 * Grid controls are sent to Grid object.
 */
GamePanel::GamePanel(wxPanel *parent, int id):
    wxPanel(parent, id, wxDefaultPosition), grid_(30) {

    // Timer which runs cells to next state in intervals
    timer_ = new wxTimer(this, 1);

    Connect(wxEVT_PAINT, wxPaintEventHandler(GamePanel::onPaint));
    Connect(wxEVT_SIZE, wxSizeEventHandler(GamePanel::onSize));
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(GamePanel::onMouseClick));
    Connect(wxEVT_TIMER, wxCommandEventHandler(GamePanel::onTimer));
}

void
GamePanel::setSize(int size) {
    grid_ = Grid(size);
    resetGame();
}

void
GamePanel::toggleRun() {
    if (timer_->IsRunning()) {
        timer_->Stop();
    } else {
        timer_->Start(100);
    }
}

void
GamePanel::randomGrid() {
    if (timer_->IsRunning()) {
        timer_->Stop();
    }
    grid_.randomize();
    Refresh();
}

void
GamePanel::resetGame() {
    if (timer_->IsRunning()) {
        timer_->Stop();
    }
    grid_.fillWithZeroes();
    Refresh();
}

void
GamePanel::runStep() {
    grid_.evolve();
    Refresh();
}

void
GamePanel::onTimer(wxCommandEvent& event) {
    runStep();
}

void
GamePanel::onMouseClick(wxMouseEvent& event) {
    wxPoint p = event.GetPosition();
    int width = GetSize().x;
    int height = GetSize().y;
    int cellSizeX = width / grid_.sizeX();
    int cellSizeY = height / grid_.sizeY();
    int offsetX = (width % grid_.sizeX()) / 2;
    int offsetY = (height % grid_.sizeY()) / 2;

    int i = (p.x - offsetX) / cellSizeX;
    int j = (p.y - offsetY) / cellSizeY;
    grid_.toggleCell(i, j);

    Refresh();
}

/**
 * Draws rectangles for each cell in grid.
 * NOTE: wxWidgets coordinates are ints and it lefts some empty space
 * when dividing canvas into multiple cells on certain sizes.
 * TODO: find a proper way to draw scalable grid.
 */
void
GamePanel::onPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);

    int width = GetSize().x;
    int height = GetSize().y;
    int cellSizeX = width / grid_.sizeX();
    int cellSizeY = height / grid_.sizeY();
    // offset to center grid on canvas, so it doesnt look that ugly
    int offsetX = (width % grid_.sizeX()) / 2;
    int offsetY = (height % grid_.sizeY()) / 2;

    for (int i = 0; i < grid_.sizeX(); i++) {
        for (int j = 0; j < grid_.sizeY(); j++) {
            int x = i * cellSizeX + offsetX;
            int y = j * cellSizeY + offsetY;
            if (grid_.isAlive(i, j)) {
                dc.SetPen(wxPen(wxColour(0, 0, 0), 0, wxPENSTYLE_TRANSPARENT));
                dc.SetBrush(wxBrush(wxColour(130, 200, 130)));
            } else {
                dc.SetPen(wxPen(wxColour(230, 230, 230), 0));
                dc.SetBrush(wxBrush(wxColour(255, 255, 255)));
            }
            dc.DrawRectangle(x, y, cellSizeX, cellSizeY);
        }
    }
}

void
GamePanel::onSize(wxSizeEvent& event) {
    Refresh();
}