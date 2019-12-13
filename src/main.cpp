#include <iostream>


#include <GL/glew.h>
#include <glm/glm.hpp>

#define SDL_HANDLED_MAIN
#include <SDL.h>


#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
    std::cout << "Hello world!" << std::endl;

    auto window = SDL_CreateWindow("Hi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 100, 100, SDL_WINDOW_OPENGL);

    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}
