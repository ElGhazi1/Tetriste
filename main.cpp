#include "tetris.hpp"

int main() {
    srand(time(NULL));

    ListGameBoard gameBoard;
    int piecesInserted = 0;

    // Initialize the game board with 4 unique pieces
    while (piecesInserted < 4) {
        Piece* newPiece = generateRandomPiece();
        gameBoard.insertPiece(newPiece);
        piecesInserted++;
    }

    // Premier Affichage du Plateau du jeu.
    Piece* currentPiece = generateRandomPiece();
    std::cout << "\nNext Piece:";
    displayPiece(currentPiece);
    std::cout << std::endl;
    gameBoard.display();
    gameBoard.displayLists(); // Display lists

    while (true) {
        if (_kbhit()) {
            char key = _getch();
            if ((key == 75 || key == 77) && piecesInserted < MAX_PIECES) {
                if (key == 75) { // Left arrow key
                    // Add the new piece to the left
                    currentPiece->next = gameBoard.getHead();
                    currentPiece->prev = gameBoard.getHead()->prev;
                    gameBoard.getHead()->prev->next = currentPiece;
                    gameBoard.getHead()->prev = currentPiece;
                    gameBoard.setHead(currentPiece);
                    // Add the piece to the beginning of lists
                    addPieceToLists(currentPiece, true);
                } else if (key == 77) { // Right arrow key
                    // Add the new piece to the right (before the first piece)
                    currentPiece->next = gameBoard.getHead();
                    currentPiece->prev = gameBoard.getHead()->prev;
                    gameBoard.getHead()->prev->next = currentPiece;
                    gameBoard.getHead()->prev = currentPiece;
                    gameBoard.setTail(currentPiece);
                    // Add the piece to the end of lists
                    addPieceToLists(currentPiece, false);
                }

                // Vérifiez et supprimez les pièces ayant la même couleur
                if (checkAndRemoveSameColorPieces(gameBoard)) {
                    system("cls");
                    gameBoard.display();
                    gameBoard.displayLists(); // Display lists
                    std::cout << "\n";
                    piecesInserted--;
                }

                system("cls");
                currentPiece = generateRandomPiece();
                std::cout << "\nNext Piece:";
                displayPiece(currentPiece);
                std::cout << std::endl;

                gameBoard.display();
                gameBoard.displayLists(); // Display lists

                std::cout << "\n";
                piecesInserted++;
            } else if (key == 'n' || key == 'N') { // Key E
                if (gameBoard.getHead() != nullptr) {
                    gameBoard.setHead(gameBoard.getHead()->prev);
                    system("cls");

                    gameBoard.display();
                    gameBoard.displayLists(); // Display lists
                }
            } else if (key == 'p' || key == 'P') { // Key Q
                break;
            } else if (key == 'q' || key == 'Q') { // Key N
                rotatePiecesByColorOnBoard(gameBoard,"Red");
                rotatePiecesByColor(colorLists[0]); // Rotate pieces of color Red
                system("cls");

                gameBoard.display();
                gameBoard.displayLists(); // Display lists
            } else if (key == 'd' || key == 'D') { // Key A
                rotatePiecesByColor(colorLists[2]); // Rotate pieces of color J
                system("cls");

                gameBoard.display();
                gameBoard.displayLists(); // Display lists
            } else if (key == 's' || key == 'S') { // Key B
                rotatePiecesByColor(colorLists[1]); // Rotate pieces of color V
                system("cls");

                gameBoard.display();
                gameBoard.displayLists(); // Display lists
            } else if (key == 'f' || key == 'F') { // Key C
                rotatePiecesByColor(colorLists[3]); // Rotate pieces of color B
                system("cls");

                gameBoard.display();
                gameBoard.displayLists(); // Display lists
            } else if (key == 'w' || key == 'W') { // Key D
                // rotatePiecesByShapeOnBoard(gameBoard, "C");
                rotatePiecesByShape(shapeLists[0]); // Rotate pieces of shape C
                system("cls");

                gameBoard.display();
                gameBoard.displayLists(); // Display lists
            } else if (key == 'x' || key == 'X') { // Key E
                rotatePiecesByShape(shapeLists[1]); // Rotate pieces of shape T
                system("cls");

                gameBoard.display();
                gameBoard.displayLists(); // Display lists
            } else if (key == 'c' || key == 'C') { // Key F
                rotatePiecesByShape(shapeLists[2]); // Rotate pieces of shape Rond
                system("cls");

                gameBoard.display();
                gameBoard.displayLists(); // Display lists
            } else if (key == 'v' || key == 'V') { // Key G
                rotatePiecesByShape(shapeLists[3]); // Rotate pieces of shape L
                system("cls");

                gameBoard.display();
                gameBoard.displayLists(); // Display lists
            }
            // Add more rotation keys as needed...
        }
        Sleep(100);
    }

    while (gameBoard.getHead() != nullptr) {
        Piece* temp = gameBoard.getHead();
        gameBoard.setHead(gameBoard.getHead()->next);
        delete temp;
    }

    return 0;
}
