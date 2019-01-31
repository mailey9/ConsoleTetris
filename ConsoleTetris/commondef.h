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

enum EBlockType
{
    I = 0,
    J,
    L,
    O,
    S,
    T,
    Z,
    SIZE_BLOCKTYPE
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
