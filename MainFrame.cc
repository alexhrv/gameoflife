#include "MainFrame.hh"

/**
 * Main window which holds canvas and controls
 *
 */
MainFrame::MainFrame(const wxString& title):
    wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(610, 644)) {

    initGui();

    // conenct gui elements to event handling methods
    Connect(ID_RUN, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(MainFrame::onToggleRun));
    Connect(ID_STEP, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(MainFrame::onStep));
    Connect(ID_RANDOM, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(MainFrame::onRandom));
    Connect(ID_RESET, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(MainFrame::onReset));
    Connect(ID_SPINNER, wxEVT_SPINCTRL,
        wxSpinEventHandler(MainFrame::onSpinnerChange));
}

/**
 * Various event handling methods for game control
 */
void
MainFrame::onSpinnerChange(wxSpinEvent& event) {
    gamePanel_->setSize(spinner_->GetValue());
}

void
MainFrame::onToggleRun(wxCommandEvent& event) {
    gamePanel_->toggleRun();
}

void
MainFrame::onStep(wxCommandEvent& event) {
    gamePanel_->runStep();
}

void
MainFrame::onRandom(wxCommandEvent& event) {
    gamePanel_->randomGrid();
}

void
MainFrame::onReset(wxCommandEvent& event) {
    gamePanel_->resetGame();
}

/**
 * Initialize GUI, add game canvas and control elements
 */
void
MainFrame::initGui() {
    // main panel which holds everything
    wxPanel *panel = new wxPanel(this, -1);
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    // game canvas
    gamePanel_ = new GamePanel(panel, ID_CANVAS);
    gamePanel_->SetBackgroundColour(wxColour(50, 50, 50));

    // control elements
    wxStaticText *txtLbl = new wxStaticText(panel, wxID_ANY, wxT("Grid size:"));
    spinner_ = new wxSpinCtrl(panel, ID_SPINNER, wxT("30"));
    spinner_->SetRange(10, 100);
    wxButton* runBtn = new wxButton(panel, ID_RUN, wxT("Run/Pause"));
    wxButton* stepBtn = new wxButton(panel, ID_STEP, wxT("Step"));
    wxButton* rndBtn = new wxButton(panel, ID_RANDOM, wxT("Random"));
    wxButton* rstBtn = new wxButton(panel, ID_RESET, wxT("Reset"));
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    hbox->Add(txtLbl, 0, wxALIGN_CENTER_VERTICAL);
    hbox->Add(spinner_, 0, wxALIGN_CENTER_VERTICAL);
    hbox->Add(runBtn, 0, wxALIGN_CENTER_VERTICAL);
    hbox->Add(stepBtn, 0, wxALIGN_CENTER_VERTICAL);
    hbox->Add(rndBtn, 0, wxALIGN_CENTER_VERTICAL);
    hbox->Add(rstBtn, 0, wxALIGN_CENTER_VERTICAL);

    vbox->Add(gamePanel_, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 5);
    vbox->Add(hbox, 0, wxALIGN_CENTER | wxALL, 5);
    panel->SetSizer(vbox);
    Centre();
}
