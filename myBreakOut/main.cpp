#include <glad/glad.h> //！glad的引用必须放在最前面
#include <GLFW/glfw3.h>
#include <iostream>
#include "Game.h"
#include "ResourceManager.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

Game Breakout(screen_width, screen_height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (0 < key && key < 1024)
	{
		if (GLFW_PRESS == action )
		{
			Breakout.setKey(key, true);
		}
		else if(GLFW_RELEASE == action){
			Breakout.setKey(key, false);
		}
	}
}

int main(int argc, char *argv[])
{
	GLFWwindow *window = nullptr;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);		//配置glfw,表示使用的opengl版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式
	glfwWindowHint(GLFW_RESIZABLE, false);

	window = glfwCreateWindow(screen_width, screen_height, "break out", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);  //需要放在gladloadglloader之前
	
	//初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glViewport(0, 0, screen_width, screen_height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Breakout.init();

	float deltaTime = 0.0f;
	float lastTime = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glfwPollEvents();

		Breakout.processInput(deltaTime);

		Breakout.update(deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Breakout.render();

		glfwSwapBuffers(window);
	}
	ResourceManager::clear();
	glfwTerminate();
	return 0;
}