#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"

//着色器
class COpenglDemo1_2
{
public:
	COpenglDemo1_2();
	~COpenglDemo1_2();
	void glfwInit_all();
	GLFWwindow * glfwCreateWin(int w = 800, int h = 600);
	void processInput(GLFWwindow * window);
	unsigned int createShader();
	unsigned int createShaderbyColor(double r, double g, double b);
public:
	//1_2_1 测试uniform
	void render_trangle();
	//1_2_2 顶点属性  位置+颜色
	void reader_trangle_posColor();
	//1_2_3  测试Shader类
	void render_test_Shader();
	//excersise
	//1_2_1 颠倒三角形
	void reverse_trangle();
	void move_trangle_pos();
	void shader_color_same();
};

