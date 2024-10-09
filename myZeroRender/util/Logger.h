#pragma once
#include <iostream>
#include <string>

class Logger
{
public:
	enum class Level
	{
		Info,
		Error
	};
	
	static  Logger& GetInstance()
	{
		Logger logger;
		return logger;
	}

	void Log(std::string file, std::string fun, int line, Level level, std::string fmt, ...);

private:
	Logger();

	~Logger();

};


#define LOG(fmt, ...) Logger::GetInstance().Log(__FILE__, __FUNCTION__, __LINE__, Logger::Level::Info, fmt, __VA_ARGS__)