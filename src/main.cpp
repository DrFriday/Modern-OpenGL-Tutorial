#include "Display.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Camera.hpp"

#include <GL/glew.h>
#include <iostream>
#include <chrono>
#include <thread>

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

    Camera camera(glm::vec3(0, 0, -3), 70, display.getAspectRatio(), 0.01f, 1000.0f);

    float counter {};

    while (!display.isClosed())
    {
        display.clear(0, 1, 0, 1);

        transform.getPosition().x = sinf(counter);
        transform.getPosition().z = cosf(counter);
        transform.getRotation().x = sinf(counter);
        transform.getRotation().y = sinf(counter);
        transform.getRotation().x = sinf(counter);
//        transform.getScale().x = sinf(counter) * 2;

        shader.bind();
        shader.update(transform, camera);

        texture.bind(0);

        mesh.draw();

        display.update();

        counter += 0.01f;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000/30));
    }

    return 0;
}
