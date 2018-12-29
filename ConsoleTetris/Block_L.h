#pragma once

#include "commondef.h"

struct LBlock : public Block
{
public:
    LBlock()
    {
        coords[ 0 ] = { 7, 2 };
        coords[ 1 ] = { 6, 2 };
        coords[ 2 ] = { 7, 1 };
        coords[ 3 ] = { 5, 2 };

        anchor = coords[ 1 ];
    }
protected:
    virtual Coord GetShapeOffset(ERot eRot, int idx) final
    {
        static constexpr Coord shapeOffset[ ERot::ROT_SIZE ][ 4 ] =
        {
            { { +1, 0 },    //   2
              {  0, 0 },    // 310
              { +1,-1 },
              { -1, 0 } },    // 0

            { {  0,+1 },     // 3
              {  0, 0 },     // 1
              { +1,+1 },     // 02
              {  0,-1 } },     // 90

            { { -1, 0 },     // 013
              {  0, 0 },     // 2
              { -1,+1 },
              { +1, 0 } },    // 180

            { {  0,-1 },     // 20
              {  0, 0 },     //  1
              { -1,-1 },     //  3
              {  0,+1 } },    // 270
        };

        return shapeOffset[ eRot ][ idx ];
    }
};
