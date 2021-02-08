#include "app.h"

// wxWidgets entry point: hands over control of main to wxWidgets
// Called upon wxWidgets startup and should be used to initialize the program
bool CrawlerApp::OnInit() {
  MainFrame *frame = new MainFrame(GUI::appTitle, GUI::windowPosition, GUI::windowSize, GUI::windowStyle);
  frame->Show(true);
  return true;
}

// Main function implementation in wxWidgets
wxIMPLEMENT_APP(CrawlerApp);  // scenario where main in hidden
// wxIMPLEMENT_APP_NO_MAIN(CrawlerApp);