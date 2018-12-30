#pragma once

#include "Block_Abstract.h"

// 000 0000 000
//
struct IBlock : public Block
{
public:
    IBlock()
    {
        coords[ 0 ] = { 4,1 };
        coords[ 1 ] = { 5,1 };
        coords[ 2 ] = { 6,1 };
        coords[ 3 ] = { 7,1 };

        anchor = coords[ 1 ];
    }
    virtual ~IBlock() {}
private:
    virtual Coord GetShapeOffset(ERot eRot, int idx) final
    {
        static constexpr Coord shapeOffset[ ERot::ROT_SIZE ][ 4 ]  =
        {
            { { -1,0 },
              {  0,0 },
              { +1,0 },
              { +2,0 } },    // 0

            { { 0,-1 },
              { 0, 0 },
              { 0,+1 },
              { 0,+2 } },    // 90

            { { -1,0 },
              {  0,0 },
              { +1,0 },
              { +2,0 } },    // 180

            { { 0,-1 },
              { 0, 0 },
              { 0,+1 },
              { 0,+2 } }     // 270
        };

        return shapeOffset[ eRot ][ idx ];
    }
};