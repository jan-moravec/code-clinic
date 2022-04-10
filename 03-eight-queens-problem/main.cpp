#include "Board.h"
#include <fmt/format.h>


int main()
{
    Board board;
    board.AddQueen(Queen{ 0 }, Board::Position{ 0, 0 });
    board.AddQueen(Queen{ 1 }, Board::Position{ 7, 7 });

    auto queens = board.GetQueens();
    for (const auto &[queen, position] : queens)
    {
        fmt::print("Queen {} on possition {} {}\n", queen.GetId(), position.x, position.y);
    }

    return 0;
}
