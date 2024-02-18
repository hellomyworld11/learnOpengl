//
// Created by captain on 2021/3/25.
// 顶点坐标 顶点颜色
//

#ifndef UNTITLED_VERTEXDATA_H
#define UNTITLED_VERTEXDATA_H

#include <glm/glm.hpp>


static const glm::vec3 kPositions[3] = {
        glm::vec3{ -1.0f, -1.0f,0.0f},
        glm::vec3{  1.0f, -1.0f,0.0f},
        glm::vec3{   0.f,  1.0f,0.0f}
};

static const glm::vec4 kColors[3] = {
        glm::vec4{ 1.f, 0.f, 0.f ,1.f},
        glm::vec4{ 0.f, 1.f, 0.f ,1.f},
        glm::vec4{ 0.f, 0.f, 1.f ,1.f}
};



static const glm::vec3 kPositions_rectangle[6] = {
	//第一个三角形
	{ -1.0f, -1.0f,0.0f },//左下
	{ 1.0f, -1.0f,0.0f },//右下
	{ 1.0f,  1.0f,0.0f },//右上
						 //第二个三角形
	{ 1.0f,  1.0f,0.0f },//右上
	{ -1.0f,  1.0f,0.0f },//左上
	{ -1.0f, -1.0f,0.0f } //左下
};

static const glm::vec4 kColors_rectangle[6] = {
	//第一个三角形颜色
	{ 1.f, 0.f, 0.f ,1.f },//左下
	{ 0.f, 1.f, 0.f ,1.f },//右下
	{ 0.f, 0.f, 1.f ,1.f },//右上
						   //第二个三角形颜色
	{ 0.f, 0.f, 1.f ,1.f },//右上
	{ 1.f, 0.f, 0.f ,1.f },//左上
	{ 1.f, 0.f, 0.f ,1.f } //左下
};


#endif //UNTITLED_VERTEXDATA_H
