#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <cstdint>
#include <array>
#include <cassert>
#include <vector>

enum class PieceType : uint8_t {
    EMPTY = 0,
    PAWN = 1,
    KNIGHT = 2,
    BISHOP = 3,
    ROOK = 4,
    QUEEN = 5,
    KING = 6
};

enum class Color : uint8_t {
    WHITE = 0,
    BLACK = 1
};

// Combined piece representation: MSB = color, lower 3 bits = piece type
using Piece = uint8_t;

// Move structure: 16-bit encoding with source and destination square
struct Move {
    uint8_t from : 6;  // Source square (0-63)
    uint8_t to : 6;    // Destination square (0-63) 
    uint8_t promotion : 2;  // Promotion piece (0=none, 1=pawn, 2=knight, etc.)

    Move() : from(0), to(0), promotion(0) {}
    Move(uint8_t source, uint8_t dest) : from(source), to(dest), promotion(0) {}
    Move(uint8_t source, uint8_t dest, uint8_t promote) : from(source), to(dest), promotion(promote) {}

    // For testing/debugging
    bool operator==(const Move& other) const {
        return from == other.from && to == other.to && promotion == other.promotion;
    }
};

class ChessBoard {
private:
    std::array<uint8_t, 32> board_;

    // Helper methods for nibble-level operations
    inline uint8_t getSquareNibble(uint8_t square) const;
    inline void setSquareNibble(uint8_t square, uint8_t nibble);
    
public:
    ChessBoard();
    
    // Board operations
    Piece getPiece(uint8_t square) const;
    void setPiece(uint8_t square, Piece piece);
    void clearSquare(uint8_t square);
    
    // Piece helpers  
    static Color getColor(Piece piece);
    static PieceType getPieceType(Piece piece);
    static Piece makePiece(Color color, PieceType type);
    
    // Move generation - pawns
    std::vector<Move> generatePawnMoves(uint8_t square) const;
    std::vector<Move> generateAllLegalMoves(Color color) const;
    
    // Board initialization
    void initializeStartingPosition();
    
    // Debug/printing
    void printBoard() const;
};

#endif // CHESS_BOARD_H