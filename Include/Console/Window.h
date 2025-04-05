#pragma once

#include <string>
#include <Windows.h>

#include "ErrorSystem.h"

class Window
{
private:
    Window() {}    

    HWND ConsoleWindow;

    HANDLE ConsoleOutputH;
    HANDLE ConsoleInputtH;

    void ConstructWindow();

    int WIDTH;
    int HEIGHT;
    int FONT_SIZE;
    std::wstring TITLE;

public:
    Window(const Window&) = delete;
    void operator=(const Window&) = delete;

    void SetParameters(int width, int height, int fontSize, const std::wstring &title);
    void SetTitle(const std::wstring &title);

    static Window &GetInstance(); 
};