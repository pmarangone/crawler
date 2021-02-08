#ifndef APP_H
#define APP_H

#include "gui.h"

class CrawlerApp : public wxApp {
 public:
  virtual bool OnInit();  // wxWidgets entry point: hands over control of main to wxWidgets
};


#endif /* APP_H */