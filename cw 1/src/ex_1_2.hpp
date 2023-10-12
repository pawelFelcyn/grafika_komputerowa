﻿#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"

GLuint program; // Shader ID

GLuint triangleVAO;

Core::Shader_Loader shaderLoader;
void prepareTriangle();

void renderScene(GLFWwindow* window)
{
    glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Aktywowanie shadera
    glUseProgram(program);

    //wywolaj funkcje Core::drawVAO z render utils z parametrem wejściowym GLuint triangleVAO 
    Core::drawVAO(triangleVAO, 12);
    // Wylaczenie shadera
    glUseProgram(0);

    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init(GLFWwindow* window) {
    prepareTriangle();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    program = shaderLoader.CreateProgram("shaders/shader_1_1.vert", "shaders/shader_1_1.frag");

    //stworz tablice wierzcholkow i zaladuj je do GPU za pomoca funkcji initVAO, wynik zapisz w triangleVAO
}

void prepareTriangle()
{
    float points[12] = { -0.5f, -0.5f, 0.0f, 1.0f,  0.5f, 0.5f, 0.0f, 1.0f, 0.7f, 0.0f, 0.0f, 1.0f };
    triangleVAO = Core::initVAO(points ,3, 4);
}

void shutdown(GLFWwindow* window)
{
    shaderLoader.DeleteProgram(program);
}


//obsluga wejscia
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// funkcja jest glowna petla
void renderLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        renderScene(window);
        glfwPollEvents();
    }
}   
//}