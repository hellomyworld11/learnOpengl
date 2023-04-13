#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {
public:
	//程序ID
	unsigned int ID;
	//构造器读取并后见着色器
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	//使用/激活程序
	void use();
	//uniform 
	void setBool(const std::string &name,bool value)const;
	void setInt(const std::string &name,int value)const;
	void setFloat(const std::string &name,float value)const;

	
};