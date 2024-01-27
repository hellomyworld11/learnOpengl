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

//������ɫ������
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
	//***�̶�����*****************************************
	glfwInit();	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);   //���汾3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	 //�ΰ汾3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //����ģʽ

	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGl", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "failed to create glfw window" << std::endl;
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(window);   //�������������óɵ�ǰ�̵߳�������

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  //glad ��װ�˻�ȡ����ָ��Ĺ��̣�����ʹ��opengl����
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return ;
	}
	glViewport(0, 0, 800, 600);  //�����ӿ�

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //�ӿ��洰�ڱ仯���仯
	//****************************************************


	//���嶥������
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

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

	//--//   ׼����������
	unsigned int VBO;
	glGenBuffers(1, &VBO);  //���ɶ��㻺��������
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); //��������
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 1. ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);  //���
	glBindVertexArray(0);

	glBindVertexArray(VAO);

	glEnable(GL_PROGRAM_POINT_SIZE);
	while (!glfwWindowShouldClose(window))
	{
		//�����������
		processInput(window);

		// 3. ��������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //���������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT);		 //�����ɫ����
		//ʹ����ɫ������
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glDrawArrays(GL_POINTS, 0, 3);
		//ˢ��֡����
		glfwSwapBuffers(window);   //������ɫ����
		glfwPollEvents();  //��� �¼�(���̣�����)
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//�˳�flfw
	glfwTerminate(); //�ͷ���Դ
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
	glViewport(0, 0, width / 2, height / 2);
}

