#include "tetris.hpp"

Piece::Piece(std::string s, std::string c) : shape(s), color(c), next(nullptr), prev(nullptr) {}

ListGameBoard::ListGameBoard() : head(nullptr), tail(nullptr) {}

ListGameBoard::~ListGameBoard() {
    while (head != nullptr) {
        Piece* temp = head;
        head = head->next;
        delete temp;
    }
}

void ListGameBoard::insertPiece(Piece* newPiece) {
    if (head == nullptr) {
        head = newPiece;
        tail = newPiece;
        newPiece->next = newPiece;
        newPiece->prev = newPiece;
    } else {
        newPiece->next = head;
        newPiece->prev = head->prev;
        head->prev->next = newPiece;
        head->prev = newPiece;
        tail = newPiece;
    }
    // Add the piece to the color and shape lists
    addPieceToLists(newPiece, false); // Insert at the end by default
}

void ListGameBoard::display() const {
    std::cout << "\n\nGame Board:\n<        ";
    if (head != nullptr) {
        const Piece* current = head;
        do {
            displayPiece(current);
            current = current->next;
        } while (current != head);
    }
    std::cout << "        >" << std::endl;
}

void ListGameBoard::displayLists() const {
    std::cout << "\nColor Lists:\n";
    for (int i = 0; i < 4; ++i) {
        std::cout << "Piece " << i + 1 << " (" << colorLists[i].size() << " pieces): ";
        for (const auto& piece : colorLists[i]) {
            displayPiece(piece);
        }
        std::cout << std::endl;
    }

    std::cout << "\nShape Lists:\n";
    for (int i = 0; i < 4; ++i) {
        std::cout << "Shape " << i + 1 << " (" << shapeLists[i].size() << " pieces): ";
        for (const auto& piece : shapeLists[i]) {
            displayPiece(piece);
        }
        std::cout << std::endl;
    }
}

Piece* ListGameBoard::getHead() const {
    return head;
}

Piece* ListGameBoard::getTail() const {
    return tail;
}

void ListGameBoard::setHead(Piece* newHead) {
    head = newHead;
}

void ListGameBoard::setTail(Piece* newTail) {
    tail = newTail;
}

void displayPiece(const Piece* piece) {
    std::cout << "[" << piece->shape << piece->color << "] ";
}

Piece* generateRandomPiece() {
    std::string shapes[] = {"C", "T", "Rond", "L"};
    std::string colors[] = {"Red", "V", "J", "B"};

    return new Piece(shapes[rand() % 4], colors[rand() % 4]);
}

std::vector<Piece*> colorLists[4]; // 4 colors
std::vector<Piece*> shapeLists[4]; // 4 shapes

// Function to add a piece to the color and shape lists
void addPieceToLists(Piece* piece, bool insertAtBeginning) {
    // Find the index of the color and shape in their respective arrays
    int colorIndex = -1;
    int shapeIndex = -1;
    std::string colors[] = {"Red", "V", "J", "B"};
    std::string shapes[] = {"C", "T", "Rond", "L"};

    for (int i = 0; i < 4; ++i) {
        if (colors[i] == piece->color) {
            colorIndex = i;
            break;
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (shapes[i] == piece->shape) {
            shapeIndex = i;
            break;
        }
    }

    if (colorIndex != -1 && shapeIndex != -1) {
        if (insertAtBeginning) {
            colorLists[colorIndex].insert(colorLists[colorIndex].begin(), piece);
            shapeLists[shapeIndex].insert(shapeLists[shapeIndex].begin(), piece);
        } else {
            colorLists[colorIndex].push_back(piece);
            shapeLists[shapeIndex].push_back(piece);
        }
    }
}


// --------------------------------  Faire les rotations aux niveaux des Listes par couleurs / Shapes  -------------------------------- //  

// Function to rotate pieces of a certain color
void rotatePiecesByColor(std::vector<Piece*>& colorList) {
    if (colorList.size() > 1) {
        Piece* temp = colorList.front(); // Store the head of the list
        colorList.erase(colorList.begin()); // Remove the head of the list
        colorList.push_back(temp); // Add the head to the end of the list
    }
}

// Function to rotate pieces of a certain shape
void rotatePiecesByShape(std::vector<Piece*>& shapeList) {
    if (shapeList.size() > 1) {
        Piece* temp = shapeList.front(); // Store the head of the list
        shapeList.erase(shapeList.begin()); // Remove the head of the list
        shapeList.push_back(temp); // Add the head to the end of the list
    }
}

// --------------------------------  Faire les rotations aux niveaux du plateau de jeu lui même par couleurs / Shapes  -------------------------------- //  


// Rotation des pièces par couleur sur le plateau de jeu
void rotatePiecesByColorOnBoard(ListGameBoard& gameBoard, const std::string& color) {

    Piece* currentPiece = gameBoard.getHead();
    Piece* initialPiece = currentPiece;
    Piece* temp;
    // Placer la première pièce rencontré du couleur color dans une variable temporaire.
    while (currentPiece!=initialPiece)
    {
        if (currentPiece->color==color){
            temp = currentPiece;
            break;
        }
        currentPiece = currentPiece->next;
    }


    

}



// --------------------------------  Faire la suppression  -------------------------------- //  

bool checkAndRemoveSameColorPieces(ListGameBoard& gameBoard) {
    Piece* currentPiece = gameBoard.getHead();
    Piece* initialPiece = currentPiece;

    // Parcours des pièces sur le plateau de jeu
    do {
        Piece* prevPiece = currentPiece->prev;
        Piece* nextPiece = currentPiece->next;

        // Vérifier si la pièce actuelle a la même couleur que sa pièce précédente et sa pièce suivante
        if (prevPiece && nextPiece && prevPiece->color == currentPiece->color && nextPiece->color == currentPiece->color) {
            // Supprimer les trois pièces
            if (currentPiece == gameBoard.getHead()) {
                gameBoard.setHead(nextPiece->next);
            }
            if (currentPiece == gameBoard.getTail()) {
                gameBoard.setTail(prevPiece->prev);
            }
            prevPiece->next = nextPiece->next;
            nextPiece->next->prev = prevPiece;

            delete currentPiece;
            delete prevPiece;
            delete nextPiece;

            // Retourner true indiquant que des pièces ont été supprimées
            return true;
        }

        currentPiece = currentPiece->next;
    } while (currentPiece != initialPiece);

    // Vérifier s'il ne reste que trois pièces ayant la même couleur sur le plateau de jeu
    if (gameBoard.getHead() && gameBoard.getHead()->next && gameBoard.getHead()->next->next &&
        gameBoard.getHead()->color == gameBoard.getHead()->next->color &&
        gameBoard.getHead()->next->color == gameBoard.getHead()->next->next->color) {
        // Supprimer les trois pièces
        Piece* head = gameBoard.getHead();
        Piece* next = head->next;
        Piece* nextNext = next->next;

        gameBoard.setHead(nextNext->next);

        delete head;
        delete next;
        delete nextNext;

        // Afficher "You win" et arrêter le jeu
        std::cout << "You win!" << std::endl;
        return true;
    }

    // Aucune pièce n'a été supprimée
    return false;
}

