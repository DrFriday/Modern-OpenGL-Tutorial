#include "display.hpp"

#include <iostream>

#include <GL/glew.h>

int main(int argc, char** argv)
{
    std::cout << "Hello world!" << std::endl;

    auto disp = display(100, 100, "test");

    while (!disp.isClosed())
    {

		disp.clear(0, 0, 1, 1);
		disp.update();
    }

    return 0;
}
