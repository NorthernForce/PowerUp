#include "LogFileName.h"
#include <ctime>

std::string GetCurrentTime()
{
	constexpr int bufferSize = 32;
	char buffer[bufferSize];
	const auto t = std::time(nullptr);
	std::strftime(buffer, bufferSize, "%F %T", std::localtime(&t));
	for(auto c = buffer; *c; ++c)
	{
		if(*c == ':')
		{
			*c = '-';
		}
	}
	return buffer;
}

std::string GetLogFileName(const char* prefix, const char* postfix)
{
	char path[200];
	const auto& time = GetCurrentTime();
	const char* format = postfix ? "/tmp/%s %s %s.csv" : "/tmp/%s %s.csv";
	sprintf(path, format, prefix, time.c_str(), postfix);
	return path;
}
