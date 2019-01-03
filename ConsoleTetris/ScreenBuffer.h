// * using win32 console
//  ref. Raymond Chen
//    Q. When MSDN says NULL, is it okay to use nullptr?
//    A. Yes.
//  https://blogs.msdn.microsoft.com/oldnewthing/20180307-00/?p=98175

// * pro-tip
//  ref. riv from StackOverflow
//  https://stackoverflow.com/questions/17125440/c-win32-console-color/17125539

#pragma once

#include <memory>
#include <Windows.h>

class ScreenBuffer
{
public:
    enum class EForeColor : uint8_t
    {
        Black       = 0,

        DarkBlue    = FOREGROUND_BLUE,
        DarkGreen   = FOREGROUND_GREEN,
        DarkCyan    = FOREGROUND_GREEN | FOREGROUND_BLUE,
        DarkRed     = FOREGROUND_RED,
        DarkMagenta = FOREGROUND_RED | FOREGROUND_BLUE,
        DarkYellow  = FOREGROUND_RED | FOREGROUND_GREEN,
        DarkGray    = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,

        Gray        = FOREGROUND_INTENSITY,
        Blue        = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
        Green       = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
        Cyan        = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
        Red         = FOREGROUND_INTENSITY | FOREGROUND_RED,
        Magenta     = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
        Yellow      = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
        White       = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
    };
    enum class EBackColor : uint8_t
    {
        Black       = 0,

        DarkBlue    = BACKGROUND_BLUE,
        DarkGreen   = BACKGROUND_GREEN,
        DarkCyan    = BACKGROUND_GREEN | BACKGROUND_BLUE,
        DarkRed     = BACKGROUND_RED,
        DarkMagenta = BACKGROUND_RED | BACKGROUND_BLUE,
        DarkYellow  = BACKGROUND_RED | BACKGROUND_GREEN,
        DarkGray    = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,

        Gray        = BACKGROUND_INTENSITY,
        Blue        = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
        Green       = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
        Cyan        = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
        Red         = BACKGROUND_INTENSITY | BACKGROUND_RED,
        Magenta     = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
        Yellow      = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
        White       = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
    };
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
    
    bool SetPoint(SHORT x, SHORT y, EForeColor eFore, EBackColor eBack, TCHAR ch);
    inline bool SetPoint(SHORT x, SHORT y)
    {
        return SetPoint(x, y, EForeColor::DarkMagenta, EBackColor::White, TEXT('@'));
    }
    inline bool SetPoint(SHORT x, SHORT y, EBackColor eBackColor)
    {
        return SetPoint(x, y, EForeColor::Black, eBackColor, TEXT(' '));
    }
    
    const HANDLE GetHandle() const { return h; }
};