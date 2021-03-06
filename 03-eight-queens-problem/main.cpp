#include "Board.h"
#include <cassert>
#include <fmt/format.h>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/screen.hpp>

/*
1) Start in the rightmost column
2) If all queens are placed return true
3) Try all rows in the current column.
   Do following for every tried row.
    a) If the queen can be placed safely in this row
       then mark this [row, column] as part of the
       solution and recursively check if placing
       queen here leads to a solution.
    b) If placing the queen in [row, column] leads to
       a solution then return true.
    c) If placing queen doesn't lead to a solution then
       unmark this [row, column] (Backtrack) and go to
       step (a) to try other rows.
4) If all rows have been tried and nothing worked,
   return false to trigger backtracking.
*/
bool Solve(Board &board, int column)
{
    if (column < 0)
    {
        return true;
    }

    for (int row = 0; row < board.ROWS; ++row)
    {
        if (board.IsSafeRightSide(row, column))
        {
            board.PlaceQueen(Queen{ column }, row, column);

            if (Solve(board, column - 1))
            {
                return true;
            }

            board.TakeQueen(row, column);// Backtrack
        }
    }

    return false;
}

void Print(const Board &board)
{
    std::vector<std::vector<std::string>> strings;

    for (int row = 0; row < board.ROWS; ++row)
    {
        std::vector<std::string> rowStrings;
        for (int column = 0; column < board.COLUMNS; ++column)
        {
            if (board.HasQueen(row, column))
            {
                rowStrings.push_back(" O ");
            }
            else
            {
                rowStrings.push_back("   ");
            }
        }
        strings.push_back(rowStrings);
    }

    using namespace ftxui;
    auto table = Table(strings);

    table.SelectAll().Border(DOUBLE);
    table.SelectAll().Separator(LIGHT);
    auto document = table.Render();
    auto screen = Screen::Create(Dimension::Fit(document));
    Render(screen, document);
    screen.Print();
}

int main()
{
    Board board;
    Solve(board, board.COLUMNS - 1);

    auto queens = board.GetQueens();
    for (const auto &[queen, position] : queens)
    {
        fmt::print("Queen {} on possition [{}, {}]\n", queen.GetId(), position.first, position.second);
        assert(board.IsSafe(position.first, position.second));
    }

    Print(board);

    return 0;
}
