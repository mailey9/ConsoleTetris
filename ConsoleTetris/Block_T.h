#pragma once

#include "Block_Abstract.h"

struct TBlock : public Block
{
public:
    TBlock()
    {
        coords[ 0 ] = { 5, 1 };
        coords[ 1 ] = { 5, 2 };
        coords[ 2 ] = { 4, 2 };
        coords[ 3 ] = { 6, 2 };

        anchor = coords[ 1 ];
    }
    virtual ~TBlock() {}
protected:
    virtual Coord GetShapeOffset(ERot eRot, int idx) final
    {
        static constexpr Coord shapeOffset[ ERot::ROT_SIZE ][ 4 ] =
        {
            // 0
            { {  0,-1 },
              {  0, 0 },
              { -1, 0 },
              { +1, 0 } },

            // 90
            { { +1, 0 },
              {  0, 0 },
              {  0,-1 },
              {  0,+1 } },

            // 180
            { {  0,+1 },
              {  0, 0 },
              { +1, 0 },
              { -1, 0 } },

            // 270
            { { -1, 0 },
              {  0, 0 },
              {  0,+1 },
              {  0,-1 } }
        };

        return shapeOffset[ eRot ][ idx ];
    }
};
