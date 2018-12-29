#pragma once

#include "commondef.h"

struct ZBlock : public Block
{
public:
    ZBlock()
    {
        coords[ 0 ] = { 5, 1 };
        coords[ 1 ] = { 6, 1 };
        coords[ 2 ] = { 6, 2 };
        coords[ 3 ] = { 7, 2 };

        anchor = coords[ 1 ];
    }
protected:
    virtual Coord GetShapeOffset(ERot eRot, int idx) final
    {
        static constexpr Coord shapeOffset[ ERot::ROT_SIZE ][ 4 ] =
        {
            // 0
            { { -1, 0 },
              {  0, 0 },
              {  0,+1 },
              { +1,+1 } },

            // 90
            { {  0,-1 },
              {  0, 0 },
              { -1, 0 },
              { -1,+1 } },

            // 180
            { { -1, 0 },
              {  0, 0 },
              {  0,+1 },
              { +1,+1 } },

            // 270
            { {  0,-1 },
              {  0, 0 },
              { -1, 0 },
              { -1,+1 } }
        };

        return shapeOffset[ eRot ][ idx ];
    }
};
