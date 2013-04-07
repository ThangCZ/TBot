#ifndef BOT_H_INCLUDED
#define BOT_H_INCLUDED

#include <map>
#include <vector>
#include <functional>
#include "connection.h"

namespace TBot
{
    class Bot
    {

    private:
        std::vector<std::function<void (const std::vector<std::string>&)>> read_handlers;
        std::map<std::string, std::string> configmap;
        Connection conn;
        void Pass(const std::string&);
        void Nick(const std::string&);
        void Join(const std::string&);
        void Message(const std::string&, const std::string&);

    public:
        Bot(const std::string&);
        void AddReadHandler(std::function<void (const std::vector<std::string>&)>);
        void ReadHandler(const std::vector<std::string>&);
        void Loop();
        void AddNewUser(const std::string&, bool = false);
        void BasicWrite(const std::string&);
        std::vector<User*> user_holder;
        //void Join();
        void HandlerUserMesssage(User*, std::string&);

    };
}


#endif // BOT_H_INCLUDED
