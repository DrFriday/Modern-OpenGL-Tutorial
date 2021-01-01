#include "Display.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

#include <GL/glew.h>
#include <iostream>

int main(int argc, char** argv)
{
    Display display(400, 400, "test");

    Shader shader("../res/basicShader");

    Triangle arrTest = {Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
                        Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
                        Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0))};

    auto mesh = Mesh(arrTest);

    Texture texture("../res/bricks.jpg");

    Transform transform;

    while (!display.isClosed())
    {
        display.clear(0, 1, 0, 1);

        shader.bind();
        shader.update(transform);

        texture.bind(0);

        mesh.draw();

        display.update();
    }

    return 0;
}
