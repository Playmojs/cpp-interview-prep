
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

#include <cassert>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <memory>
#include <vector>
#include <array>

class Square 
{
public:
  Square(){};
  Square(unsigned column, unsigned row): _column(column),_row(row){};
  unsigned _row;
  unsigned _column;
  bool _is_occupied = false;
  bool operator==(Square square)
  {
    if (square._column == _column && square._row == _row){return true;}
    return false;
  }
};

class Piece {
public:
  Piece(Square& square) : _square(square) {}
  virtual ~Piece(){};
  virtual bool isLegalMove(Square to_square) = 0;
  Square& getSquare() {return _square;}

protected:
  Square& _square;
};

class Pawn: public Piece
{
public:
  using Piece::Piece;
  bool isLegalMove(const Square to_square)
  {
    if(to_square._row > 8 || to_square._column > 8){return false;}
    if(!to_square._is_occupied && to_square._row == _square._row && to_square._column == _square._column + 1)
    {return true;}
    return false;
  }
};

class Bishop : public Piece
{
public:
  using Piece::Piece;
  bool isLegalMove(const Square to_square)
  {
    if(to_square._row > 8 || to_square._column > 8){return false;}
    unsigned diff = abs(int(to_square._column - _square._column));
    if(diff != 0 && diff == abs(int(to_square._row - _square._row))){return true;}
    return false;
  }
};

std::unique_ptr<Pawn> make_pawn(Square square){return std::make_unique<Pawn>(square);}
std::unique_ptr<Bishop> make_bishop(Square square){return std::make_unique<Bishop>(square);}

class Board {
private:
  std::array<std::array<Square, 8>, 8> _squares;
  std::vector<std::unique_ptr<Piece>> _pieces;
public:
  Board() 
  {
    for (int i = 0; i < 64; i ++)
    {
      int column = i / 8;
      int row = i % 8;
      _squares[column][row] = Square(column, row);
    }
  }

  Square& getSquare(unsigned column, unsigned row){
    assert(row < 8 && column < 8);
    return _squares[column][row];}

  int findPiece(const Square& square)
  {
    // if(!square._is_occupied){return -1;}
    for(int i = 0; i < _pieces.size() ; ++i )
    {
      if (_pieces[i]->getSquare() == square){return i;}
    }
    return -1;
  }
    
  void add(std::unique_ptr<Piece> piece)
  {
    piece->getSquare()._is_occupied = true;
    _pieces.push_back(std::move(piece)); 
  }
  
  bool isLegalMove(const Square& from_square, const Square& to_square) 
  {
    int index = findPiece(from_square);
    if(index == -1){return false;}
    //This fails if a piece is in the way, lol.
    return _pieces[index]->isLegalMove(to_square);
  }

};

int main() {
  Board board;

  Square& b2 = board.getSquare(1, 1);
  Square& a3 = board.getSquare(0, 2);

  auto pawn = make_pawn(b2);
  auto bishop = make_bishop(a3);

  board.add(std::move(pawn));
  board.add(std::move(bishop));
  bool legal = board.isLegalMove(a3, board.getSquare(5, 7));
  std::cout<< std::boolalpha << legal << "\n";

  return 0;
}
