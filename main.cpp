#include "bot.h"
#include "logger.h"
#include "user.h"

#include <iostream>
#include <boost/algorithm/string.hpp>


int main(int argc, char *argv[])
{
    try
    {
        TBot::Bot bot("config");
        bot.AddReadHandler([&bot](const std::vector<std::string> &m)
                           {
                               for(std::string i : m)
                               {
                                   if(i.compare(0,4,"PING") == 0)
                                       bot.BasicWrite("PONG" + i.substr(4));
                               }
                           });
        bot.AddReadHandler([&bot](const std::vector<std::string> &m)
                           {
                               for(std::string i : m)
                               {
                                   std::istringstream iss(i);
                                   std::string from, type;
                                   iss >> from >> type;
                                   /*if(type == "376")
                                       bot.Join();*/
                                   if(type == "353")
                                   {
                                       std::string waste, names;
                                       iss >> waste >> waste >> waste;
                                       std::getline(iss, names);
                                       names.erase(0,2);
                                       //TBot::Logger::Log("Debug", names);
                                       std::vector<std::string> namelist;
                                       boost::split(namelist, names, boost::is_any_of(" "));
                                       for(std::string name : namelist)
                                           bot.AddNewUser(name);
                                   }

                               }

                           });
        bot.AddReadHandler([&bot](const std::vector<std::string> &m)
                           {
                               for(std::string i : m)
                               {
                                   std::istringstream iss(i);
                                   std::string from, type;
                                   iss >> from >> type;
                                   if(type == "JOIN")
                                   {
                                        const std::string name = from.substr(1,from.find("!")-1);
                                       bot.AddNewUser(name);
                                   }
                                   if(type == "PART")
                                       for(TBot::User * user: bot.user_holder)
                                           if(boost::iequals(user->GetName(),from.substr(1,from.find("!")-1)))
                                                user->SetOnline(false);

                               }
                           });
        bot.AddReadHandler([&bot](const std::vector<std::string> &m)
                           {
                               for(std::string i : m)
                               {
                                   std::istringstream iss(i);
                                   std::string from, type;
                                   iss >> from >> type;
                                   if(type == "MODE")
                                   {
                                       std::string channel, mode, name;
                                       iss >> channel >> mode >> name;
                                       if(mode == "+o"|| mode == "-o")
                                       {
                                           bool isop = (mode == "+o") ? true : false;
                                           for(TBot::User* users : bot.user_holder)
                                           {
                                               if(boost::iequals(users->GetName(),name))
                                                {
                                                    users->SetOp(isop);
                                                    TBot::Logger::Log("Info", "Setting op of " + name);
                                                }
                                           }
                                       }
                                   }
                               }
                           });
        bot.AddReadHandler([&bot](const std::vector<std::string>&m)
                           {
                               for(std::string i : m)
                               {
                                   std::istringstream iss(i);
                                   std::string from, mode;
                                   iss >> from >> mode;
                                   if(mode == "PRIVMSG")
                                   {
                                       iss >> mode; //let's just get rid of the channel name, we won't use mode anymore
                                       std::string message;
                                       std::getline(iss, message);
                                       message.erase(0,2); // Remove first 2 characters which are " :"
                                       mode = from.substr(1,from.find("!")-1);
                                       for(TBot::User* users : bot.user_holder)
                                            if(boost::iequals(users->GetName(),mode))
                                                bot.HandlerUserMesssage(users, message);
                                   }
                               }
                           });
        bot.Loop();
    }
    catch (const std::exception& exc)
    {
        std::cout << exc.what() << std::endl;
    }
    return 0;
}
