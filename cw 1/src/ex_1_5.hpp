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

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// ! Macierz translation jest definiowana wierszowo dla poprawy czytelnosci. OpenGL i GLM domyslnie stosuje macierze kolumnowe, dlatego musimy ja transponowac !
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	glm::mat4 rotation =
	{ cos(time),- sin(time),0,0,
	  sin(time),cos(time),0,0,
	  0,0,1,0,
	  0,0,0,1 };
	rotation = glm::transpose(rotation);
	glm::mat4 translation =
	{ 1,0,0,0,
	  0,1,0,sin(time) * 0.5f,
	  0,0,1,0,
	  0,0,0,1 };
	translation = glm::transpose(translation);

	// ZADANIE: Narysuj dwa czworokaty, jeden ruszajacy sie, drugi obracajacy sie 
	// Do rysowania ruszajacego sie czworokatu mozesz uzyc kodu z poprzedniego zadania, zmodyfikuj tylko macierz translacji, zeby byly obok siebie, nie jeden na drugim
	// Uzyj zmiennej "time" do zdefiniowania takiej macierzy rotacji, aby czworokat obracal sie wokol srodka (znajdz odpowiednia macierz 4x4 w internecie)
	// Kat obrotu podajemy w radianach

	glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&translation);

	Core::drawVAOIndexed(quadVAO, 16);

	glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&rotation);

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