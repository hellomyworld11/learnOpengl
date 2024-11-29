#pragma once


#include <glad/glad.h>   //用来方便调用opengl的函数
#include <GLFW/glfw3.h> //方便开发
#include <iostream>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow *window);


//2.OpenGL绘制三角形
int openglTangle_main();

//opengl VAO VBO EBO 测试
int openglTangle_test();
