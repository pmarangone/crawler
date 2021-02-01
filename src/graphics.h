#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>

class Screen {
 public:
  Screen();
  virtual ~Screen();
  bool init();
  void close();
  bool processEvents();
  void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
  void update();
  void boxBlur();
  void clear();
  const static int SCREEN_WIDTH = 400;
  const static int SCREEN_HEIGHT = 200;

 private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  SDL_Texture *_texture;
  Uint32 *_buffer1;
  Uint32 *_buffer2;
};

#endif /* GRAPHICS_H */

// How to embed SDl2 window into a wxWidgets panel: https://forums.wxwidgets.org/viewtopic.php?t=42189