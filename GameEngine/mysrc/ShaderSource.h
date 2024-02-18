//
// Created by captain on 2021/3/25.
//

#ifndef UNTITLED_SHADERSOURCE_H
#define UNTITLED_SHADERSOURCE_H

//顶点着色器代码
static const char* vertex_shader_text =
        "#version 330 core\n"

        "uniform mat4 u_mvp;\n"

        "attribute  vec3 a_pos;\n"
        "attribute  vec4 a_color;\n"

        "varying vec4 v_color;\n"

        "void main()\n"
        "{\n"
        "    gl_Position = u_mvp * vec4(a_pos, 1.0);\n"
        "    v_color = a_color;\n"
        "}\n";
//片段着色器代码
static const char* fragment_shader_text =
        "#version 330\n"
        "varying vec4 v_color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = v_color;\n"
        "}\n";


static const glm::vec3 kPositions_cube[36] = {
	//Front
	glm::vec3(-1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	//back
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f),
	//left
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f),
	//right
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	//up
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f),
	//down
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, 1.0f),
};

static const glm::vec4 kColors_cube[36] = {
	//Front
	glm::vec4(1, 0, 0, 1),
	glm::vec4(1, 0, 0, 1),
	glm::vec4(1, 0, 0, 1),
	glm::vec4(1, 0, 0, 1),
	glm::vec4(1, 0, 0, 1),
	glm::vec4(1, 0, 0, 1),
	//back
	glm::vec4(1, 0, 0, 1),
	glm::vec4(1, 0, 0, 1),
	glm::vec4(1, 0, 0, 1),
	glm::vec4(1, 0, 0, 1),
	glm::vec4(1, 0, 0, 1),
	glm::vec4(1, 0, 0, 1),
	//left
	glm::vec4(0, 1, 0, 1),
	glm::vec4(0, 1, 0, 1),
	glm::vec4(0, 1, 0, 1),
	glm::vec4(0, 1, 0, 1),
	glm::vec4(0, 1, 0, 1),
	glm::vec4(0, 1, 0, 1),
	//right
	glm::vec4(0, 1, 0, 1),
	glm::vec4(0, 1, 0, 1),
	glm::vec4(0, 1, 0, 1),
	glm::vec4(0, 1, 0, 1),
	glm::vec4(0, 1, 0, 1),
	glm::vec4(0, 1, 0, 1),
	//up
	glm::vec4(0, 0, 1, 1),
	glm::vec4(0, 0, 1, 1),
	glm::vec4(0, 0, 1, 1),
	glm::vec4(0, 0, 1, 1),
	glm::vec4(0, 0, 1, 1),
	glm::vec4(0, 0, 1, 1),
	//down
	glm::vec4(0, 0, 1, 1),
	glm::vec4(0, 0, 1, 1),
	glm::vec4(0, 0, 1, 1),
	glm::vec4(0, 0, 1, 1),
	glm::vec4(0, 0, 1, 1),
	glm::vec4(0, 0, 1, 1),
};


#endif //UNTITLED_SHADERSOURCE_H
