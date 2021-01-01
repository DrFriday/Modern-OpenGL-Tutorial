#pragma once

#include <SDL.h>

class Display
{
  public:
    Display(int width, int height, const char* title);
    ~Display();

    void update();

	bool isClosed() const;

	void clear(float r, float g, float b, float a) const;

    float getAspectRatio() const;

  private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    bool m_isClosed;
    int m_width;
    int m_height;
};