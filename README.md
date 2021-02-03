# Crawler CS188

Custom homemade replica of Berkeley's CS188 class implemented in C++, wxWidgets and SDL2 by Patrick Marangone (@[pmarangone](https://github.com/pmarangone)) and Sergei Kononov (@[hemulens](https://github.com/hemulens)).

## Target

![Target interface of the project](_resources/img/example-berkeley-1.png "Crawler CS188")

## Tentative TODOs

- [x] Find approach to building a CS188's crawler-app-like GUI and graphics
- [ ] Choose best suitable libraries
  - [x] a) Use WxWidgets for GUI
  - [x] b) [Integrate](http://code.technoplaza.net/wx-sdl/) SDL2 (graphics) into WxWidgets GUI (CANCELED)
- [ ] Build GUI
  - [x] Create top and bottom panels
  - [x] Add two buttons: ["run", "stop"]
  - [ ] ...
- [ ] Create graphics
  - [ ] Learn how [bitmap graphics](https://stackoverflow.com/questions/55877790/wxwidgets-best-control-for-drawing-realtime-graphics) works in wxWidgets
  - [ ] Draw the floor
  - [ ] Create crawler's body
    - [ ] Create a function Body::walk() where the crawler walks automatically; for reference – [this repo](https://github.com/rwwaskk/CS188-Berkeley/blob/master/reinforcement/crawler.py)
- [ ] Perfectionist's list:
  - [ ] Automatically adjust width & height of the bitmap subwindow on main window resize

## References

- CS188 Reinforcement Learning lecture
  - [Main](https://www.youtube.com/watch?v=TiXS7vROBEg&t=775s)
  - [Auxiliary](https://www.youtube.com/watch?v=aTcIQWMPmJY&t=607s&ab_channel=CS188)
- [The GUI of inspiration](https://www.youtube.com/watch?v=PBjVn5OWK0k)
- [GitHub reference repo](https://github.com/rwwaskk/CS188-Berkeley/blob/master/reinforcement/crawler.py)
