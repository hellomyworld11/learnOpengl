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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //����ģʽ
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
	glViewport(0, 0, 800, 600);  //�����ӿ�

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
		"layout (location = 0) in vec3 aPos;\n"  //��������λ�� 0
		"layout(location = 1) in vec3 aColor;\n"
		"layout(location = 2) in vec2 aTexCoord;\n" //������������
		"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"  //�����������
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
		"	FragColor = texture(ourTexture,TexCoord);\n" //ָ������������������
		"}\0";
	//����������ɫ�� - ����
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//����Ƭ����ɫ�� - ����
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//������ɫ������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//ɾ����ɫ������
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
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	//��������
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


	// 1. ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);//������֮���������ö��������������������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//����ͼƬ
	int width, height, nrChannels;
	unsigned char *data = stbi_load("F:\\mycode\\sourceCC++\\learnOpengl\\test\\container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		//��������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height
			, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//���ɶ༶��Զ����
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//�����任����
	
	

	glBindBuffer(GL_ARRAY_BUFFER, 0);  //���
	glBindVertexArray(0);
	while (!glfwWindowShouldClose(window))
	{
		//�����������
		processInput(window);

		// 3. ��������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//ʹ����ɫ������
		glUseProgram(shaderProgram);

		//һֱ��ת  ��ƽ�ƺ���ת ������ת��ƽ�ƽ����һ�� ��������ת�ο��㲻һ��
		glm::mat4 trans;
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		

		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//ˢ��֡����
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	//�˳�flfw
	glfwTerminate();
}

void COpenglDemo1_4::render_translate_1_4_2()
{
	glfwInit_all();
	GLFWwindow *window = glfwCreateWin();

	unsigned int shaderProgram = createShader();

	float vertices[] = {
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	//��������
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


	// 1. ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);//������֮���������ö��������������������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//����ͼƬ
	int width, height, nrChannels;
	unsigned char *data = stbi_load("F:\\mycode\\sourceCC++\\learnOpengl\\test\\container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		//��������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height
			, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//���ɶ༶��Զ����
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//�����任����



	glBindBuffer(GL_ARRAY_BUFFER, 0);  //���
	glBindVertexArray(0);
	while (!glfwWindowShouldClose(window))
	{
		//�����������
		processInput(window);

		// 3. ��������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//ʹ����ɫ������
		glUseProgram(shaderProgram);

		// �ƶ������Ͻ�   ������
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

		//ˢ��֡����
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	//�˳�flfw
	glfwTerminate();
}
