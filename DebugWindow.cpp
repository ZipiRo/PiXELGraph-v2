#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <thread>

int main()
{
    SetConsoleTitleW(L"PiXELGraph v2.0 | DebugWindow");

    std::ifstream debug("debug.tmp", std::ios::in);
    debug.seekg(0);

    std::string line;

    while (true)
    {
        if (std::getline(debug, line))
        {
            if (line == "-0xKILL")
                return 0;

            std::cout << line << std::endl;
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            debug.clear();
        }
    }
}
