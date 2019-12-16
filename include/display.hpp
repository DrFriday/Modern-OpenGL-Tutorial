#pragma once

#include "SDL.h"

class display
{
  public:
    display(int width, int height, const char* title);
    ~display();

  private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
};