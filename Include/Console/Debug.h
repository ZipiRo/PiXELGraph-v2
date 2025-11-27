#pragma once
#include <fstream>
#include <string>

class Debug
{
private:
    Debug();  
    static std::ofstream debugBuffer;

public:
    Debug(const Debug&) = delete;
    Debug& operator=(const Debug&) = delete;

    static Debug& GetInstance();
    static void Log(const std::string& msg);
    static void Kill();
    static void Errors();
};
