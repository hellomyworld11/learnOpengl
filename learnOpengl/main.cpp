#include "OpenglDemo.h"
#include "OpenglDemo1_2.h"
#include "OpenglDemo1_3.h"
#include "OpenglDemo1_4.h"
#include "OpenglDemo1_5.h"
#include "OpenglDemo1_6.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//顶点着色器代码
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	gl_PointSize = 20.0f;\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

void templateRender()
{
	//***固定代码*****************************************
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //核心模式

	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGl", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "failed to create glfw window" << std::endl;
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return ;
	}
	glViewport(0, 0, 800, 600);  //设置视口

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//****************************************************


	//定义顶点数据
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	//创建顶点着色器 - 编译
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//创建片段着色器 - 编译
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//创建着色器程序
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//删除着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//--//   准备顶点数据
	unsigned int VBO;
	glGenBuffers(1, &VBO);  //生成顶点缓冲区对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); //顶点数组
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 1. 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);  //解绑
	glBindVertexArray(0);

	glBindVertexArray(VAO);

	glEnable(GL_PROGRAM_POINT_SIZE);
	while (!glfwWindowShouldClose(window))
	{
		//处理键盘输入
		processInput(window);

		// 3. 绘制物体
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//使用着色器程序，
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glDrawArrays(GL_POINTS, 0, 3);
		//刷新帧缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//退出flfw
	glfwTerminate();
	return ;
}


int main()
{
	COpenglDemo1_6 aDemo;
	//aDemo.render_trangle();
	//aDemo.render_rectangle();
	aDemo.camera_mouse();
	return 0;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

