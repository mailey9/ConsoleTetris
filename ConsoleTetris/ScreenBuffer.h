// * using win32 console
//  ref. Raymond Chen
//    Q. When MSDN says NULL, is it okay to use nullptr?
//    A. Yes.
//  https://blogs.msdn.microsoft.com/oldnewthing/20180307-00/?p=98175

#pragma once

#include <memory>
#include <Windows.h>

class ScreenBuffer
{
private:
    HANDLE h;

    COORD bufSize;
    std::unique_ptr<CHAR_INFO> bufConsole;
    CONSOLE_SCREEN_BUFFER_INFOEX csbi_ex;
public:
    ScreenBuffer();
    ~ScreenBuffer();

    void Initialize();

    void Clear();

    bool Present();
    bool SetColor(short x, short y, int attr);

    const HANDLE GetHandle() const { return h; }
};