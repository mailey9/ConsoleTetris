#pragma once

#include <stdint.h>
#include <memory.h>
#include <assert.h>

constexpr int ROW_COUNT = 20 + 2;
constexpr int COL_COUNT = 10 + 2;

extern int g_board[ ROW_COUNT ][ COL_COUNT ];

enum class EDir : uint8_t
{
    Up,
    Down,
    Left,
    Right
};
enum ERot
{
    _0 = 0,
    _90,
    _180,
    _270,

    ROT_SIZE
};

struct Coord
{
    int x;
    int y;

    bool operator== (const Coord& rhs)
    {
        return (x == rhs.x) && (y == rhs.y);
    }
    bool operator!= (const Coord& rhs)
    {
        return !((x == rhs.x) && (y == rhs.y));
    }
};

Coord operator+ (const Coord& lhs, const Coord& rhs)
{
    return Coord{ lhs.x + rhs.x, lhs.y + rhs.y };
}

//----------------------------------------

struct Block
{
protected:
    Coord anchor;
    ERot  currRot;
public:
    Coord coords[ 4 ];
protected:
    Block()// cannot be created directly
        : currRot( ERot::_0 )
    {};
public:
    virtual ~Block(){}
protected:
    virtual Coord GetShapeOffset(ERot eRot, int idx) = 0;
public:
    // --commenting--
    bool TryMove( EDir eDir )
    {
        Coord comparers[ 4 ];
        ::memcpy( comparers, coords, sizeof(Coord)*4 );

        switch ( eDir )
        {
        case EDir::Up:
            for (int i = 0; i < 4; ++i)
            {
                comparers[ i ].y -= 1;
            }
            break;
        case EDir::Down:
            for (int i = 0; i < 4; ++i)
            {
                comparers[ i ].y += 1;
            }
            break;
        case EDir::Left:
            for (int i = 0; i < 4; ++i)
            {
                comparers[ i ].x -= 1;
            }
            break;
        case EDir::Right:
            for (int i = 0; i < 4; ++i)
            {
                comparers[ i ].x += 1;
            }
            break;
        }

        for (int i = 0; i < 4; ++i)
        {
            assert( coords[i] != comparers[i] );
            if ( g_board[ comparers[i].y ][ comparers[i].x ] != 0 )
            {
                return false;
            }
        }

        ::memcpy( coords, comparers, sizeof(Coord)*4 );
        anchor = coords[ 1 ];
        return true;
    }

    // --commenting--
    bool TryRotate()
    {
        Coord comparers[ 4 ];
        ERot nextRot = static_cast<ERot>( (currRot + 1) % ERot::ROT_SIZE );
        
        // constructing comparers
        for (int i = 0; i < 4; ++i)
        {
            comparers[ i ] = GetShapeOffset( nextRot, i ) + anchor;
        }

        // if cannot fit
        for (int i = 0; i < 4; ++i)
        {
            if ( g_board[ comparers[i].y ][ comparers[i].x ] != 0 )
            {
                return false;
            }
        }

        ::memcpy( coords, comparers, sizeof(Coord)*4 );
        currRot = nextRot;
        anchor = coords[ 1 ];

        return false;
    }
};