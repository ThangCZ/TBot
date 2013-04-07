#include "bot.h"

#include <fstream>
#include <boost/algorithm/string.hpp>

namespace TBot
{
    Bot::Bot(const std::string &file_name)
    {
        std::ifstream file(file_name);
        std::string key, value;

        while(file >> key >> value)
            configmap[key] = value;

        conn.SetReadHandler([this](const std::vector<std::string> &m){ this->ReadHandler(m); });

        conn.Connect(configmap["SERVER_ADDRESS"], configmap["SERVER_PORT"]);
        Pass(configmap["PASSWORD"]);
        Nick(configmap["NAME"]);
        Join(configmap["CHANNEL_NAME"]);

    }

    void Bot::AddReadHandler(std::function<void (const std::vector<std::string>&)> func)
    {
        read_handlers.push_back(func);
    }

    void Bot::ReadHandler(const std::vector<std::string> &message)
    {
        for(auto i : read_handlers)
            i(message);
    }

    void Bot::Loop()
    {
        conn.Run();
    }
    void Bot::Pass(const std::string &pass)
    {
        conn.Write("PASS "+pass);
    }
    void Bot::Nick(const std::string &nick)
    {
        conn.Write("NICK "+nick);
        conn.Write("USER "+nick+" * * :"+nick);
    }
    void Bot::Join(const std::string &chan)
    {
        conn.Write("JOIN "+chan);
    }
    /*void Bot::Join()
    {
        conn.Write("JOIN "+configmap["CHANNEL_NAME"]);
    }*/
    void Bot::Message(const std::string &reciever, const std::string &message)
    {
        conn.Write("PRIVMSG " + reciever + " :" + message);
    }
    void Bot::BasicWrite(const std::string &message)
    {
        conn.Write(message);
    }
    void Bot::AddNewUser(const std::string &name, bool isop)
    {
        for(User* i : user_holder)
            if(boost::iequals(name, i->GetName()))
                return;
        //User newuser(name, isop);
        //user_holder.push_back(newuser);
        user_holder.push_back(new User(name, isop));
        Logger::Log("Info", "New user " + name + " was registered.");
    }
    void Bot::HandlerUserMesssage(User *user, std::string &message)
    {
        if(!std::any_of(message.begin(),message.end(), ::islower) /*&& !user.IsOp()*/)
        {
            unsigned int seconds = user->IssueWarning()*300;
            std::ostringstream stringstr;
            stringstr << ".timeout " << user->GetName() << " " << seconds;
            Message(configmap["CHANNEL_NAME"], stringstr.str());
            stringstr.str("");
            stringstr << user->GetName() << ": Don't use caps, please. Warning number " << user->GetWarnings() << " issued";
            Message(configmap["CHANNEL_NAME"], stringstr.str());
        }
    }
}
