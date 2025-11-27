#include "Console/Debug.h"

std::ofstream Debug::debugBuffer;

Debug::Debug()
{
    debugBuffer.open("debug.tmp");
}

Debug& Debug::Get()
{
    static Debug instance;
    return instance;
}

void Debug::Log(const std::string& msg)
{
    Get();                             
    debugBuffer << msg << std::endl;
    debugBuffer.flush();              
}

void Debug::Kill()
{
    Log("-0xKILL");
}
