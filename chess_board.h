#pragma once

#include <cstdint>
#include <array>

class ChessBoard{

private:
    std::array<std::uint64_t, 4> board; 
public:
    ChessBoard();
};