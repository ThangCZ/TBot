#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <string>

namespace TBot
{
    class Logger
    {
    public:
        static void Log(const std::string&, const std::string&);
    };
}


#endif // LOGGER_H_INCLUDED
