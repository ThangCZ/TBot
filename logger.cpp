#include "logger.h"
#include <iostream>
#include <chrono>
#include <string>

namespace TBot
{
    void Logger::Log(const std::string & type, const std::string & message)
    {
        char endofit = (message.back() == '\n') ?  '\0' : '\n';
        std::time_t timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::string timestr = std::ctime(&timenow);
        std::cout << timestr.substr(0, timestr.length()-1)  << " [" << type << "] : " << message << endofit;
    }
}
