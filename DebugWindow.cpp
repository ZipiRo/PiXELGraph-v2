#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

std::ifstream debug;
std::ofstream debugOf;

char buffer[105];
int bufferSize, lastBufferSize;

int main()
{
    while (1)
    {        
        bufferSize = std::filesystem::file_size("debug.tmp");
        if(bufferSize == lastBufferSize) continue;
        if(bufferSize == 0)
        {
            lastBufferSize = 0;
            continue;
        }

        lastBufferSize = bufferSize;

        debug.open("debug.tmp");
        debug.getline(buffer, 105);
        std::cout << buffer << '\n';
        debug.close();
        
        debugOf.open("debug.tmp");
        debugOf << "";
        debugOf.close();
    }

    return 0;
}