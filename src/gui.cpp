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
MainFrame::MainFrame(const wxString &title, const wxPoint &pos = GUI::windowPosition, const wxSize &size = GUI::windowSize, long style = GUI::windowStyleNonResizable)
    : wxFrame(NULL, wxID_ANY, title, pos, size, style),
      _graphics(nullptr),
      _robot(std::make_unique<CrawlingRobot>()) {

  // GUI initialization:
  // Init menu
  this->InitMenu();
  // Init control panels
  this->InitPanelTop();
  this->InitPanelBottom();
  this->InitPanelGraphics();
  // Fit all GUI elements into the main app window
  this->InitAppLayout();

  // Graphics; TODO(SK): move to a separate function
  this->_graphics->SetBackgroundStyle(wxBG_STYLE_PAINT);
  this->_graphics->GetRenderSurface()->Bind(wxEVT_PAINT, &MainFrame::OnPaint, this);  // impl in parent through handle

  // Set timer for bitmap demo
  this->_graphics->SetTimerOwner(this);
  this->_graphics->StartTimer(17);
  this->Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);
}

MainFrame::~MainFrame() {
  // TODO(SK): Destroy panels and all its children manually, if wxWidgets doesn't automatically (https://docs.wxwidgets.org/trunk/overview_windowdeletion.html)
  // Destroy spin controls, e.g.:
  // if (this->_ctrlLearningRate != nullptr) {
  //   this->_ctrlLearningRate->Destroy();
  // }
}

// GUI initializers
void MainFrame::InitMenu() {
  // Init new menu bar
  this->_menuBar = new wxMenuBar;
  // Set menu items & status bar; list of standard IDs: https://docs.wxwidgets.org/3.0/page_stockitems.html
  this->_menuFile = new wxMenu;
  this->_menuFile->Append(ID::MENU_HELLO, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
  this->_menuFile->AppendSeparator();
  this->_menuFile->Append(wxID_EXIT);
  this->_menuHelp = new wxMenu;
  this->_menuHelp->Append(wxID_ABOUT);
  // Include all menu items created into the menu bar
  this->_menuBar->Append(this->_menuFile, "&File");
  this->_menuBar->Append(this->_menuHelp, "&Help");
  SetMenuBar(this->_menuBar);
  // Status bar in the bottom of the main window
  CreateStatusBar();
  SetStatusText("Reinforcement Learning: Crawler CS188");
};

void MainFrame::InitPanelTop() {
  // Create the top panel
  this->_panelTop = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::topPanelHeight));
  this->_panelTop->SetBackgroundColour(GUI::topPanelBgrColor);
  this->_panelTopCH = new wxPanel(this->_panelTop, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::topPanelHeight));
  // panelTopCH->SetBackgroundColour(wxColour(100, 200, 200));

  // Top sizer (nested)
  this->_sizerTopCV = new wxBoxSizer(wxVERTICAL);
  this->_sizerTopCH = new wxBoxSizer(wxHORIZONTAL);

  // Three sizers for behavior controls
  this->_sizerMotion = new wxBoxSizer(wxHORIZONTAL);
  this->_sizerSteps = new wxBoxSizer(wxHORIZONTAL);
  this->_sizerReset = new wxBoxSizer(wxHORIZONTAL);

  // sizerTopCH->Add(panelTopCH, 1, wxALIGN_CENTER);
  this->_sizerMotion->Add(new wxButton(this->_panelTop, ID::BTN_RUN, wxString::FromUTF8("Run \u25B6")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  this->_sizerMotion->Add(new wxButton(this->_panelTop, ID::BTN_STOP, wxString::FromUTF8("Stop \u25FC")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  this->_sizerSteps->Add(new wxButton(this->_panelTop, wxID_ANY, "Skip 30K steps"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  this->_sizerSteps->Add(new wxButton(this->_panelTop, wxID_ANY, "Skip 1000K steps"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  this->_sizerReset->Add(new wxButton(this->_panelTop, wxID_ANY, "Reset speed counter"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  this->_sizerReset->Add(new wxButton(this->_panelTop, wxID_ANY, "Reset Q"), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  this->_sizerTopCH->Add(this->_sizerMotion, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  this->_sizerTopCH->Add(this->_sizerSteps, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  this->_sizerTopCH->Add(this->_sizerReset, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  this->_sizerTopCV->Add(_sizerTopCH, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

  this->_panelTop->SetSizerAndFit(this->_sizerTopCV);
};

void MainFrame::InitPanelBottom() {
  // Create the bottom panel
  this->_panelBottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::bottomPanelHeight));
  this->_panelBottom->SetBackgroundColour(GUI::bottomPanelBgrColor);
  this->_panelBottomCH = new wxPanel(this->_panelBottom, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::bottomPanelHeight));

  // Bottom sizer (nested)
  this->_sizerBottomCV = new wxBoxSizer(wxVERTICAL);
  this->_sizerBottomCH = new wxBoxSizer(wxHORIZONTAL);

  // Four sizers for grouped variable controls
  this->_sizerStepDelay = new wxBoxSizer(wxHORIZONTAL);
  this->_sizerEpsilon = new wxBoxSizer(wxHORIZONTAL);
  this->_sizerDiscount = new wxBoxSizer(wxHORIZONTAL);
  this->_sizerLearningRate = new wxBoxSizer(wxHORIZONTAL);

  // Control variables (TODO(SK): move to panels.h)
  // wxSpinCtrlDouble *ctrlLearningRate = new wxSpinCtrlDouble(panelBottom, ID::SPIN_LEARNINGRATE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_WRAP, 0.0, 1.0, 0.8, 0.05);
  this->_ctrlLearningRate = new wxSpinCtrlDouble(_panelBottom, ID::SPIN_LEARNINGRATE);
  this->_ctrlStepDelay = new wxSpinCtrlDouble(_panelBottom, ID::SPIN_STEPDELAY);
  this->_ctrlDiscount = new wxSpinCtrlDouble(_panelBottom, ID::SPIN_DISCOUNT);
  this->_ctrlEpsilon = new wxSpinCtrlDouble(_panelBottom, ID::SPIN_EPSILON);

  this->_ctrlLearningRate->SetDigits(3);  // sets precision of the value of the spin control.
  this->_ctrlLearningRate->SetIncrement(0.05);
  this->_ctrlLearningRate->SetValue(this->_robot->GetLearningRate());

  this->_ctrlStepDelay->SetDigits(3);
  this->_ctrlStepDelay->SetIncrement(0.05);
  this->_ctrlStepDelay->SetValue(this->_robot->GetStepDelay());

  this->_ctrlDiscount->SetDigits(3);
  this->_ctrlDiscount->SetRange(0.0, 1.0);
  this->_ctrlDiscount->SetIncrement(0.05);
  this->_ctrlDiscount->SetValue(this->_robot->GetDiscount());

  this->_ctrlEpsilon->SetDigits(3);
  this->_ctrlEpsilon->SetRange(0.0, 1.0);
  this->_ctrlEpsilon->SetIncrement(0.05);
  this->_ctrlEpsilon->SetValue(this->_robot->GetEpsilon());

  this->_sizerLearningRate->Add(new wxStaticText(this->_panelBottom, wxID_ANY, wxT("Learning Rate:")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 3);
  this->_sizerLearningRate->Add(this->_ctrlLearningRate, 0, wxALIGN_CENTER, 0);
  this->_sizerStepDelay->Add(new wxStaticText(this->_panelBottom, wxID_ANY, wxT("Step Delay:")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 3);
  this->_sizerStepDelay->Add(this->_ctrlStepDelay, 0, wxALIGN_CENTER, 0);
  this->_sizerDiscount->Add(new wxStaticText(this->_panelBottom, wxID_ANY, wxT("Discount:")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 3);
  this->_sizerDiscount->Add(this->_ctrlDiscount, 0, wxALIGN_CENTER, 0);
  this->_sizerEpsilon->Add(new wxStaticText(this->_panelBottom, wxID_ANY, wxT("Epsilon:")), 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 3);
  this->_sizerEpsilon->Add(this->_ctrlEpsilon, 0, wxALIGN_CENTER, 0);

  this->_sizerBottomCH->Add(this->_sizerLearningRate, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  this->_sizerBottomCH->Add(this->_sizerStepDelay, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  this->_sizerBottomCH->Add(this->_sizerDiscount, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
  this->_sizerBottomCH->Add(this->_sizerEpsilon, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);

  this->_sizerBottomCV->Add(this->_sizerBottomCH, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

  this->_panelBottom->SetSizerAndFit(this->_sizerBottomCV);
};

void MainFrame::InitPanelGraphics() {
  // Create the graphics panel
  this->_panelGraphics = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(GUI::bitmapWidth, GUI::bitmapHeight));
  this->_panelGraphics->SetBackgroundColour(GUI::middlePanelBgrColor);  // in case the bitmap width != window width
  
  // Middle sizer – _graphics
  this->_graphics = std::make_unique<Graphics>(this->_panelGraphics, GUI::bitmapWidth, GUI::bitmapHeight);
  this->_sizerGraphics = new wxBoxSizer(wxVERTICAL);
  this->_sizerGraphics->Add(this->_graphics->GetRenderSurface(), 1, wxALIGN_CENTER);
  this->_panelGraphics->SetSizerAndFit(this->_sizerGraphics);
  // Layout(); // resize element to cover the entire window: https://docs.wxwidgets.org/trunk/classwx_top_level_window.html#adfe7e3f4a32f3ed178968f64431bbfe0
};

void MainFrame::InitAppLayout() {
  // Main vertical sizer
  this->_sizerMain = new wxBoxSizer(wxVERTICAL);
  this->_sizerMain->Add(this->_panelTop, 0, wxEXPAND);
  this->_sizerMain->Add(this->_panelGraphics, 1, wxEXPAND);
  this->_sizerMain->Add(this->_panelBottom, 0, wxEXPAND);
  this->SetSizerAndFit(this->_sizerMain);
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
      this->_robot->SetLearningRate(value);
      break;
    }
    case ID::SPIN_STEPDELAY: {
      std::cout << "SPIN_STEPDELAY: "
                << event.GetValue() << std::endl;
      this->_robot->SetStepDelay(value);
      break;
    }
    case ID::SPIN_DISCOUNT: {
      std::cout << "SPIN_DISCOUNT: "
                << event.GetValue() << std::endl;
      this->_robot->SetDiscount(value);
      break;
    }
    case ID::SPIN_EPSILON: {
      std::cout << "SPIN_EPSILON: "
                << event.GetValue() << std::endl;
      this->_robot->SetEpsilon(value);
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
  this->_graphics->DrawToBuffer();
}

void MainFrame::OnTimer(wxTimerEvent &event) {
  _graphics->RebuildBufferAndRefresh();
}