#include "connection.h"
#include "logger.h"

#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <stdexcept>


namespace TBot
{
    void Connection::Connect(const std::string &addr, const std::string &port)
    {
        this->addr = addr;
        this->port = port;

        boost::asio::ip::tcp::resolver resolver (io_service);
        boost::asio::ip::tcp::resolver::query query (this->addr, this->port, boost::asio::ip::resolver_query_base::numeric_service);
        boost::system::error_code error = boost::asio::error::host_not_found;

        boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
        boost::asio::ip::tcp::resolver::iterator enditerator;

        while(iterator != enditerator)
        {
            if(!error)
                break;

            socket.close();
            Logger::Log("Info", "Connecting to: " + this->addr + ":" + this->port);

            socket.connect(*iterator++, error);

            if(error)
                Logger::Log("ERROR", error.message());
        }
        if(error)
            throw std::runtime_error(error.message());

        Logger::Log("Info","Connected");

    }
    void Connection::Run()
    {
        socket.async_read_some(boost::asio::buffer(buffer),
                               boost::bind(&Connection::Read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        io_service.run();

    }
    void Connection::SetReadHandler(const std::function<void (const std::vector<std::string>&)> &handler)
    {
        read_handler = handler;
    }
    bool Connection::IsAlive()
    {
        return socket.is_open();
    }
    void Connection::Close()
    {
        Logger::Log("Info", "Closing connection");
        socket.close();
        io_service.stop();
    }
    void Connection::Read(const boost::system::error_code& error, std::size_t count)
    {
        if(error)
        {
            std::cout << "Reading error " << error << std::endl;
            Close();
        }
        else
        {
            Logger::Log("Read", std::string(buffer.data(), count));
            std::vector<std::string> strvec;
            std::string tmpstr (buffer.data(), count);
            boost::split(strvec, tmpstr  , boost::is_any_of("\r\n"));
            read_handler(strvec);

            socket.async_read_some(boost::asio::buffer(buffer),
                               boost::bind(&Connection::Read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        }
    }
    void Connection::Write(const std::string &towrite)
    {
        Logger::Log("Write", towrite);
        boost::asio::write(socket, boost::asio::buffer(towrite+"\r\n"));
    }
}
