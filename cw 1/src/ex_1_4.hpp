#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include <cmath>
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

	// "translation" jest automatycznie zainicjalizowana macierza 4x4
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// ! Macierz translation jest definiowana wierszowo dla poprawy czytelnosci. OpenGL i GLM domyslnie stosuje macierze kolumnowe, dlatego musimy ja transponowac !
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	glm::mat4 translation =
	{ 1,0,0,0,
	  0,1,0,sin(time) * 0.5f,
	  0,0,1,0,
	  0,0,0,1 };
	translation = glm::transpose(translation);

	// ZADANIE: Narysuj ruszajacy sie czworokat
	//
	// Uzyj zmiennej "time" do zdefiniowania macierzy translacji w taki sposob, aby czworokat przesuwal sie w gore i w dol ekranu (wartosci wspolrzednej y powinny zmieniac sie pomiedzy -0.5 i 0.5)
	// Wykorzystaj funkcje sinus: sin(float x)

	// glUniformMatrix4fv przekazuje macierz "translation" do GPU i powiazuje ja w shaderze ze zmienna typu mat4 o nazwie "transformation"
	// Shader uzywa tej macierzy to transformacji wierzcholkow podczas renderowania
	glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&translation);

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