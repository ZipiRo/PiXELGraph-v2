#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <thread>

int main()
{
    SetConsoleTitleW(L"PiXELGraph v2.0 | DebugWindow");
    
    HWND console = GetConsoleWindow();
    HMENU menu = GetSystemMenu(console, FALSE);

    EnableMenuItem(menu, SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
    
    std::ifstream debug("debug.tmp", std::ios::in);
    debug.seekg(0);

    std::string line;

    while (true)
    {
        if (std::getline(debug, line))
        {
            if (line == "-0xKILL")
                return 0;
            else if(line == "-0xERROR")
            {
                ShowWindow(console, SW_RESTORE);
                SetForegroundWindow(console);
                EnableMenuItem(menu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);

                DrawMenuBar(console); 
            }

            std::cout << line << std::endl;
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            debug.clear();
        }
    }
}
