#include "user.h"

namespace TBot
{
    void User::SetOp(bool op)
    {
        isop = op;
    }
    void User::SetOnline(bool online)
    {
        isonline = online;
    }
    bool User::IsOp()
    {
        return isop;
    }
    bool User::IsOnline()
    {
        return isonline;
    }
    std::string User::GetName()
    {
        return name;
    }
    unsigned int User::GetWarnings()
    {
        return warnings;
    }
    unsigned int User::IssueWarning()
    {
        warnings+=1;
        return warnings;
    }
    void User::ResetWarnings()
    {
        warnings = 0;
    }

}
