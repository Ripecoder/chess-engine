#include "chess_board.h"
#include <iostream>
#include <iomanip>
#include <cctype>

// Helper methods for nibble-level operations
inline uint8_t ChessBoard::getSquareNibble(uint8_t square) const {
    uint8_t byteIndex = square / 2;
    uint8_t nibbleIndex = square % 2;
    
    if (nibbleIndex == 0) {
        // Even square - return lower 4 bits
        return board_[byteIndex] & 0x0F;
    } else {
        // Odd square - return upper 4 bits
        return (board_[byteIndex] >> 4) & 0x0F;
    }
}

inline void ChessBoard::setSquareNibble(uint8_t square, uint8_t nibble) {
    uint8_t byteIndex = square / 2;
    uint8_t nibbleIndex = square % 2;
    
    if (nibbleIndex == 0) {
        // Even square - modify lower 4 bits
        board_[byteIndex] = (board_[byteIndex] & 0xF0) | (nibble & 0x0F);
    } else {
        // Odd square - modify upper 4 bits
        board_[byteIndex] = (board_[byteIndex] & 0x0F) | ((nibble & 0x0F) << 4);
    }
}

ChessBoard::ChessBoard() {
    initializeStartingPosition();
}

Piece ChessBoard::getPiece(uint8_t square) const {
    assert(square < 64 && "Square index out of range");
    return getSquareNibble(square);
}

void ChessBoard::setPiece(uint8_t square, Piece piece) {
    assert(square < 64 && "Square index out of range"); 
    assert(piece <= 0x0F && "Invalid piece value (should be 0-15)");
    
    setSquareNibble(square, piece);
}

void ChessBoard::clearSquare(uint8_t square) {
    assert(square < 64 && "Square index out of range");
    setSquareNibble(square, 0); // Set to empty
}

Color ChessBoard::getColor(Piece piece) {
    return (piece & 0x08) ? Color::BLACK : Color::WHITE;  
}

PieceType ChessBoard::getPieceType(Piece piece) {
    return static_cast<PieceType>(piece & 0x07);
}

Piece ChessBoard::makePiece(Color color, PieceType type) {
    return static_cast<Piece>((static_cast<uint8_t>(color) << 3) | static_cast<uint8_t>(type));
}

void ChessBoard::initializeStartingPosition() {
    // Clear the board
    for (int i = 0; i < 32; i++) {
        board_[i] = 0;
    }
    
    // Set up white pieces (rank 7)
    board_[28] = makePiece(Color::WHITE, PieceType::ROOK) | (makePiece(Color::WHITE, PieceType::KNIGHT) << 4);
    board_[29] = makePiece(Color::WHITE, PieceType::BISHOP) | (makePiece(Color::WHITE, PieceType::QUEEN) << 4);
    board_[30] = makePiece(Color::WHITE, PieceType::KING) | (makePiece(Color::WHITE, PieceType::BISHOP) << 4);
    board_[31] = makePiece(Color::WHITE, PieceType::KNIGHT) | (makePiece(Color::WHITE, PieceType::ROOK) << 4);
    
    // Set up white pawns (rank 6)
    for (int i = 0; i < 8; i++) {
        setSquareNibble(48 + i, makePiece(Color::WHITE, PieceType::PAWN));
    }
    
    // Set up black pieces (rank 0)
    board_[0] = makePiece(Color::BLACK, PieceType::ROOK) | (makePiece(Color::BLACK, PieceType::KNIGHT) << 4);
    board_[1] = makePiece(Color::BLACK, PieceType::BISHOP) | (makePiece(Color::BLACK, PieceType::QUEEN) << 4);
    board_[2] = makePiece(Color::BLACK, PieceType::KING) | (makePiece(Color::BLACK, PieceType::BISHOP) << 4);
    board_[3] = makePiece(Color::BLACK, PieceType::KNIGHT) | (makePiece(Color::BLACK, PieceType::ROOK) << 4);
    
    // Set up black pawns (rank 1)
    for (int i = 0; i < 8; i++) {
        setSquareNibble(8 + i, makePiece(Color::BLACK, PieceType::PAWN));
    }
}

void ChessBoard::printBoard() const {
    std::cout << "  a b c d e f g h\n";
    for (int rank = 7; rank >= 0; rank--) {
        std::cout << (rank + 1) << " ";
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            Piece piece = getPiece(square);
            
            if (piece == 0) {
                std::cout << ". ";
            } else {
                Color color = getColor(piece);
                PieceType type = getPieceType(piece);
                
                char piece_char;
                switch (type) {
                    case PieceType::PAWN:   piece_char = 'p'; break;
                    case PieceType::KNIGHT: piece_char = 'n'; break;
                    case PieceType::BISHOP: piece_char = 'b'; break;
                    case PieceType::ROOK:   piece_char = 'r'; break;
                    case PieceType::QUEEN:  piece_char = 'q'; break;
                    case PieceType::KING:   piece_char = 'k'; break;
                    default:                piece_char = '?'; break;
                }
                
                if (color == Color::WHITE) {
                    std::cout << static_cast<char>(std::toupper(piece_char)) << " ";
                } else {
                    std::cout << piece_char << " ";
                }
            }
        }
        std::cout << rank + 1 << "\n";
    }
    std::cout << "  a b c d e f g h\n";
}