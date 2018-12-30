#pragma once

#include "Block_Abstract.h"

struct OBlock : public Block
{
public:
    OBlock()
    {
        coords[ 0 ] = { 5,1 };
        coords[ 1 ] = { 6,1 };
        coords[ 2 ] = { 5,2 };
        coords[ 3 ] = { 6,2 };

        anchor = coords[ 1 ];
    }
    virtual ~OBlock() {}
protected:
    virtual Coord GetShapeOffset(ERot eRot, int idx) final
    {
        static constexpr Coord shapeOffset[ 4 ] =
        {
            { -1, 0 }, { 0, 0 }, { -1, +1 }, { 0, +1 }
        };

        return shapeOffset[ idx ];
    }
};
