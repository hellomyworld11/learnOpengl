#pragma once
#include <glad/glad.h>   //�����������opengl�ĺ���  ���������ǰ��
#include <GLFW/glfw3.h> //���㿪��
#include <iostream>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow *window);


//1.OpenGL�������� 
int openglWidet_main();