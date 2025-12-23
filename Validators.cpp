//This files contains all the validation needed for the project
#include "Validators.h"
void numberOfPlayersCinLogic(int& n) {
    while (n < 2 || n > 4) {
        std::cout << "You must enter a number between 2 and 4! ";
        std::cin >> n;
    }
}
void validateKinputTilesForMakingCombination(Player& player, int& k) {
    //std::cin >> k;
    while (k < 3 || k > player.number_in_hand) {
        std::cout << "Enter a valid number of tails :) " << '\n';
        std::cin >> k;
    }
}
void validateNumberOfCombinations(Player& player, int& k) {
    while (k < 1 || k > player.number_in_hand / 3) {
        std::cout << "Enter a valid number of combinations :) " << '\n';
        std::cin >> k;
    }
}
void validateNumberOfMoves(int& k) {
    while (k < 1) {
        std::cout << "Enter a valid number of combinations :) " << '\n';
        std::cin >> k;
    }
}
void validateIndx(Player& player, int& idx) {
    while (idx < 0 || idx >= player.number_in_hand) {
        std::cout << "Invalid idx entered - enter a new idx " << '\n';
        std::cin >> idx;
    }
}
//Here we have two moves - c - combinations and r - rearrangement
void validateMove(char& move, char* moves, int len) {

    while (true) {
        bool flag = false;
        for (int i = 0;i < len;i++) {
            if (moves[i] == move) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            std::cout << "Enter a valid char - c or r! ";
            std::cin >> move;
        }
        else break;
    }
}
//validators for decision - c or r
void validateGettingDec(int& dec) {
    while (dec != 0 && dec != 1) {
        std::cout << "Invalid input it must be 0 or 1 ";
        std::cin >> dec;
    }
}


//validating the coordinates of x and y when putting a tile
bool validCoordsTilePuttingInDeck(int& x, int& y, Deck& d, Tile& tile) {
    if (y == 0 && d.deck[x][y + 1].color == tile.color && d.deck[x][y + 1].number == tile.number + 1) return true;
    if (y == d.sizes[x] && d.deck[x][y - 1].color == tile.color && d.deck[x][y - 1].number == tile.number - 1) return true;

    //it must be in the same color as the other ones in the row and sequential or it must be the same number but different color
    if (y == 0 && d.deck[x][y + 1].color != tile.color && d.deck[x][y + 1].number == tile.number) return true;
    if (y == d.sizes[x] && d.deck[x][y - 1].color != tile.color && d.deck[x][y - 1].number == tile.number) return true;
    if (x < 0 || x > d.count) return false;
    else if (y < 0 || y > d.sizes[x])return false;
    if (y != 0 && y != d.sizes[x]) return false;
    return true;
}
bool validCoordsTileGettingInDeck(int& x, int& y, Deck& d, Tile& tile) {

    if (x < 0 || x > d.count - 1) return false;
    else if (y < 0 || y > d.sizes[x] - 1)return false;
    //here the logic is if we want to remove a tile it musn't remain other two subrows of tiles with len < 3
    //for example we cant remove 3 from 1 2 3 4 5 cause we will get 1 2 and 3 4
    if (d.sizes[x] < 4) return false;
    else if (y > 0 && y < 3) return false;
    else if (y == 0) return true;
    else if (y < d.sizes[x] && d.sizes[x] - y - 1 < 3)return false;

    return true;
}
//a high-order function for the different validation functions
void validateOperationOnDeck(int& x, int& y, Tile& tile, Deck& d, bool (*func)(int&, int&, Deck&, Tile&)) {

    while (true) {
        if (func(x, y, d, tile)) break;

        std::cout << "Invalid x and y!" << '\n';
        std::cin >> x >> y;
    }
}

void validationChoosingMove(char& move) {
    std::cout << "Are you going to make combination from your tiles or rearrange the deck? /c or r/ ";
    std::cin >> move;
    char* moves = new char[2];
    moves[0] = 'c';
    moves[1] = 'r';
    validateMove(move, moves, 2);
}
