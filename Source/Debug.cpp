#include "Console/Debug.h"

std::ofstream Debug::debugBuffer;

Debug::Debug()
{
    debugBuffer.open("debug.tmp");
}

Debug& Debug::GetInstance()
{
    static Debug instance;
    return instance;
}

void Debug::Log(const std::string& msg)
{
    GetInstance();                             
    debugBuffer << msg << std::endl;
    debugBuffer.flush();              
}

void Debug::Kill()
{
    Log("-0xKILL");
}
