#include "gui.h"

// // Initialise SDL before WX-Widgets and GTK3
// int main(int argc, char** argv) {
//   if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
//     std::cerr << "SDL Initialisation Error\n\n";
//   }
//   return wxEntry(argc, argv);
// }

// Main function implementation in wxWidgets
wxIMPLEMENT_APP(CrawlerApp);  // scenario where main in hidden
// wxIMPLEMENT_APP_NO_MAIN(CrawlerApp);