#include "Logger.h"
#include <stdarg.h>
#include <sstream>

void Logger::Log(std::string file, std::string fun, int line, Level level, std::string fmt, ...)
{
	std::string fullstr;
	va_list arg;
	std::stringstream fmtio;
	va_start(arg, fmt);

	char data[64];
	memset(data, 0, sizeof(data));
	vsprintf_s(data, fmt.c_str(), arg);
	fmtio << "{" << file << "}" << "{" << fun << "}" << "[" << line << "]" << " ==> " << data;
	fullstr = fmtio.str();
	va_end(arg);
	std::cout << fullstr << std::endl;
}

Logger::Logger()
{
}


Logger::~Logger()
{
}
