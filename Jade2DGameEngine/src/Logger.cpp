#include "Logger.h"
#include <iostream>
#include <ctime>


void Logger::Log( const std::string& message ) {
    // Get the current time in seconds since January 1, 1970
    time_t now = time(0);

    // Convert the time to a string
    char* date_time = ctime(&now);

    // Print the current date and time
    std::cout << date_time << message << std::endl;
}

void Logger::Err( const std::string& message ) {
    // Get the current time in seconds since January 1, 1970
    time_t now = time(0);

    // Convert the time to a string
    char* date_time = ctime(&now);

    // Print the current date and time
    std::cout << date_time << message << std::endl;
}
