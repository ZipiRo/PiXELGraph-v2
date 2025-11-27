#include <windows.h>
#include <string.h>

#include "Console/Debug.h"

std::ofstream Debug::debugBuffer;

Debug::Debug()
{
    wchar_t tempPath[MAX_PATH];
    GetTempPathW(MAX_PATH, tempPath);

    std::wstring file = std::wstring(tempPath) + L"debug.tmp";
    debugBuffer.open(file.c_str());
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

void Debug::Errors()
{
    Log("-0xERROR");
}
