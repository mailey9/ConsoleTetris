#pragma once

#include "commondef.h"

struct JBlock : public Block
{
public:
    JBlock()
    {
        coords[ 0 ] = { 4, 2 };
        coords[ 1 ] = { 5, 2 };
        coords[ 2 ] = { 4, 1 };
        coords[ 3 ] = { 6, 2 };

        anchor = coords[ 1 ];
    }
protected:
    virtual Coord GetShapeOffset(ERot eRot, int idx) final
    {
        static constexpr Coord shapeOffset[ ERot::ROT_SIZE ][ 4 ] =
        {
            { { -1, 0 },    // 2
              {  0, 0 },    // 013
              { -1,-1 },
              { +1, 0 } },    // 0

            { {  0,-1 },     // 02
              {  0, 0 },     // 1
              { +1,-1 },     // 3
              {  0,+1 } },    // 90

            { { +1, 0 },     // 310
              {  0, 0 },     //   2
              { +1,+1 },
              { -1, 0 } },    // 180

            { {  0,+1 },     //  3
              {  0, 0 },     //  1
              { -1,+1 },     // 20
              {  0,-1 } }     // 270
        };

        return shapeOffset[ eRot ][ idx ];
    }
};
