#include "gui.h"

// Custom event table for MainFrame class where events are routed to their respective handler functions
// clang-format off
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
  // Menu
  EVT_MENU(ID::MENU_HELLO, MainFrame::OnHello)
  EVT_MENU(wxID_EXIT, MainFrame::OnExit)
  EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
  // Buttons
	EVT_BUTTON(ID::BTN_RUN, MainFrame::OnClickRun)	// run btn mouse click
	EVT_BUTTON(ID::BTN_STOP, MainFrame::OnClickStop)	// stop btn mouse click
	EVT_BUTTON(wxID_ANY, MainFrame::OnClick)  // wxID_ANY here means we react the same way to all buttons; standard implementation should be in the bottom
  // Controls
  EVT_SPINCTRLDOUBLE(wxID_ANY, MainFrame::OnSpinCtrl)

  // EVT_IDLE(MainFrame::OnIdle)
wxEND_EVENT_TABLE()
;  // clang-format on

// Main window

// Constructor for a non-resizable window (use wxDEFAULT_FRAME_STYLE style for a resizable window)
MainFrame::MainFrame(const wxString &title, 
                     const wxPoint &pos = GUI::windowPosition, 
                     const wxSize &size = GUI::windowSize, 
                     long style = GUI::windowStyleNonResizable)
    : wxFrame(NULL, wxID_ANY, title, pos, size, style),
      _graphics(nullptr),
      _robot(std::make_unique<CrawlingRobot>()) {

  // GUI initialization:
  // Init menu
  InitMenu();
  // Init control panels
  InitPanelTop();
  InitPanelBottom();
  InitPanelGraphics();
  // Fit all GUI elements into the main app window
  InitAppLayout();

  // Graphics; TODO(SK): move to a separate function
  _graphics->SetBackgroundStyle(wxBG_STYLE_PAINT);
  _graphics->GetRenderSurface()->Bind(wxEVT_PAINT, &MainFrame::OnPaint, this);  // impl in parent through handle

  // Set timer for bitmap demo
  _graphics->SetTimerOwner(this);
  _graphics->StartTimer(17);
  Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);
}

MainFrame::~MainFrame() {
  // TODO(SK): Destroy panels and all its children manually, if wxWidgets doesn't automatically (https://docs.wxwidgets.org/trunk/overview_windowdeletion.html)
  // Destroy spin controls, e.g.:
  // if (_ctrlLearningRate != nullptr) {
  //   _ctrlLearningRate->Destroy();
  // }
}

// GUI initializers
void MainFrame::InitMenu() {
  // Init new menu bar
  _menuBar = new wxMenuBar;
  // Set menu items & status bar; list of standard IDs: https://docs.wxwidgets.org/3.0/page_stockitems.html
  _menuFile = new wxMenu;
  _menuFile->Append(ID::MENU_HELLO, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
  _menuFile->AppendSeparator();
  _menuFile->Append(wxID_EXIT);
  _menuHelp = new wxMenu;
  _menuHelp->Append(wxID_ABOUT);
  // Include all menu items created into the menu bar
  _menuBar->Append(_menuFile, "&File");
  _menuBar->Append(_menuHelp, "&Help");
  SetMenuBar(_menuBar);
  // Status bar in the bottom of the main window
  CreateStatusBar();
  SetStatusText("Reinforcement Learning: Crawler CS188");
};

void MainFrame::InitPanelTop() {
  // Create the top panel
  _panelTop = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::topPanelHeight));
  _panelTop->SetBackgroundColour(GUI::topPanelBgrColor);
  _panelTopCH = new wxPanel(_panelTop, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::topPanelHeight));
  // panelTopCH->SetBackgroundColour(wxColour(100, 200, 200));

  // Top sizer (nested)
  _sizerTopCV = new wxBoxSizer(wxVERTICAL);
  _sizerTopCH = new wxBoxSizer(wxHORIZONTAL);

  // Three sizers for behavior controls
  _sizerMotion = new wxBoxSizer(wxHORIZONTAL);
  _sizerSteps = new wxBoxSizer(wxHORIZONTAL);
  _sizerReset = new wxBoxSizer(wxHORIZONTAL);

  // sizerTopCH->Add(panelTopCH, 1, wxALIGN_CENTER);
  _sizerMotion->Add(new wxButton(_panelTop, ID::BTN_RUN, wxString::FromUTF8("Run \u25B6")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  _sizerMotion->Add(new wxButton(_panelTop, ID::BTN_STOP, wxString::FromUTF8("Stop \u25FC")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  _sizerSteps->Add(new wxButton(_panelTop, wxID_ANY, "Skip 30K steps"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  _sizerSteps->Add(new wxButton(_panelTop, wxID_ANY, "Skip 1000K steps"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  _sizerReset->Add(new wxButton(_panelTop, wxID_ANY, "Reset speed counter"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  _sizerReset->Add(new wxButton(_panelTop, wxID_ANY, "Reset Q"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  _sizerTopCH->Add(_sizerMotion, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  _sizerTopCH->Add(_sizerSteps, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  _sizerTopCH->Add(_sizerReset, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  _sizerTopCV->Add(_sizerTopCH, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

  _panelTop->SetSizerAndFit(_sizerTopCV);
};

void MainFrame::InitPanelBottom() {
  // Create the bottom panel
  _panelBottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::bottomPanelHeight));
  _panelBottom->SetBackgroundColour(GUI::bottomPanelBgrColor);
  _panelBottomCH = new wxPanel(_panelBottom, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::bottomPanelHeight));

  // Bottom sizer (nested)
  _sizerBottomCV = new wxBoxSizer(wxVERTICAL);
  _sizerBottomCH = new wxBoxSizer(wxHORIZONTAL);

  // Four sizers for grouped variable controls
  _sizerStepDelay = new wxBoxSizer(wxHORIZONTAL);
  _sizerEpsilon = new wxBoxSizer(wxHORIZONTAL);
  _sizerDiscount = new wxBoxSizer(wxHORIZONTAL);
  _sizerLearningRate = new wxBoxSizer(wxHORIZONTAL);

  // Control variables (TODO(SK): move to panels.h)
  // wxSpinCtrlDouble *ctrlLearningRate = new wxSpinCtrlDouble(panelBottom, ID::SPIN_LEARNINGRATE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_WRAP, 0.0, 1.0, 0.8, 0.05);
  _ctrlLearningRate = new wxSpinCtrlDouble(_panelBottom, ID::SPIN_LEARNINGRATE);
  _ctrlStepDelay = new wxSpinCtrlDouble(_panelBottom, ID::SPIN_STEPDELAY);
  _ctrlDiscount = new wxSpinCtrlDouble(_panelBottom, ID::SPIN_DISCOUNT);
  _ctrlEpsilon = new wxSpinCtrlDouble(_panelBottom, ID::SPIN_EPSILON);

  _ctrlLearningRate->SetDigits(3);  // sets precision of the value of the spin control.
  _ctrlLearningRate->SetIncrement(0.05);
  _ctrlLearningRate->SetValue(_robot->GetLearningRate());

  _ctrlStepDelay->SetDigits(3);
  _ctrlStepDelay->SetIncrement(0.05);
  _ctrlStepDelay->SetValue(_robot->GetStepDelay());

  _ctrlDiscount->SetDigits(3);
  _ctrlDiscount->SetRange(0.0, 1.0);
  _ctrlDiscount->SetIncrement(0.05);
  _ctrlDiscount->SetValue(_robot->GetDiscount());

  _ctrlEpsilon->SetDigits(3);
  _ctrlEpsilon->SetRange(0.0, 1.0);
  _ctrlEpsilon->SetIncrement(0.05);
  _ctrlEpsilon->SetValue(_robot->GetEpsilon());

  _sizerLearningRate->Add(new wxStaticText(_panelBottom, wxID_ANY, wxT("Learning Rate:")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 3);
  _sizerLearningRate->Add(_ctrlLearningRate, 0, wxALIGN_CENTER, 0);
  _sizerStepDelay->Add(new wxStaticText(_panelBottom, wxID_ANY, wxT("Step Delay:")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 3);
  _sizerStepDelay->Add(_ctrlStepDelay, 0, wxALIGN_CENTER, 0);
  _sizerDiscount->Add(new wxStaticText(_panelBottom, wxID_ANY, wxT("Discount:")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 3);
  _sizerDiscount->Add(_ctrlDiscount, 0, wxALIGN_CENTER, 0);
  _sizerEpsilon->Add(new wxStaticText(_panelBottom, wxID_ANY, wxT("Epsilon:")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 3);
  _sizerEpsilon->Add(_ctrlEpsilon, 0, wxALIGN_CENTER, 0);

  _sizerBottomCH->Add(_sizerLearningRate, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  _sizerBottomCH->Add(_sizerStepDelay, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  _sizerBottomCH->Add(_sizerDiscount, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  _sizerBottomCH->Add(_sizerEpsilon, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  _sizerBottomCV->Add(_sizerBottomCH, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

  _panelBottom->SetSizerAndFit(_sizerBottomCV);
};

void MainFrame::InitPanelGraphics() {
  // Create the graphics panel
  _panelGraphics = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::bitmapHeight));
  _panelGraphics->SetBackgroundColour(GUI::middlePanelBgrColor);  // in case the bitmap width != window width
  
  // Middle sizer – _graphics
  _graphics = std::make_unique<Graphics>(_panelGraphics, GUI::bitmapWidth, GUI::bitmapHeight);
  _sizerGraphics = new wxBoxSizer(wxVERTICAL);
  _sizerGraphics->Add(_graphics->GetRenderSurface(), 1, wxALIGN_CENTER);
  _panelGraphics->SetSizerAndFit(_sizerGraphics);
  // Layout(); // resize element to cover the entire window: https://docs.wxwidgets.org/trunk/classwx_top_level_window.html#adfe7e3f4a32f3ed178968f64431bbfe0
};

void MainFrame::InitAppLayout() {
  // Main vertical sizer
  _sizerMain = new wxBoxSizer(wxVERTICAL);
  _sizerMain->Add(_panelTop, 0, wxEXPAND);
  _sizerMain->Add(_panelGraphics, 1, wxEXPAND);
  _sizerMain->Add(_panelBottom, 0, wxEXPAND);
  SetSizerAndFit(_sizerMain);
}


// All event handlers
// Menu event handlers
void MainFrame::OnExit(wxCommandEvent &event) {
  Close(true);
}

void MainFrame::OnAbout(wxCommandEvent &event) {
  wxMessageBox("This application is built by Patrick Marangone and Sergei Kononov in an attempt to replicate the reinforcement learning crawler from UC Berkeley CS188 class.", "About the Crawler", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnHello(wxCommandEvent &event) {
  wxLogMessage("Hello world from wxWidgets!");
}

// Button event handlers
void MainFrame::OnClickRun(wxCommandEvent &event) {
  std::cout << "RUN btn clicked. ID: " << event.GetId() << std::endl;
}

void MainFrame::OnClickStop(wxCommandEvent &event) {
  std::cout << "STOP btn clicked. ID: " << event.GetId() << std::endl;
}

void MainFrame::OnClick(wxCommandEvent &event) {  // for events objects deriving from wxCommandEvent, the events get propagated thru parent controls (current parent where e.g. a button is, i.e. widnow, panel, frame, etc.)
  std::cout << "Standard button clicked. ID: " << event.GetId() << std::endl;
  // event.Skip();  // force event propagation to the next EVT_BUTTON event in the table (omit, if you put EVT_BUTTON(wxID_ANY, MainFrame::OnClick) in the bottom of the event table)
}

// Spin control event handlers
void MainFrame::OnSpinCtrl(wxSpinDoubleEvent &event) {
  const int id = event.GetId();
  const double value = event.GetValue();
  switch (id) {
    case ID::SPIN_LEARNINGRATE: {
      std::cout << "SPIN_LEARNINGRATE: "
                << event.GetValue() << std::endl;
      _robot->SetLearningRate(value);
      break;
    }
    case ID::SPIN_STEPDELAY: {
      std::cout << "SPIN_STEPDELAY: "
                << event.GetValue() << std::endl;
      _robot->SetStepDelay(value);
      break;
    }
    case ID::SPIN_DISCOUNT: {
      std::cout << "SPIN_DISCOUNT: "
                << event.GetValue() << std::endl;
      _robot->SetDiscount(value);
      break;
    }
    case ID::SPIN_EPSILON: {
      std::cout << "SPIN_EPSILON: "
                << event.GetValue() << std::endl;
      _robot->SetEpsilon(value);
      break;
    }
    default:
      std::cout << "General (unidentified) spin control" << std::endl;
      // TODO(SK): handle or disable
      event.StopPropagation();
  }
}

// Graphics handlers
void MainFrame::OnPaint(wxPaintEvent &event) {
  _graphics->DrawToBuffer();
}

void MainFrame::OnTimer(wxTimerEvent &event) {
  _graphics->RebuildBufferAndRefresh();
}