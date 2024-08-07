#include "Logger.h"
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

std::vector<LogEntry> Logger::messages;


std::string CurrentDateTimeToString() {
    std::time_t now = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
    std::string output( 30, '\0' );
    std::strftime( &output[0], output.size(), "%d-%b-y %H:%M:%S", std::localtime( &now ) );
    return output;
}
void Logger::Log( const std::string& message ) {

    LogEntry logEntry;
    logEntry.type = LOG_INF;
    logEntry.message = "LOG: [" + CurrentDateTimeToString() + "]: " + message;

    std::cout << "\033[1;32m" << logEntry.message << "\033[0m" << std::endl;
    messages.push_back( logEntry );

}

void Logger::Err( const std::string& message ) {

    LogEntry logEntry;
    logEntry.type = LOG_ERR;
    logEntry.message = "ERR: [" + CurrentDateTimeToString() + "]: " + message;

    std::cerr << "\033[1;31m" << logEntry.message << "\033[0m" << std::endl;
    messages.push_back( logEntry );
}
