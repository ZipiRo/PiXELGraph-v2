#pragma once
#include <fstream>
#include <string>

class Debug
{
private:
    Debug() {};

    static std::ofstream debugBuffer;

public:
    static Debug &GetDebug();
    static void Log(std::string log);
};
