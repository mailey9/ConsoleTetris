#include "ScreenBuffer.h"

#include <assert.h>

ScreenBuffer::ScreenBuffer()
    : h( nullptr )
{
    csbi_ex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

}

ScreenBuffer::~ScreenBuffer()
{
    if ( h != nullptr )
    {
        CloseHandle( h );
    }
}

//----------------------------------------------------

void ScreenBuffer::Initialize()
{
    h = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        CONSOLE_TEXTMODE_BUFFER,
        nullptr);

    // !
    assert( h != INVALID_HANDLE_VALUE );

    GetConsoleScreenBufferInfoEx( h, &csbi_ex );

    bufSize = csbi_ex.dwSize;
    // * cannot compile, "No constructor"
    //bufConsole = std::make_unique<CHAR_INFO>(bufSize.X * bufSize.Y);
    bufConsole.reset( new CHAR_INFO[ bufSize.X * bufSize.Y ] );
    ::ZeroMemory( bufConsole.get(), sizeof(CHAR_INFO) * bufSize.X * bufSize.Y );
}

void ScreenBuffer::Clear()
{
    COORD topLeft = { 0, 0 };
    DWORD len = bufSize.X * bufSize.Y;
    DWORD written;

    FillConsoleOutputCharacter( h, TEXT(' '), len, topLeft, &written );
    FillConsoleOutputCharacter( h, 0, len, topLeft, &written);
    ::ZeroMemory( bufConsole.get(), sizeof(CHAR_INFO) * len );

    SetConsoleCursorPosition( h, topLeft );
}

bool ScreenBuffer::Present()
{
    COORD topLeft = { 0,0 };
    SMALL_RECT rcWritten = { 0,0,bufSize.X, bufSize.Y };

    WriteConsoleOutput( h, bufConsole.get(), bufSize, topLeft, &rcWritten );
    return SetConsoleActiveScreenBuffer( h );
}

bool ScreenBuffer::SetPoint(SHORT x, SHORT y, EForeColor eFore, EBackColor eBack, TCHAR ch)
{
    CHAR_INFO* pBuf = bufConsole.get();
#ifdef _UNICODE
    pBuf[ bufSize.X * y + x ].Char.UnicodeChar = ch;
#else /* NotSet or MBCS */
    pBuf[ bufSize.X * y + x ].Char.AsciiChar = ch;
#endif

    pBuf[ bufSize.X * y + x ].Attributes = ((WORD)eFore | (WORD)eBack);
    
    return false;
}