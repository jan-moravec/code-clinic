#pragma once

#include "Queen.h"
#include <array>
#include <optional>
#include <utility>
#include <vector>

class Board
{
public:
    struct Position
    {
        std::size_t x;
        std::size_t y;
    };

    std::vector<std::pair<Queen, Position>> GetQueens() const;
    void AddQueen(const Queen &queen, const Position &position);

private:
    std::array<std::array<std::optional<Queen>, 8>, 8> m_board;
};
