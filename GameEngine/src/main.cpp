#include <iostream>
#include <chrono>
#include <ctime>

#ifdef WIN32
#define __func__ __FUNCTION__
#endif

// This define must be before including "cpplog.hpp"
#define LOG_LEVEL(level, logger) CustomLogMessage(__FILE__, __func__, __LINE__, (level), logger).getStream()
#include "cpplog\cpplog.h"


#include "filewatcher\FileWatcher.h"

class CustomLogMessage : public cpplog::LogMessage
{
public:
	CustomLogMessage(const char* file, const char* function,
		unsigned int line, cpplog::loglevel_t logLevel,
		cpplog::BaseLogger &outputLogger)
		: cpplog::LogMessage(file, line, logLevel, outputLogger, false),
		m_function(function)
	{
		InitLogMessage();
	}

	static const char* shortLogLevelName(cpplog::loglevel_t logLevel)
	{
		switch (logLevel)
		{
		case LL_TRACE: return "TRACE";
		case LL_DEBUG: return "DEBUG";
		case LL_INFO:  return "INFO";
		case LL_WARN:  return "WARNING";
		case LL_ERROR: return "ERROR";
		case LL_FATAL: return "FATAL";
		default:       return "OTHER";
		};
	}

protected:
	virtual void InitLogMessage()
	{
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);

		m_logData->stream
			<< "["
			<< std::put_time(std::localtime(&now_c), "%F %T") << " "
			<< m_logData->fileName << ":"
			<< m_function << ":"
			<< m_logData->line
			<< "]["
			<< shortLogLevelName(m_logData->level)
			<< "] ";
	}
private:
	const char *m_function;
};

extern int Render();//Forward declare from RenderWindow.cpp cos I'm tired

int main()
{
	std::string filename = "C:\\Users\\Zulhairul\\Documents\\Visual Studio 2015\\Projects\\GameEngine\\GameEngine";

	int  i;
	WatchDirectory(filename.c_str());
	cpplog::StdErrLogger slog;
	LOG_WARN(slog) << "Custom log format.";

	Render();

	std::cin >> i;
	return 0;
}
