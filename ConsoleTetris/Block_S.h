#pragma once

#include "Block_Abstract.h"

struct SBlock : public Block
{
public:
    SBlock()
    {
        coords[ 0 ] = { 6, 1 };
        coords[ 1 ] = { 5, 1 };
        coords[ 2 ] = { 5, 2 };
        coords[ 3 ] = { 4, 2 };

        anchor = coords[ 1 ];
    }
    virtual ~SBlock() {}
protected:
    virtual Coord GetShapeOffset(ERot eRot, int idx) final
    {
        static constexpr Coord shapeOffset[ ERot::ROT_SIZE ][ 4 ] =
        {
            // 0
            { { +1, 0 },
              {  0, 0 },
              {  0,+1 },
              { -1,+1 } },

            // 90
            { {  0,-1 },
              {  0, 0 },
              { +1, 0 },
              { +1,+1 } },

            // 180
            { { +1, 0 },
              {  0, 0 },
              {  0,+1 },
              { -1,+1 } },

            // 270
            { {  0,-1 },
              {  0, 0 },
              { +1, 0 },
              { +1,+1 } }
        };

        return shapeOffset[ eRot ][ idx ];
    }
};
