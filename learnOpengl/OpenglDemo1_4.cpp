#include "OpenglDemo1_4.h"


static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

COpenglDemo1_4::COpenglDemo1_4()
{
}


COpenglDemo1_4::~COpenglDemo1_4()
{
}

void COpenglDemo1_4::glfwInit_all()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //核心模式
}

GLFWwindow * COpenglDemo1_4::glfwCreateWin(int w, int h)
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


void COpenglDemo1_4::processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

unsigned int COpenglDemo1_4::createShader()
{
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"  //顶点属性位置 0
		"layout(location = 1) in vec3 aColor;\n"
		"layout(location = 2) in vec2 aTexCoord;\n" //输入纹理坐标
		"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"  //输出纹理坐标
		"uniform mat4 transform;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"   ourColor = aColor;\n"
		"	TexCoord = vec2(aTexCoord.x,1.0 - aTexCoord.y);\n"
		"}\0";

	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D ourTexture;\n"
		"void main()\n"
		"{\n"
		"	FragColor = texture(ourTexture,TexCoord);\n" //指定采样器和纹理坐标
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


void COpenglDemo1_4::test_glm()
{
	glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans*vec;
	for (int i = 0; i < trans.length(); i++)
	{
		glm::vec4 avec = trans[i];
		std::cout << "[" ;
		for (int j = 0; j < avec.length(); j++)
		{
			std::cout << trans[i][j] << ",";
		}
		std::cout << "]" << std::endl;
	}
	
	std::cout << "("<< vec.x<<"," << vec.y <<","<< vec.z <<")"<< std::endl;
	system("pause");
}

void COpenglDemo1_4::render_texture_translate()
{
	glfwInit_all();
	GLFWwindow *window = glfwCreateWin();

	unsigned int shaderProgram = createShader();

	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	//纹理坐标
	float texCoords[] = {
		0.0f,0.0f,
		1.0f,0.0f,
		0.5f,1.0f
	};

	unsigned int VBO;
	unsigned int EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// 1. 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);//绑定纹理，之后纹理设置都会针对这个纹理进行设置
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//加载图片
	int width, height, nrChannels;
	unsigned char *data = stbi_load("F:\\mycode\\sourceCC++\\learnOpengl\\test\\container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		//生成纹理
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height
			, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//生成多级渐远纹理
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//创建变换矩阵
	
	

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

		//一直旋转  先平移后旋转 和先旋转后平移结果不一样 ，两个旋转参考点不一致
		glm::mat4 trans;
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		

		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

void COpenglDemo1_4::render_translate_1_4_2()
{
	glfwInit_all();
	GLFWwindow *window = glfwCreateWin();

	unsigned int shaderProgram = createShader();

	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	//纹理坐标
	float texCoords[] = {
		0.0f,0.0f,
		1.0f,0.0f,
		0.5f,1.0f
	};

	unsigned int VBO;
	unsigned int EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// 1. 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);//绑定纹理，之后纹理设置都会针对这个纹理进行设置
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//加载图片
	int width, height, nrChannels;
	unsigned char *data = stbi_load("F:\\mycode\\sourceCC++\\learnOpengl\\test\\container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		//生成纹理
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height
			, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//生成多级渐远纹理
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//创建变换矩阵



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

		// 移动到左上角   并缩放
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(-1.0f, 1.0f, 0.0f));
		float timeValue = glfwGetTime();
		float scale = sin(timeValue) ;
		trans = glm::scale(trans, glm::vec3(scale, scale, scale));

		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
