#include <stdio.h>
#include <conio.h>
#include <stdint.h>
#include <memory.h>
#include <assert.h>

#include <Windows.h>

#include "commondef.h"

#include "Block_I.h"
#include "Block_J.h"
#include "Block_L.h"
#include "Block_O.h"
#include "Block_S.h"
#include "Block_T.h"
#include "Block_Z.h"

BOOL gotoxy( SHORT x, SHORT y )
{
    COORD coord = { x,y };
    HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
    return SetConsoleCursorPosition( h, coord );
}
int clrscr()
{
    return system("cls");
}
//----------------------------------------
Block*  g_pBlock = nullptr;
bool    g_run    = true;
bool    g_own = false;
int     g_board[ ROW_COUNT ][ COL_COUNT ] =
{
    1,  1,1,1,1,1,  1,1,1,1,1,  1,
    
    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,

    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,

    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,

    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,
    1,  0,0,0,0,0,  0,0,0,0,0,  1,

    1,  1,1,1,1,1,  1,1,1,1,1,  1,
};

inline bool IsLineFull(int i)
{
    assert(i >= 1 && i < ROW_COUNT - 1);
    
    for (int col = 1; col < COL_COUNT - 1; ++col)
    {
        if ( g_board[ i ][ col ] == 0 )
        {
            return false;
        }
    }

    return true;
}
//----------------------------------------
void ProcessInput()
{
    int ch = _getch();
    switch ( ch )
    {
    case 'w': case 'W':
        g_pBlock->TryRotate();
        break;
    case 's': case 'S':
        g_pBlock->TryMove( EDir::Down );
        break;
    case 'a': case 'A':
        g_pBlock->TryMove( EDir::Left );
        break;
    case 'd': case 'D':
        g_pBlock->TryMove( EDir::Right );
        break;
    case 'q': case 'Q':
        g_run = false;
        break;
    }
}

void Update(float dt)
{
    static float timeAcc = .0f;
    timeAcc += dt;

    if ( timeAcc >= 0.2f )
    {
        timeAcc -= 0.2f;

        if ( g_pBlock != nullptr )
        {
            g_pBlock->TryMove( EDir::Down );
        }
    }

    //----


}

void Draw()
{
    clrscr();

    for (int row = 0; row < ROW_COUNT; ++row)
    {
        for (int col = 0; col < COL_COUNT; ++col)
        {
            switch ( g_board[ row ][ col ] )
            {
            case 0:
                gotoxy( col*3, row );
                printf(" . ");
                break;
            case 1:
                gotoxy( col*3, row );
                printf(" # ");
                break;
            }
        }
    }

    if ( g_pBlock == nullptr )
    {
        return;// *early return
    }

    for (int i = 0; i < 4; ++i)
    {
        Coord c = g_pBlock->coords[ i ];
        if ( c.x >= 0 && c.x < COL_COUNT &&
             c.y >= 0 && c.y < ROW_COUNT )
        {
            gotoxy( c.x*3, c.y );
            printf(" @ ");
        }
    }
}

int main( int argc, char* argv[] )
{
    g_pBlock = new TBlock();

    float timeOld  = .0f;
    float timeCurr = .0f;

    while ( g_run == true )
    {
        if ( _kbhit() != 0 )
        {
            ProcessInput();
        }

        timeCurr = GetTickCount64() * 0.001f;
        Update( timeCurr - timeOld );
        timeOld = timeCurr;

        Draw();
    }
    
    if ( g_pBlock != nullptr )
    {
        delete g_pBlock;
    }

    return 0;
}