#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <signal.h>

#ifndef TETRIS_HPP
#define TETRIS_HPP
#define MAX_PIECES 15

// Forward declaration of ListGameBoard
class ListGameBoard;

struct Piece {
    std::string shape;
    std::string color;
    Piece* next;
    Piece* prev;

    Piece(std::string s, std::string c);
    friend void displayPiece(const Piece* piece);
};

class ListGameBoard {
private:
    Piece* head;
    Piece* tail;

public:
    ListGameBoard();
    ~ListGameBoard();

    void insertPiece(Piece* newPiece);
    void display() const;
    void displayLists() const;

    Piece* getHead() const;
    Piece* getTail() const;
    void setHead(Piece* newHead);
    void setTail(Piece* newTail);
};

Piece* generateRandomPiece();

// Global lists for colors and shapes
extern std::vector<Piece*> colorLists[4]; // 4 colors
extern std::vector<Piece*> shapeLists[4]; // 4 shapes

// Function to add a piece to the color and shape lists
void addPieceToLists(Piece* piece, bool insertAtBeginning);

// Function to rotate pieces of a certain color
void rotatePiecesByColor(std::vector<Piece*>& colorList);

// Function to rotate pieces of a certain shape
void rotatePiecesByShape(std::vector<Piece*>& shapeList);

void rotatePiecesByColorOnBoard(  ListGameBoard&, const std::string&);

void rotatePiecesByShapeOnBoard(  ListGameBoard&, const std::string&);

bool checkAndRemoveSameColorPieces(ListGameBoard&); 
#endif
