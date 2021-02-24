#include "Camera.hpp"
#include "Display.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
    Display display(400, 400, "test");

    Shader shader("../res/basicShader");

    std::vector<Vertex> vertices = {Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
                                    Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
                                    Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0)),
                                    Vertex(glm::vec3(1, 0.5, 1), glm::vec2(0, 0))};

    std::vector<unsigned int> indices = {0, 1, 2, 1, 2, 3};

    auto mesh = Mesh(vertices, indices);
//    auto mesh = Mesh("../res/monkey3.obj");

    Texture texture("../res/bricks.jpg");

    Transform transform;

    Camera camera(glm::vec3(0, 0, -2), 70, display.getAspectRatio(), 0.01f, 1000.0f);

    float counter{};

    while (!display.isClosed())
    {
        Display::clear(0, 1, 0, 1);

//        transform.getPosition().x = sinf(counter);
//        transform.getPosition().z = cosf(counter);
//        transform.getRotation().x = sinf(counter);
//
//        transform.getRotation().x = sinf(counter);
//        transform.getRotation().x = sinf(45);
//        transform.getRotation().y = 0;
//        transform.getRotation().z = 0;

//        transform.getRotation().y = counter;

        shader.bind();
        shader.update(transform, camera);

        texture.bind(0);

        mesh.draw();

        display.update();

        counter += 0.01f;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30));
    }

    return 0;
}
