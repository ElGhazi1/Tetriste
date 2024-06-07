# Tetris-Like Game System

This project is a Tetris-like game implementation in C++. It features a list-based game board, with pieces that can be rotated by color or shape. The game uses double-linked lists to manage pieces on the board and allows for various operations on these pieces.

## Table of Contents

- [Features](#features)
- [Technologies Used](#technologies-used)
- [Installation](#installation)
- [Usage](#usage)
- [File Structure](#file-structure)
- [License](#license)

## Features

- Tetris-like game board using a double-linked list structure
- Piece generation with random colors and shapes
- Rotate pieces by color or shape
- Check and remove pieces of the same color on the board
- Display the game board and lists of pieces

## Technologies Used

- C++ (Core language)
- Windows API for console control (for `_getch()` and `Sleep()` functions)

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/tetris-like-game.git
    cd tetris-like-game
    ```

2. Compile the code:
    - Using g++:
      ```bash
      g++ -o tetris_game main.cpp tetris.cpp -std=c++11
      ```

## Usage

1. **Running the Game:**
    - Run the compiled executable:
      ```bash
      ./tetris_game
      ```

2. **Game Controls:**
    - The game currently uses `_getch()` for capturing keyboard inputs. Modify the code to include specific controls for rotating pieces or other game actions.

## File Structure

.
├── include
│ └── tetris.hpp
├── src
│ └── tetris.cpp
├── main.cpp
├── README.md
└── LICENSE


## File Descriptions

- **tetris.hpp**: Header file containing the declarations for the `Piece` and `ListGameBoard` classes, and related functions.
- **tetris.cpp**: Implementation of the functions declared in `tetris.hpp`.
- **main.cpp**: Entry point of the game, handling the game loop and interactions.
- **LICENSE**: License file for the project.

## Classes and Functions

### Piece Class
- `Piece(std::string s, std::string c)`: Constructor to create a new piece with given shape and color.
- `friend void displayPiece(const Piece* piece)`: Function to display a piece.

### ListGameBoard Class
- `ListGameBoard()`: Constructor to initialize the game board.
- `~ListGameBoard()`: Destructor to clean up the game board.
- `void insertPiece(Piece* newPiece)`: Insert a new piece on the board.
- `void display() const`: Display the game board.
- `void displayLists() const`: Display the lists of pieces by color and shape.

### Functions
- `Piece* generateRandomPiece()`: Generate a random piece with random shape and color.
- `void addPieceToLists(Piece* piece, bool insertAtBeginning)`: Add a piece to the color and shape lists.
- `void rotatePiecesByColor(std::vector<Piece*>& colorList)`: Rotate pieces of a certain color.
- `void rotatePiecesByShape(std::vector<Piece*>& shapeList)`: Rotate pieces of a certain shape.
- `void rotatePiecesByColorOnBoard(ListGameBoard&, const std::string&)`: Rotate pieces of a certain color on the board.
- `void rotatePiecesByShapeOnBoard(ListGameBoard&, const std::string&)`: Rotate pieces of a certain shape on the board.
- `bool checkAndRemoveSameColorPieces(ListGameBoard&)`: Check and remove pieces of the same color on the board.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
