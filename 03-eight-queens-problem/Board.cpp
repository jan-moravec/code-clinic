#include "Board.h"


std::vector<std::pair<Queen, Board::Position>> Board::GetQueens() const
{
    std::vector<std::pair<Queen, Board::Position>> queens;

    for (std::size_t x = 0; x < m_board.size(); ++x)
    {
        for (std::size_t y = 0; y < m_board[x].size(); ++y)
        {
            const std::optional<Queen> &queen = m_board[x][y];
            if (queen.has_value())
            {
                queens.push_back(std::make_pair(queen.value(), Position{ x, y }));
            }
        }
    }

    return queens;
}

void Board::AddQueen(const Queen &queen, const Position &position)
{
    m_board[position.x][position.y] = queen;
}
