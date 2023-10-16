#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"

GLuint program; // Shader ID

GLuint quadVAO;

Core::Shader_Loader shaderLoader;


void renderScene(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Zmienna "time" przechowuje czas ktory uplynal od uruchomienia aplikacji
	float time = glfwGetTime();

    glUseProgram(program);
    
    // ZADANIE: Wyswietl czworokat, ktory jednoczesnie przesuwa sie i obraca.
    glm::mat4 goToMiddle =
    { 1,0,0,0.5f,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1 };
    glm::mat4 rotation =
    { cos(time),-sin(time),0,0,
      sin(time),cos(time),0,0,
      0,0,1,0,
      0,0,0,1 };
    glm::mat4 goBack =
    { 1,0,0,-0.5f,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1 };
    glm::mat4 translation =
    { 1,0,0,0,
      0,1,0,sin(time) * 0.5f,
      0,0,1,0,
      0,0,0,1 };
    glm::mat4 ultimateMatrix = transpose(goToMiddle * rotation * goBack * translation);
    glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&ultimateMatrix);

    Core::drawVAOIndexed(quadVAO, 16);

    glUseProgram(0);

    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    program = shaderLoader.CreateProgram("shaders/shader_1_2.vert", "shaders/shader_1_2.frag");

    float points[16] = { -0.75f, 0.25f, 0.0f, 1.0f,
        -0.75f, -0.25f, 0.0f, 1.0f,
        -0.25f, 0.25f, 0.0f, 1.0f,
        -0.25f, -0.25f, 0.0f, 1.0f };
    unsigned int indexes[6] = { 0, 1, 2, 1, 2, 3 };
    quadVAO = Core::initVAOIndexed(points, indexes, 4, 4, 6);
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