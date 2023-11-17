#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    if (glewInit() != GLEW_OK) {
        std::cout << "Error" << std::endl;
    }
    window.setActive(true);
    window.setVerticalSyncEnabled(true);
    sf::Clock clock;
    glViewport(0, 0, 800, 600);
    float vertices[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
     1.0f,  1.0f,
    -1.0f,  1.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;
    VertexBuffer vb(vertices, 4 * 2 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);
    
    Shader shader("res/shaders/Basic.shader");
    shader.Bind();

    shader.SetUniform2f("iResolution", 800.0f, 600.0f);
    shader.setUniform1f("iTime", 0);
    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.Unbind();

    Renderer renderer;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        renderer.Clear();
        sf::Time time = clock.getElapsedTime();
        shader.Bind();
        shader.SetUniform2f("iResolution", 640.0f, 360.0f);
        shader.setUniform1f("iTime", time.asSeconds());
        renderer.Draw(va, ib, shader);

        window.display();
    }
    return 0;
}