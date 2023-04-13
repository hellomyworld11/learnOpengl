#include "OpenglDemo1_2.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

COpenglDemo1_2::COpenglDemo1_2()
{
}


COpenglDemo1_2::~COpenglDemo1_2()
{
}

void COpenglDemo1_2::glfwInit_all()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //核心模式
}

GLFWwindow * COpenglDemo1_2::glfwCreateWin(int w, int h)
{
	GLFWwindow *window = glfwCreateWindow(w, h, "LearnOpenGl", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "failed to create glfw window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}
	glViewport(0, 0, 800, 600);  //设置视口

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}


void COpenglDemo1_2::processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

unsigned int COpenglDemo1_2::createShader()
{
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
	return shaderProgram;
}

unsigned int COpenglDemo1_2::createShaderbyColor(double r, double g, double b)
{
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	gl_PointSize = 20.0f;\n"
		"}\0";

	char fragmentShaderSource[256] = { 0 };
	sprintf_s(fragmentShaderSource, "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(%f, %f, %f, 1.0f);\n"
		"}\0", r, g, b);
	const char *p = fragmentShaderSource;
	//创建顶点着色器 - 编译
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//创建片段着色器 - 编译
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &p, NULL);
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
	return shaderProgram;
}

void COpenglDemo1_2::render_trangle()
{
	glfwInit_all();
	GLFWwindow *window = glfwCreateWin();

	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	gl_PointSize = 20.0f;\n"
		"}\0";

	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = ourColor;\n"
		"}\0";


	//定义顶点数据
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};
	//顶点数据给 顶点着色器
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

	while (!glfwWindowShouldClose(window))
	{
		//处理键盘输入
		processInput(window);

		// 3. 绘制物体
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//使用着色器程序，
		glUseProgram(shaderProgram);

		//更新uniform 颜色
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;  //至少为0
		int vertexColorlocation = glGetUniformLocation(shaderProgram,"ourColor");
		glUniform4f(vertexColorlocation,0.0f,greenValue,0.0f,1.0f); //设置

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	
		//刷新帧缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	//退出flfw
	glfwTerminate();
}

void COpenglDemo1_2::reader_trangle_posColor()
{
	glfwInit_all();
	GLFWwindow *window = glfwCreateWin();

	const char *vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"    //位置变量属性位置值为0
		"layout (location = 1) in vec3 aColor;\n"  //颜色变量属性位置值为1
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"	ourColor = aColor;\n"
		"}\0";

	const char *fragmentShaderSource = 
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n" //顶点着色器的输出作为 片段着色器的输入
		"void main()\n"
		"{\n"
		"	FragColor = vec4(ourColor,1.0);\n"   
		"}\0";

	//定义顶点数据
	float vertices[] = {
		//位置					//颜色
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
	};
	//顶点数据给 顶点着色器
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

	unsigned int VBO;
	glGenBuffers(1, &VBO);  //生成顶点缓冲区对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); //顶点数组
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 1. 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);  //解绑
	glBindVertexArray(0);

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
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//刷新帧缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	//退出flfw
	glfwTerminate();
}

void COpenglDemo1_2::render_test_Shader()
{
	glfwInit_all();
	GLFWwindow *window = glfwCreateWin();

	
	//定义顶点数据
	float vertices[] = {
		//位置					//颜色
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
	};
	
	Shader ourShader("F:\\mycode\\sourceCC++\\learnOpengl\\x64\\Release\\shader.vs","F:\\mycode\\sourceCC++\\learnOpengl\\x64\\Release\\shader.fs");

	unsigned int VBO;
	glGenBuffers(1, &VBO);  //生成顶点缓冲区对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); //顶点数组
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 1. 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);  //解绑
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		//处理键盘输入
		processInput(window);

		// 3. 绘制物体
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//使用着色器程序，
		ourShader.use();
		//ourShader.setFloat("someUniform", 1.0f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//刷新帧缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//退出flfw
	glfwTerminate();
}

void COpenglDemo1_2::reverse_trangle()
{
	glfwInit_all();
	GLFWwindow *window = glfwCreateWin();

	const char *vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"    //位置变量属性位置值为0
		"layout (location = 1) in vec3 aColor;\n"  //颜色变量属性位置值为1
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x,-aPos.y,aPos.z, 1.0);\n"
		"	ourColor = aColor;\n"
		"}\0";

	const char *fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n" //顶点着色器的输出作为 片段着色器的输入
		"void main()\n"
		"{\n"
		"	FragColor = vec4(ourColor,1.0);\n"
		"}\0";

	//定义顶点数据
	float vertices[] = {
		//位置					//颜色
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
	};
	//顶点数据给 顶点着色器
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

	unsigned int VBO;
	glGenBuffers(1, &VBO);  //生成顶点缓冲区对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); //顶点数组
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 1. 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);  //解绑
	glBindVertexArray(0);

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
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//刷新帧缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	//退出flfw
	glfwTerminate();
}

void COpenglDemo1_2::move_trangle_pos()
{
	glfwInit_all();
	GLFWwindow *window = glfwCreateWin();

	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform vec4 ourPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x+ourPos.x,aPos.y+ourPos.y,aPos.z+ourPos.z,1.0f);\n"
		"	gl_PointSize = 20.0f;\n"
		"}\0";

	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = ourColor;\n"
		"}\0";


	//定义顶点数据
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};
	//顶点数据给 顶点着色器
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
	double d = 0.0f;
	while (!glfwWindowShouldClose(window))
	{
		//处理键盘输入
		processInput(window);

		// 3. 绘制物体
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//使用着色器程序，
		glUseProgram(shaderProgram);

		//更新uniform 颜色
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;  //至少为0
		int vertexColorlocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorlocation, 0.0f, greenValue, 0.0f, 1.0f); //设置
		//更新 uniform 位置
		int vertexPoslocation = glGetUniformLocation(shaderProgram, "ourPos");
		d += 0.00001f;
		glUniform4f(vertexPoslocation, d, 0.5f, 0.0f, 1.0f); //设置

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//刷新帧缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	//退出flfw
	glfwTerminate();
}

void COpenglDemo1_2::shader_color_same()
{
	glfwInit_all();
	GLFWwindow *window = glfwCreateWin();

	const char *vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"    //位置变量属性位置值为0
		"layout (location = 1) in vec3 aColor;\n"  //颜色变量属性位置值为1
		"out vec3 ourPosition;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"	ourPosition = aPos;\n"
		"}\0";

	const char *fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourPosition;\n" //顶点着色器的输出作为 片段着色器的输入
		"void main()\n"
		"{\n"
		"	FragColor = vec4(ourPosition,1.0);\n"
		"}\0";

	//定义顶点数据
	float vertices[] = {
		//位置					//颜色
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
	};
	//顶点数据给 顶点着色器
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

	unsigned int VBO;
	glGenBuffers(1, &VBO);  //生成顶点缓冲区对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); //顶点数组
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 1. 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);  //解绑
	glBindVertexArray(0);

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
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//刷新帧缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	//退出flfw
	glfwTerminate();
}
