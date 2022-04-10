#pragma once

#include "Queen.h"
#include <array>
#include <optional>
#include <utility>
#include <vector>

class Board
{
public:
    static constexpr int ROWS = 8;
    static constexpr int COLUMNS = 8;

    std::vector<std::pair<Queen, std::pair<int, int>>> GetQueens() const;
    void PlaceQueen(const Queen &queen, int row, int column);
    Queen TakeQueen(int row, int column);
    bool HasQueen(int row, int column) const;

    bool IsSafe(int row, int column) const;
    bool IsSafeRightSide(int row, int column) const;

private:
    const std::optional<Queen> &GetPosition(int row, int column) const;

    std::array<std::array<std::optional<Queen>, COLUMNS>, ROWS> m_board;
};
