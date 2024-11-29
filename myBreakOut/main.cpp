#include <glad/glad.h> //！glad的引用必须放在最前面
#include <GLFW/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


int main(int argc, char *argv[])
{
	GLFWwindow *window = nullptr;

	glfwInit();


	window = glfwCreateWindow(800, 600, "break out", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(-1);
	}

	//初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	glfwMakeContextCurrent(window);

//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}