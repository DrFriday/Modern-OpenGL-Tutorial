#include "display.hpp"

display::display(int width, int height, const char* title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

	// Size is in bits
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);   // 2^8 power of red values
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // 2^8 power of green values
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);  // 2^8 power of blue values
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // Space for each pixel
    SDL_GL_SetAttribute(
        SDL_GL_DOUBLEBUFFER,
        1); // Allocate space for two windows, will only create one

    m_window =
        SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         width, height, SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);
}

display::~display() 
{
	SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);

	SDL_Quit();
}