#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

class COpenglDemo1_6
{
public:
	COpenglDemo1_6();
	~COpenglDemo1_6();
	void glfwInit_all();
	GLFWwindow * glfwCreateWin(int w = 800, int h = 600);
	void processInput(GLFWwindow * window);
	void processInputFree(GLFWwindow *window, float deltaTime,glm::vec3& cameraPos,
		glm::vec3& cameraFront, glm::vec3& cameraUp );
	unsigned int createShader();
public:
	void camera_lookat();
	//自由相机 W S A D
	void camera_free();
	//鼠标和键盘控制相机lookat 
	void camera_mouse();
};

