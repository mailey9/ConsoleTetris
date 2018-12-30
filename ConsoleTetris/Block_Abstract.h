#pragma once

#include "commondef.h"

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