#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <string>

namespace TBot
{
    class User
    {
    private:
        std::string name;
        bool isop;
        unsigned int warnings;
        bool isonline;
    public:
        //User(std::string& newname) : name(newname), isop(false) {}
        User(const std::string& newname, bool &newop) : name(newname), isop(newop), warnings(0), isonline(1) {}
        void SetOp(bool);
        void SetOnline(bool);
        bool IsOp();
        bool IsOnline();
        std::string GetName();
        unsigned int GetWarnings();
        unsigned int IssueWarning();
        void ResetWarnings();
    };
}

#endif // USER_H_INCLUDED
