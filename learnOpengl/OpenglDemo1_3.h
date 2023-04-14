#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class COpenglDemo1_3
{
public:
	COpenglDemo1_3();
	~COpenglDemo1_3();
	void glfwInit_all();
	GLFWwindow * glfwCreateWin(int w = 800, int h = 600);
	void processInput(GLFWwindow * window);
	unsigned int createShader();
public:
	void render_texture();
};

