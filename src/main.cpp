#include "Display.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

#include <GL/glew.h>
#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "Hello world!" << std::endl;

    Display display(400, 400, "test");

    Shader shader("../res/basicShader");

    // Vertex temp[] = {Vertex(glm::vec3(-0.5, -0.5, 0)),
    //                  Vertex(glm::vec3(0, 0.5, 0)),
    //                  Vertex(glm::vec3(0.5, -0.5, 0))};

    Triangle arrTest = {Vertex(glm::vec3(-0.5, -0.5, 0)),
                        Vertex(glm::vec3(0, 0.5, 0)),
                        Vertex(glm::vec3(0.5, -0.5, 0))};

    // auto mesh = Mesh(temp, sizeof(temp)/sizeof(temp[0])); // workds
    // auto mesh = Mesh(temp, 3); // workds

    auto mesh = Mesh(arrTest);

    while (!display.isClosed())
    {
        display.clear(0, 1, 0, 1);

        shader.bind();

        mesh.draw();

        display.update();
    }

    return 0;
}
