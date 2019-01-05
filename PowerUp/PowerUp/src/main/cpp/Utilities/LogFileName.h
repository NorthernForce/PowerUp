#ifndef LOGFILENAME_H
#define LOGFILENAME_H

#include <string>

std::string GetCurrentTime();
std::string GetLogFileName(const char* prefix, const char* postfix = nullptr);

#endif
