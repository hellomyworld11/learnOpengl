#pragma once


#include <glad/glad.h>   //�����������opengl�ĺ���
#include <GLFW/glfw3.h> //���㿪��
#include <iostream>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow *window);


//2.OpenGL����������
int openglTangle_main();

//opengl VAO VBO EBO ����
int openglTangle_test();
