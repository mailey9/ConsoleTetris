//  TODO
//  * win32 : optimize clrscr();
//  * win32 : simple-console double buffering
//  * stdio : pattern binary data's file i/o

#include <stdio.h>
#include <conio.h>
#include <stdint.h>
#include <memory.h>
#include <assert.h>
#include <stdlib.h>

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
    //
    COORD coord = { x,y };
    HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
    return SetConsoleCursorPosition( h, coord );
}
int clrscr()
{
    return system("cls");
}
//----------------------------------------
Block*  g_pBlock         = nullptr;
bool    g_tryDownBlocked = false;

bool    g_run = true;
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

Block* GenerateBlock(EBlockType e)
{
    assert( e >= 0 && e < SIZE_BLOCKTYPE );
    switch ( e )
    {
    case I:
        return new IBlock();
    case J:
        return new JBlock();
    case L:
        return new LBlock();
    case O:
        return new OBlock();
    case S:
        return new SBlock();
    case T:
        return new TBlock();
    case Z:
        return new ZBlock();
    default:
        return nullptr;
    }
}

Block* GenerateBlock()
{
    int r = rand() % SIZE_BLOCKTYPE;
    return GenerateBlock( (EBlockType)r );
}

bool IsLineFull(int i)
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

void ClearLine(int i)
{
    assert( i >= 1 && i < ROW_COUNT - 1 );

    for (int col = 1; col < COL_COUNT - 1; ++col)
    {
        g_board[ i ][ col ] = 0;
    }

    // * can be substituted with one line ::memset();
    //::memset( g_board[ mem_point ], 0, sizeof(int)*count );
}

void BlockToBoard()
{
    assert( g_pBlock != nullptr );

    for (int i = 0; i < 4; ++i)
    {
        Coord c = g_pBlock->coords[ i ];
        g_board[ c.y ][ c.x ] = 1;
    }
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
        // try,
        g_tryDownBlocked = !g_pBlock->TryMove( EDir::Down );
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

void Update()
{
    if ( g_tryDownBlocked == true )
    {
        g_tryDownBlocked = false; // reset the flag.
        BlockToBoard();

        delete g_pBlock;
        g_pBlock = GenerateBlock();
    }

    // *from bottom to top (except boundary)
    int targetRow = ROW_COUNT - 2;
    while ( targetRow > 0 )
    {
        if ( IsLineFull( targetRow ) == true )
        {
            ClearLine( targetRow );

            // *above cells of the line . y += 1;
            for (int r = targetRow; r > 1; --r)
            {
                for (int c = 1; c < COL_COUNT - 1; ++c)
                {
                    g_board[ r ][ c ] = g_board[ r-1 ][ c ];
                }
            }
        }
        else
        {
            --targetRow;
        }
    }
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

#include "ScreenBuffer.h"

int main( int argc, char* argv[] )
{
    ScreenBuffer buf;
    buf.Initialize();

    buf.SetColor(3, 1, FOREGROUND_RED);
    buf.Present();

    _getch();
    
    return 0;

    double timeOld  = 0.0;

    ::srand( 10 );  // testing seed : 10
    g_pBlock = GenerateBlock();

    while ( g_run == true )
    {
        double timeCurr  = GetTickCount64() * 0.001;
        double timeDelta = timeCurr - timeOld;

        if ( _kbhit() != 0 )
        {
            ProcessInput();
        }

        if ( timeDelta >= 1.0 )
        {
            if ( g_pBlock != nullptr )
            {
                g_tryDownBlocked = !g_pBlock->TryMove( EDir::Down );
            }

            timeOld = timeCurr;
        }

        Update();

        Draw();
    }
    
    if ( g_pBlock != nullptr )
    {
        delete g_pBlock;
    }

    return 0;
}