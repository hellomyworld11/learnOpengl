#pragma once
#include <glad/glad.h>   //用来方便调用opengl的函数  必须放在最前面
#include <GLFW/glfw3.h> //方便开发
#include <iostream>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow *window);


//1.OpenGL创建窗口 
int openglWidet_main();