#include "Logger.h"
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

std::string CurrentDateTimeToString() {
    std::time_t now = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
    std::string output( 30, '\0' );
    std::strftime( &output[0], output.size(), "%d-%b-y %H:%M:%S", std::localtime( &now ) );
    return output;
}
void Logger::Log( const std::string& message ) {

    std::string output = "LOG: [" + CurrentDateTimeToString() + "]: " + message;

    // Print the current date and time
    std::cout << "\033[1;32m" << output << "\033[0m" << std::endl;
}

void Logger::Err( const std::string& message ) {

    std::string output = "ERR: [" + CurrentDateTimeToString() + "]: " + message;

    // Print the current date and time
    std::cout << "\033[1;31m" << output << "\033[0m" << std::endl;
}
