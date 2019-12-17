#include "display.hpp"
#include "Shader.hpp"
#include <iostream>

#include <GL/glew.h>

int main(int argc, char** argv)
{
    std::cout << "Hello world!" << std::endl;

    auto display = Display(400, 400, "test");

    while (!display.isClosed())
    {
		display.clear(0, 0, 1, 1);
        display.update();
    }

    return 0;
}
