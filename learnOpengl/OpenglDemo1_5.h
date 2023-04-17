#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

//cys
// model - > view -> projection
class COpenglDemo1_5
{
public:
	COpenglDemo1_5();
	~COpenglDemo1_5();
	void glfwInit_all();
	GLFWwindow * glfwCreateWin(int w = 800, int h = 600);
	void processInput(GLFWwindow * window);
	unsigned int createShader();
public:
	void render_3D();
	void render_3D_rodate();
	void render_3D_10rodate();
};

