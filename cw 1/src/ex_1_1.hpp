#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"

float randomFloat();
int randomInt(int a, int b);
float randomFloat(int a, int b);
void setRandomBackground(GLFWwindow* window);

// funkcja renderujaca scene    
void renderScene(GLFWwindow* window)
{
    setRandomBackground(window);

    glfwSwapBuffers(window);
}

void setRandomBackground(GLFWwindow* window)
{
    float randomRed = randomFloat(0, 1);
    float randomGreen = randomFloat(0, 1);
    float randomBlue = randomFloat(0, 1);

    // ZADANIE: Przesledz kod i komentarze
    // ZADANIE: Zmien kolor tla sceny, przyjmujac zmiennoprzecinkowy standard RGBA
    glClearColor(randomRed, randomGreen, randomBlue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

float randomFloat()
{
    return (float)(rand()) / (float)(RAND_MAX);
}

int randomInt(int a, int b)
{
    if (a > b)
        return randomInt(b, a);
    if (a == b)
        return a;
    return a + (rand() % (b - a));
}

float randomFloat(int a, int b)
{
    if (a > b)
        return randomFloat(b, a);
    if (a == b)
        return a;

    return (float)randomInt(a, b) + randomFloat();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init(GLFWwindow* window) {

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void shutdown(GLFWwindow* window)
{
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