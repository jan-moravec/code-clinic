#include "Board.h"
#include <fmt/format.h>


std::vector<std::pair<Queen, std::pair<int, int>>> Board::GetQueens() const
{
    std::vector<std::pair<Queen, std::pair<int, int>>> queens;

    for (int row = 0; row < m_board.size(); ++row)
    {
        for (int column = 0; column < m_board[row].size(); ++column)
        {
            const std::optional<Queen> &queen = m_board[row][column];
            if (queen.has_value())
            {
                queens.push_back(std::make_pair(queen.value(), std::make_pair(row, column)));
            }
        }
    }

    return queens;
}

void Board::PlaceQueen(const Queen &queen, int row, int column)
{
    m_board[row][column] = queen;
}

Queen Board::TakeQueen(int row, int column)
{
    Queen queen = m_board[row][column].value();
    m_board[row][column].reset();
    return queen;
}

bool Board::HasQueen(int row, int column) const
{
    return this->GetPosition(row, column).has_value();
}

bool Board::IsSafe(int row, int column) const
{
    int r;
    int c;

    // Check row
    for (r = 0; r < row; ++r)
    {
        if (this->HasQueen(r, column))
        {
            return false;
        }
    }
    for (r = row + 1; r < ROWS; ++r)
    {
        if (this->HasQueen(r, column))
        {
            return false;
        }
    }

    // Check column
    for (c = 0; c < column; ++c)
    {
        if (this->HasQueen(row, c))
        {
            return false;
        }
    }
    for (c = column + 1; c < COLUMNS; ++c)
    {
        if (this->HasQueen(row, c))
        {
            return false;
        }
    }

    // Check top-bottom diagonal
    for (r = row - 1, c = column - 1; r >= 0 && c >= 0; --r, --c)
    {
        if (this->HasQueen(r, c))
        {
            return false;
        }
    }
    for (r = row + 1, c = column + 1; r < ROWS && c < COLUMNS; ++r, ++c)
    {
        if (this->HasQueen(r, c))
        {
            return false;
        }
    }

    // Check bottom-top diagonal
    for (r = row - 1, c = column + 1; r >= 0 && c < COLUMNS; --r, ++c)
    {
        if (this->HasQueen(r, c))
        {
            return false;
        }
    }
    for (r = row + 1, c = column - 1; r < ROWS && c >= 0; ++r, --c)
    {
        if (this->HasQueen(r, c))
        {
            return false;
        }
    }


    return true;
}

bool Board::IsSafeRightSide(int row, int column) const
{
    int r;
    int c;

    // Check row
    for (r = row + 1; r < ROWS; ++r)
    {
        if (this->HasQueen(r, column))
        {
            return false;
        }
    }

    // Check column
    for (c = column + 1; c < COLUMNS; ++c)
    {
        if (this->HasQueen(row, c))
        {
            return false;
        }
    }

    // Check top-bottom diagonal
    for (r = row + 1, c = column + 1; r < ROWS && c < COLUMNS; ++r, ++c)
    {
        if (this->HasQueen(r, c))
        {
            return false;
        }
    }

    // Check bottom-top diagonal
    for (r = row - 1, c = column + 1; r >= 0 && c < COLUMNS; --r, ++c)
    {
        if (this->HasQueen(r, c))
        {
            return false;
        }
    }

    return true;
}

const std::optional<Queen> &Board::GetPosition(int row, int column) const
{
    return m_board[row][column];
}
