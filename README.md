# Chess Engine Project

A traditional chess engine implementation in C++ without neural networks, built with custom board representation.

## Project Overview

This project implements a chess engine from scratch using a position-centric packed-nibble board representation. Unlike conventional bitboard approaches, this implementation stores piece information directly at each square for easier debugging and conceptual clarity.

## Architecture Philosophy

### Custom Board Representation
- **32-byte storage** (64 squares × 4 bits each)
- **Upper-nibble-first layout**: Odd squares use upper 4 bits, even squares use lower 4 bits  
- **Position-centric**: Each square directly contains its piece information
- **Piece encoding**: MSB = color, lower 3 bits = piece type

### Design Principles
1. **Custom approach**: Deliberately chose alternative architecture over conventional bitboards
2. **Systems engineering focus**: Understanding implementation details and performance trade-offs
3. **Incremental development**: Building correctness before optimization
4. **Transparent design**: Clear separation of concerns and encapsulation

## Current Status

### Phase 1 - Board Representation (Completed)
- Packed board implementation with 32-byte storage
- Square-to-nibble mapping and access functions  
- Piece encoding, decoding, and utility methods
- Starting position initialization
- Unit testing and debugging support

### Phase 2 - Move Generation (In Progress)
- Move structure implementation
- Legal move generation for basic pieces
- Special moves handling