#include "Display.hpp"
#include "Shader.hpp"
#include <iostream>

#include <GL/glew.h>

int main(int argc, char** argv)
{
    std::cout << "Hello world!" << std::endl;

    auto display = Display(400, 400, "test");

	Shader shader("./res/basicShader");

    while (!display.isClosed())
    {
		display.clear(0, 0, 1, 1);
        shader.bind();

        display.update();
    }

    return 0;
}
