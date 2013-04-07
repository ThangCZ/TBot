#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#include "logger.h"
#include "user.h"
#include <boost/asio.hpp>
#include <vector>
#include <functional>
#include <string>
#include <array>

namespace TBot
{
    class Connection
    {
    private:
        std::string addr;
        std::string port;

        boost::asio::io_service io_service;
        boost::asio::ip::tcp::socket socket;

        std::function<void (const std::vector<std::string>&)> read_handler;

        std::array<char, 8192> buffer;




    public:
        Connection() : socket(io_service) { /* Empty body */ }
        void Connect(const std::string&, const std::string&);
        void Run();
        void SetReadHandler(const std::function<void(const std::vector<std::string>&)>&);
        bool IsAlive();
        void Close();
        void Read(const boost::system::error_code&, std::size_t);
        void Write(const std::string&);



    };
}

#endif // CONNECTION_H_INCLUDED
