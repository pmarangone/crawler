#include "app.h"

// wxWidgets entry point: hands over control of main to wxWidgets
// Called upon wxWidgets startup and should be used to initialize the program
bool CrawlerApp::OnInit() {
  MainFrame *frame = new MainFrame(GUI::appTitle, GUI::windowPosition, GUI::windowSize, GUI::windowStyleNonResizable);
  frame->Show(true);
  // Setting min & max size (to force no-resize option for Linux & Windows)
  frame->SetMinSize(GUI::windowSize);
  frame->SetMaxSize(GUI::windowSize);
  return true;
}

// Main function implementation in wxWidgets
wxIMPLEMENT_APP(CrawlerApp);  // scenario where main in hidden
// wxIMPLEMENT_APP_NO_MAIN(CrawlerApp);