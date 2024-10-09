#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


//1.1 ÄãºÃ£¬Èý½ÇÐÎ
class COpenglDemo
{
public:
	COpenglDemo();
	~COpenglDemo();
	void glfwInit_all();
	GLFWwindow * glfwCreateWin(int w = 800,int h = 600);
	void processInput(GLFWwindow * window);
	unsigned int createShader();
	unsigned int createShaderbyColor(double r,double g,double b);
public:
	void render_trangle();
	void render_rectangle();
	void render_two_trangle();
	void render_two_trangle_sameVboVao();
};

