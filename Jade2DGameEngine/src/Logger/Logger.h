#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

enum LogType {
	LOG_INF,
	LOG_WORNING,
	LOG_ERR
};

struct LogEntry {
	LogType type;
	std::string message;
};

class Logger {

public:
	static std::vector<LogEntry> messages;
	static void Log( const std::string& message );
	static void Err( const std::string& message );

};

#endif