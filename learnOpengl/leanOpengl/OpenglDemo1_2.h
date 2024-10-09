#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"

//��ɫ��
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
	//1_2_1 ����uniform
	void render_trangle();
	//1_2_2 ��������  λ��+��ɫ
	void reader_trangle_posColor();
	//1_2_3  ����Shader��
	void render_test_Shader();
	//excersise
	//1_2_1 �ߵ�������
	void reverse_trangle();
	void move_trangle_pos();
	void shader_color_same();
};

