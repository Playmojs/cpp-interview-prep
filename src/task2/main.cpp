/*
Tasks:
    a) Implement Pawn and Bishop as classes that inherit from Piece.
    You do not need to implement the logic of the isLegalMove method.
    b) Implement factory functions make_pawn and make_bishop.
    c) Implement the Board::add method that adds a piece to the board.
    d) Implement the Board::isLegalMove method.

The main function should compile. Correct behavior is not required, as this task
is mostly about the structuring of the classes and methods.
*/

class Square {};

class Piece {
public:
  Piece(Square square) : _square(square) {}
  virtual ~Piece();
  virtual bool isLegalMove(Square to_square) = 0;

protected:
  Square _square;
};

class Board {
public:
  Board() {}
  bool isLegalMove(Square from_square, Square to_square) { return true; }
};

int main() {
  Board board;

  Square b2;
  Square a3;

  auto pawn = make_pawn(b2);
  auto bishop = make_bishop(a3);

  board.add(pawn);
  board.add(bishop);
  bool legal = board.isLegalMove(b2, a3);

  return 0;
}