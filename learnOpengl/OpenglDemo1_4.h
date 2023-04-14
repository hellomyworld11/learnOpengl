#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

class COpenglDemo1_4
{
public:
	COpenglDemo1_4();
	~COpenglDemo1_4();
	void glfwInit_all();
	GLFWwindow * glfwCreateWin(int w = 800, int h = 600);
	void processInput(GLFWwindow * window);
	unsigned int createShader();
public:
	void test_glm();
	void render_texture_translate();
	void render_translate_1_4_2();
};

