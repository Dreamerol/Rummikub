// Rummikub.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>

#include <iostream>
#include <cstdlib>
//For Joker I will use the number 14 - so we have numbers from 1 to 13
//but if we have dealed joker it will be numbered with the num 14
//I will use int for colors because we have blue and black which starts with the same letter
//so it will be confusing, also using char array for the name of colors will use a lot of memory
//so i will use numbers, so

//0 - red
//1 - black
//2 - blue
//3 - yellow
struct Tile {
    int number = 0;
    int color = 0;
    bool isDealed = false;
};

struct Player {
    int ID = 0;
    Tile* tiles = nullptr;
    int number_in_hand = 0;
};
struct Deck {
    int count = 0;
    Tile** deck = nullptr;
    int* sizes = nullptr;

};
int const ALL_TILES = 106;
int const ALL_NUMBERS = 13;
int const NUMBER_OF_STARTING_TILES = 14;
int const RED_COLOR = 0;
int const BLACK_COLOR = 1;
int const BLUE_COLOR = 2;
int const YELLOW_COLOR = 3;

//how many times we will use the collection 1-13 for all the types tiles
int const TIMES_REPEATED_COLLECTION_TILES = 2;
//function - initializing the deck with all tiles
void initializeDeck(Tile* allTiles) {

    int j = 0;
    for (int l = 0;l < TIMES_REPEATED_COLLECTION_TILES;l++) {
        for (int k = RED_COLOR;k <= YELLOW_COLOR;k++) {
            for (int i = 1;i <= ALL_NUMBERS;i++) {
                allTiles[j].number = i;
                allTiles[j].color = k;
                //we haven't dealed any tail yet
                allTiles[j].isDealed = false;
                j++;
            }
        }
    }
    //here we initialize the jokers
    allTiles[104].number = 14;
    allTiles[104].color = 0;
    allTiles[105].number = 14;
    allTiles[105].color = 1;
}

//helper function to print in different colors
//it could be a little bit confusing, but the background is in color black, so I decided the black
//tiles to be printed in the console in white color, otherwise they wouldn't be seen - if i print them in black
//color on a black background

void printColourful(Tile& tile) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    switch (tile.color) {
    case 0:SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);break;
    case 2:SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);break;
    case 3:SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);break;
    }
    std::cout << tile.number << ' ';
    //reseting the color
    SetConsoleTextAttribute(h, 7);
}
//checking whether all the tails are dealed
bool allTilesDealed(Tile* allTiles) {
    for (int i = 0;i < ALL_TILES;i++) {
        if (!allTiles[i].isDealed) return false;
    }
    return true;
}
int player_with_no_cards(Player* players, int n) {
    for (int i = 0;i < n;i++) {
        if (players[i].number_in_hand == 0) return i;
    }
    return -1;
}
void dealing_tile_from_deck(Tile* allTiles, Tile& t) {
    //if all tiles are already dealed we cannot deal more tiles
    if (allTilesDealed(allTiles)) {
        std::cout << "You cannot deal more tiles!" << '\n';
        return;
    }
    while (true) {
        int r = rand() % ALL_TILES;
        if (allTiles[r].isDealed) continue;
        else {
            allTiles[r].isDealed = true;
            t = allTiles[r];
            break;
        }

    }

}

void initializePlayers(Player* players, int n, Tile* allTiles) {
    for (int i = 0;i < n;i++) {
        players[i].ID = i + 1;
        players[i].tiles = new Tile[NUMBER_OF_STARTING_TILES];
        int k = 0;
        for (int j = 0;j < NUMBER_OF_STARTING_TILES;j++) {
            dealing_tile_from_deck(allTiles, players[i].tiles[j]);
        }
        players[i].number_in_hand = NUMBER_OF_STARTING_TILES;
    }
}
//if the player enters an invalid number of players
void numberOfPlayersCinLogic(int& n) {
    while (n < 2 || n > 4) {
        std::cout << "You must enter a number between 2 and 4! ";
        std::cin >> n;
    }
}
void printHandOfPlayer(Player* players, int idx) {
    std::cout << players[idx].number_in_hand << ' ';
    std::cout << "ID: " << players[idx].ID << '\n';
    for (int j = 0;j < players[idx].number_in_hand;j++) {
        printColourful(players[idx].tiles[j]);
    }
    std::cout << '\n';
}
void printHandOfPlayerHelper(Player& player) {
    std::cout << "ID: " << player.ID << '\n';
    for (int j = 0;j < player.number_in_hand;j++) {
        printColourful(player.tiles[j]);
    }
    std::cout << '\n';
}
bool Move() {
    std::cout << "Are you going to deal or put tiles on the deck/if you deal type t for true, else type f for false ";
    char move;
    std::cin >> move;
    while (move != 'f' && move != 't') {
        std::cout << "You must enter t/f! ";
        std::cin >> move;
    }
    return (move == 't');
}
int calculateSum(Tile* tiles, int m) {
    int sum = 0;
    for (int i = 0;i < m;i++) {
        sum += tiles[i].number;
    }
    return sum;
}
//claculating and returning the idx of the player with the least score
int calculating_the_winner(Player* players, int n) {
    int minValue = 1e9;
    int minIdx = -1;
    for (int i = 0;i < n;i++) {
        int sum = calculateSum(players[i].tiles, players[i].number_in_hand);
        if (sum < minValue) {
            minValue = sum;
            minIdx = i;
        }
    }
    return minIdx;
}
void addTile(Tile tile, Player& player) {
    int m = player.number_in_hand;
    Tile* newtiles = new Tile[m + 1];
    for (int i = 0;i < m;i++) {
        newtiles[i] = player.tiles[i];
    }
    newtiles[m] = tile;
    delete[] player.tiles;
    player.tiles = newtiles;
    player.number_in_hand++;


}
void removeTileByIdx(Tile* tiles, int idx, Player& player) {
    int m = player.number_in_hand;
    if (m == 1) {
        delete[] tiles;
        return;
    }
    Tile* newTiles = new Tile[m - 1];
    int j = 0;
    for (int i = 0;i < m;i++) {
        if (i == idx)continue;
        newTiles[j++] = tiles[i];
    }
    delete[] tiles;
    tiles = newTiles;
    player.number_in_hand--;
}
bool EqualTiles(Tile& t1, Tile& t2) {
    return (t1.number == t2.number && t1.color == t2.color);
}
void removeTile(Player& player, Tile tile) {
    
    int removeIdx = -1;
    int m = player.number_in_hand;
    for (int i = 0;i < m;i++) {
        if (EqualTiles(player.tiles[i], tile)) {
            removeIdx = i;
            break;
        }
    }
    if (removeIdx == -1) return; 
    if (m == 1) {
        delete[] player.tiles;
        player.tiles = nullptr;
        player.number_in_hand = 0;
        return;
    }
    Tile* newTiles = new Tile[m - 1];
    int j = 0;
    for (int i = 0;i < m;i++) {
        if (removeIdx == i) continue;
        newTiles[j++] = player.tiles[i];
    }
    delete[] player.tiles;
    player.tiles = newTiles;
    player.number_in_hand--;
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
int sumOfPassedTilesFirstMove(int* indxs, int k, Player& player) {
    int sum = 0;
    for (int i = 0;i < k;i++) {
        sum += player.tiles[indxs[i]].number;
    }

    return sum;
}
void swapTiles(Tile& tile1, Tile& tile2) {
    Tile h = tile1;
    tile1 = tile2;
    tile2 = h;

}
void swapInt(int& a, int& b) {
    int h = a;
    a = b;
    b = h;
}
void SelectionSortTiles(Tile* playerTile, int* indxs, int size) {
    for (int i = 0;i < size - 1;i++) {
        int minidx = i;
        for (int j = i + 1;j < size;j++) {
            if (playerTile[indxs[i]].number > playerTile[indxs[j]].number) {
                minidx = j;
            }
        }
        if (minidx != i) {
            swapInt(indxs[i], indxs[minidx]);
        }
    }
}
void SelectionSortTilesPassedTiles(Tile* playerTile, int size) {
    for (int i = 0;i < size - 1;i++) {
        int minidx = i;
        for (int j = i + 1;j < size;j++) {
            if (playerTile[i].number > playerTile[j].number) {
                minidx = j;
            }
        }
        if (minidx != i) {
            swapTiles(playerTile[i], playerTile[minidx]);
        }
    }
}
//functions to check whether the combination is valid
bool sameColor(int* indxs, int k, Player& player) {
    /*  Tile* currentTiles = new Tile[k];
      for (int i = 0;i < k;i++) {
          currentTiles[i] = player.tiles[indxs[i]];
      }*/
      /* for (int i = 0;i < k;i++) {
        std::cout<<player.tiles[indxs[i]].number << ' ';
    }*/

    SelectionSortTiles(player.tiles, indxs, k);
    for (int i = 1;i < k;i++) {
        if (player.tiles[indxs[i - 1]].number + 1 != player.tiles[indxs[i]].number
            && player.tiles[indxs[i - 1]].number != 14 &&
            player.tiles[indxs[i]].number != 14) return false;
        else if (player.tiles[indxs[i - 1]].color != player.tiles[indxs[i]].color) return false;
    }
    return true;
}
bool sameColorPassedTiles(int k, Tile* tiles, Player& player) {
    SelectionSortTilesPassedTiles(player.tiles, k);
    for (int i = 1;i < k;i++) {
        if (player.tiles[i - 1].number + 1 != player.tiles[i].number
            && player.tiles[i - 1].number != 14 &&
            player.tiles[i].number != 14) return false;
        else if (player.tiles[i - 1].color != player.tiles[i].color) return false;
    }
    return true;
}
bool sameNumbers(int k, Player& player, int* indxs) {
    if (k > 4)return false;
    for (int i = 0;i < k - 1;i++) {
        for (int j = i + 1;j < k;j++) {
            if (player.tiles[indxs[i]].number != player.tiles[indxs[j]].number &&
                player.tiles[indxs[i]].number != 14 &&
                player.tiles[indxs[j]].number != 14) return false;
            else if (player.tiles[indxs[i]].color == player.tiles[indxs[j]].color) return false;
        }
    }
    return true;
}
bool sameNumbersPassedTiles(int k, Tile* cards) {
    if (k > 4)return false;
    for (int i = 0;i < k - 1;i++) {
        for (int j = i + 1;j < k;j++) {
            if (cards[i].number != cards[j].number &&
                cards[i].number != 14 &&
                cards[j].number != 14) return false;
            else if (cards[i].color == cards[j].color) return false;
        }
    }
    return true;
}


void addCombinationToDeck(Deck& d, Tile* newComb, int k) {
    int count = d.count;
    Tile** tiles = new Tile * [count + 1];
    if (count != 0) {

        for (int i = 0;i < count;i++) {
            tiles[i] = new Tile[d.sizes[i]]();
            for (int j = 0;j < d.sizes[i];j++) {
                tiles[i][j] = d.deck[i][j];
            }
        }
        for (int i = 0;i < count;i++) {
            delete[] d.deck[i];
        }
        delete[] d.deck;
    }
    tiles[count] = new Tile[k]();
    for (int y = 0;y < k;y++) {
        tiles[count][y] = newComb[y];

    }
    int* newSizes = new int[count + 1];
    for (int i = 0;i < count;i++) {
        newSizes[i] = d.sizes[i];

    }
    newSizes[count] = k;
    
    if (d.sizes) delete[] d.sizes;
    d.sizes = newSizes;
    d.count++;
    d.deck = tiles;
}

/*for (int i = 0;i < count;i++) {
    for (int j = 0;j < ALL_NUMBERS;j++) {
        tiles[i][j] = d.deck[i][j];
    }
}*/

/*  for (int i = 0;i < count;i++) {
      tiles[i] = d.deck[i];
  }*/

void printDeck(Deck& d) {
    std::cout << "DECK" << '\n';
    std::cout << "-----------------------------------------------------------------" << '\n';
    for (int i = 0;i < d.count;i++) {
        int j = 0;
        for (int j = 0;j < d.sizes[i];j++) {

            printColourful(d.deck[i][j]);
        }
        /*  while (d.deck[i][j].number != 0) {
              printColourful(d.deck[i][j]);
              j++;
          }*/

        std::cout << '\n';
    }
    std::cout << "-----------------------------------------------------------------" << '\n';

}
//function when a player deals tile
void dealingTile(Tile* allTiles, Player& player) {
    Tile tile;
    dealing_tile_from_deck(allTiles, tile);
    addTile(tile, player);
}
//----------------------------------------------------------------
//first move functions
//getting the Indxs of the tiles that the player wants to add
void gettingIdxs(int k, Player& player, int* indxs) {
    for (int j = 0;j < k;j++) {
        int idx;
        std::cin >> idx;
        validateIndx(player, idx);
        indxs[j] = idx;
    }
}
//creating and checking the combinations
void gettingEachCombination(int* indxs, Player& player, int k, int& y1, Tile** finalCards, int* sizes, int& sum) {
    if (sameColor(indxs, k, player) || sameNumbers(k, player, indxs)) {
        Tile* cards = new Tile[k];
        for (int j = 0;j < k;j++) {
            cards[j] = player.tiles[indxs[j]];

        }

        finalCards[y1] = cards;
        sizes[y1] = k;
        sum += sumOfPassedTilesFirstMove(indxs, k, player);
        y1++;

    }
    else {

        std::cout << "Invalid combination!" << '\n';

    }
}

void moveOfPlayerFirstMove(Player& player, Tile* allTiles, Deck& d);
void moveOfPlayerInTheGame(Player& player, Tile* allTiles, Deck& d);
//checking for valid first move
void checkingStartingTileCombinationSum(int& sum, Player& player, Tile** finalCards, int* sizes, Deck& d, int& y1, Tile* allTiles) {

    if (sum >= 30) {
  
        for (int u = 0;u < y1;u++) {
            for (int h = 0;h < sizes[u];h++) {
                //we remove the tiles that we want to add to the deck
                removeTile(player, finalCards[u][h]);
            }
            //we add the combination to the deck
            addCombinationToDeck(d, finalCards[u], sizes[u]);
        }
        printHandOfPlayerHelper(player);

    }
    else {
        std::cout << "Invalid game move! You can deal or try again to make combination!" << '\n';
        //if the move was invalid we return to the beggining
        moveOfPlayerFirstMove(player, allTiles, d);

    }
}
void gettingCombinationInGame(int* indxs, Player& player, int k, Tile* cards, Deck& d, Tile* allTiles) {
    if (sameColor(indxs, k, player) || sameNumbers(k, player, indxs)) {

        for (int j = 0;j < k;j++) {
            cards[j] = player.tiles[indxs[j]];
        }
    }
    else {
        std::cout << "Invalid combination!" << '\n';
        moveOfPlayerInTheGame(player, allTiles, d);
    }
}
//the realiation of the logic of first move
void moveOfPlayerFirstMove(Player& player, Tile* allTiles, Deck& d)
{
    std::cout << "Move of player " << player.ID << '\n';
    printHandOfPlayerHelper(player);
    //if the player answers true - he deals tile
    if (Move()) {
        dealingTile(allTiles, player);
    }
    else
    {
        int sum = 0;
        std::cout << "How many combinations will you make? ";
        int combs;
        std::cin >> combs;
        validateNumberOfCombinations(player, combs);
        Tile** finalCards = new Tile * [combs];
        int* sizes = new int[combs];
        int y1 = 0;
        for (int y = 0;y < combs;y++) {
            std::cout << "How many tiles will you put in the deck? ";
            int k;
            std::cin >> k;
            validateKinputTilesForMakingCombination(player, k);
            int* indxs = new int[k];

            gettingIdxs(k, player, indxs);
            gettingEachCombination(indxs, player, k, y1, finalCards, sizes, sum);
            delete[] indxs;
            
        }
        checkingStartingTileCombinationSum(sum, player, finalCards, sizes, d, y1, allTiles);
        delete[] sizes;
        for (int i = 0;i < combs;i++) {
            delete[] finalCards[i];
        }
        delete[] finalCards;
        
        
    }

}
//game - functions
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
//a function to remove the added tiles to the deck from our hand
void updateDeck(Tile* cards, Player& player, Deck& d, int k) {
    for (int h = 0;h < k;h++) {
        removeTile(player, cards[h]);
    }
    addCombinationToDeck(d, cards, k);

}
//validating the coordinates of x and y when putting a tile
bool validCoordsTilePuttingInDeck(int& x, int& y, Deck& d,Tile& tile) {
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
void validateOperationOnDeck(int& x, int& y, Tile& tile, Deck& d, bool (*func)(int& , int& , Deck& ,Tile&)) {
    
    while (true) {
        if (func(x, y, d, tile)) break;
        
        std::cout << "Invalid x and y!" << '\n';
        std::cin >> x >> y;
    }
}
//getting the objects behind those coordinates
Tile getTileFromDeck(int x, int y, Deck& d) {
    return d.deck[x][y];
}
Tile getTileFromHand(int idx, Player& player) {
    return player.tiles[idx];
}

void removeTileFromDeck(int row, Tile& tile, Deck& d) {
   
    Tile* newTiles = new Tile[d.sizes[row] - 1];
    int j = 0;
    for (int i = 0;i < d.sizes[row];i++) {
        if (EqualTiles(d.deck[row][i], tile)) continue;
        newTiles[j++] = d.deck[row][i];
    }
    delete[] d.deck[row];
    d.sizes[row]--;
    d.deck[row] = newTiles;
}
void addTileToDeck(int x, int y, Deck& d, Tile& newTile) {
    Tile* newTiles = new Tile[d.sizes[x] + 1];

    int j = 0;
    if (y == 0) newTiles[j++] = newTile;
    for (int i = 0;i < d.sizes[x];i++) {
        newTiles[j++] = d.deck[x][i];
    }
    if (y == d.sizes[x]) newTiles[j++] = newTile;
    delete[] d.deck[x];
    d.sizes[x]++;
    d.deck[x] = newTiles;
}
void validateGettingDec(int& dec) {
    while (dec != 0 && dec != 1) {
        std::cout << "Invalid input it must be 0 or 1 ";
        std::cin >> dec;
    }
}
//functions for moves in the game
//here is the logic for ptting one tile
void puttingOnlyOneTile(Player& player, Deck& d) {
    std::cout << "Enter the idx of the tile you want to put ";
    int numberOfTile;
    std::cin >> numberOfTile;
    validateIndx(player, numberOfTile);
    Tile tile = player.tiles[numberOfTile];
    std::cout << "On each row/col will you put tile?";
    int x, y;
    std::cin >> x >> y;

    validateOperationOnDeck(x, y, tile, d, validCoordsTilePuttingInDeck);

    addTileToDeck(x, y, d, tile);
    removeTile(player, tile);
}
//here is the logic for putting many tiles
void puttingManyTiles(int& numberGotTiles1, int& numberGotTiles2,Player& player, int*& lines, Deck& d, Tile*& finalCards) {
    if (numberGotTiles1 + numberGotTiles2 == 0) {
        /* std::cout << numberGotTiles1 << ' ' << numberGotTiles2 << '\n';*/
        std::cout << "You can't put combination, because you haven't." << '\n';
        return;
    }
    int allCards = numberGotTiles1 + numberGotTiles2;
    if (sameNumbersPassedTiles(allCards, finalCards) || sameColorPassedTiles(allCards, finalCards, player)) {

        addCombinationToDeck(d, finalCards, allCards);
       
        for (int i = 0;i < numberGotTiles1;i++) {
            
            removeTileFromDeck(lines[i], finalCards[i], d);
        }

        for (int j = numberGotTiles1;j < allCards;j++) {
            removeTile(player, finalCards[j]);
        }
        // printHandOfPlayerHelper(player);

    }
}
//thw function for making combinations
void CombinationLogicFunc(Player& player, Deck& d, Tile*& allTiles) {
    std::cout << "How many combinations will you make? ";
    int combs;
    std::cin >> combs;
    validateNumberOfCombinations(player, combs);
    Tile** finalCards = new Tile * [combs];


    for (int y = 0;y < combs;y++) {
        std::cout << "How many tiles will you put in the deck? ";
        int k;
        std::cin >> k;
        validateKinputTilesForMakingCombination(player, k);
        int* indxs = new int[k];

        gettingIdxs(k, player, indxs);
        Tile* cards = new Tile[k];
        gettingCombinationInGame(indxs, player, k, cards, d, allTiles);
        updateDeck(cards, player, d, k);
        printHandOfPlayerHelper(player);
    }

}
//combining all the dealed from the deck tiles - all the tiles we got
void createFinalCardsToAddToDeck(Tile*& finalCards, int& numberGotTiles1, int& numberGotTiles2, Tile*& gotTilesDeck, Tile*& gotTilesHand) {
    std::cout << "Are you putting one or many cards! Enter 0 - many and 1 - one " << '\n';
    std::cout << numberGotTiles1 << ' ' << numberGotTiles2 << '\n';
    int allCards = numberGotTiles1 + numberGotTiles2;
    finalCards = new Tile[numberGotTiles1 + numberGotTiles2];
    int j = 0;
    for (int i = 0;i < numberGotTiles1;i++) {
        finalCards[j++] = gotTilesDeck[i];
    }
    for (int i = 0;i < numberGotTiles2;i++) {
        finalCards[j++] = gotTilesHand[i];
    }
}
//a function to get from the deck by coordinates
void gettingFromDeckfunc(int& numberGotTiles1,Tile*& gotTilesDeck, int*& lines, Deck& d) {
    std::cout << "How many will you get? ";

    std::cin >> numberGotTiles1;
    validateNumberOfMoves(numberGotTiles1);
    gotTilesDeck = new Tile[numberGotTiles1];
    lines = new int[numberGotTiles1];
    for (int i = 0;i < numberGotTiles1;i++) {
        std::cout << "From each row/col will you get tile? ";
        int x, y;
        std::cin >> x >> y;
        gotTilesDeck[i] = getTileFromDeck(x, y, d);
        validateOperationOnDeck(x, y, gotTilesDeck[i], d, validCoordsTileGettingInDeck);



        lines[i] = x;
    }
}
void gettingTilesFromHandfunc(int& numberGotTiles2, Player& player, Tile*& gotTilesHand) {
    std::cout << "How many will you get? ";

    std::cin >> numberGotTiles2;
    validateNumberOfMoves(numberGotTiles2);
    gotTilesHand = new Tile[numberGotTiles2];
    for (int i = 0;i < numberGotTiles2;i++) {
        std::cout << "From each idx will you get tile? ";
        int x;
        std::cin >> x;
        validateIndx(player, x);
        gotTilesHand[i] = getTileFromHand(x, player);
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
//the function implementing the rearrange logic
void rearrangeFunctionLogic(Player& player, Deck& d){
    std::cout << "How many commands will you write? ";
    int l;
    std::cin >> l;
    validateNumberOfMoves(l);
    Tile* gotTilesDeck = nullptr;
    Tile* gotTilesHand = nullptr;
    int* lines = nullptr;
    int numberGotTiles1 = 0;
    int numberGotTiles2 = 0;
    for (int j = 0;j < l;j++) {
        std::cout << "What will you do? get tile - g, or put tile - p? ";
        char comm;
        std::cin >> comm;
        char* commands = new char[2];
        commands[0] = 'g'; //get from deck
        commands[1] = 'p'; //put on the deck

        validateMove(comm, commands, 2);
        if (comm == 'g') {
            std::cout << "Are you getting from deck or from hand! Enter 0 - deck and 1 - hand" << '\n';
            int dec;
            std::cin >> dec;
            validateGettingDec(dec);
            if (dec == 0) {
                gettingFromDeckfunc(numberGotTiles1, gotTilesDeck, lines, d);
            }
            else if (dec == 1) {
                gettingTilesFromHandfunc(numberGotTiles2, player, gotTilesHand);
            }
        }
        else if (comm == 'p') {
            Tile* finalCards = nullptr;
            createFinalCardsToAddToDeck(finalCards, numberGotTiles1, numberGotTiles2, gotTilesDeck, gotTilesHand);
            int dec;
            std::cin >> dec;
            validateGettingDec(dec);
            if (dec == 0) puttingManyTiles(numberGotTiles1, numberGotTiles2, player, lines, d, finalCards);
            else puttingOnlyOneTile(player, d);
            delete[] finalCards;
        }
    }
    delete[] lines;
    delete[] gotTilesDeck;
    delete[] gotTilesHand;
    
}
//the actual function for the moves of the gamers
void moveOfPlayerInTheGame(Player& player, Tile* allTiles, Deck& d)
{

    printDeck(d);
    std::cout << "Move of player " << player.ID << '\n';
    printHandOfPlayerHelper(player);
    if (Move()) {
        dealingTile(allTiles, player);
    }
    else
    {
        std::cout << "How many types of moves will you make? ";
        int moves;
        std::cin >> moves;
        validateNumberOfMoves(moves);
        for (int i = 0;i < moves;i++) {
            char move;
            validationChoosingMove(move);
            if (move == 'c') {
                CombinationLogicFunc(player, d, allTiles);

            }
            else if (move == 'r') {
                rearrangeFunctionLogic(player, d);
            }


        }

    }

}
//if all the tiles are dealed we get the idx of he player with the least score
bool checkingForWinner(Tile* allTiles, Player* players, int n) {
    if (allTilesDealed(allTiles)) {
        int idxWinner = calculating_the_winner(players, n);
        std::cout << "The winner is " << players[idxWinner].ID << '\n';
        return true;
    }

}
//another way to check for a winner if he has no tiles left
bool isWinner(Player& player) {
    return player.number_in_hand == 0;
}
int main()
{

    //initializing all the numbers in all 4 colors
    Tile allTiles[ALL_TILES];
    initializeDeck(allTiles);
   
    std::cout << "Welcome to Rummikub!" << '\n';
    std::cout << "How many players are going to play? /between 2 and 4/ ";
    int n;
    std::cin >> n;
    numberOfPlayersCinLogic(n);
    Player* players = new Player[n];
    initializePlayers(players, n, allTiles);

    //checking for right initialization of the deck
  /* for (int i = 0;i < 106;i++) {
       printColourful(allTiles[i]);
   }*/

    //checking for the initialization logic of the players
    /*for (int i = 0;i < n;i++) {
        printHandOfPlayer(players, i);
    }*/

    //the logic is a bit different for first and second move so that's why we use flag firstMove
    bool firstMove = true;
    Deck d;
    d.sizes = nullptr;
    d.deck = nullptr;
   
    while (true) {

        if (firstMove) {
            for (int i = 0;i < n;i++) {
                moveOfPlayerFirstMove(players[i], allTiles, d);
            }
            printDeck(d);
        }
        firstMove = false;
        if (checkingForWinner(allTiles, players, n)) break;
        //checking for no tiles
        for (int i = 0;i < n;i++) {
            //on each move we check if the player has already used his tiles
            if (isWinner(players[i])) {
                std::cout << "The winner is player " << players[i].ID << '\n';
                break;
            }
            moveOfPlayerInTheGame(players[i], allTiles, d);
        }

    }
}


/*printHandOfPlayer(players, 0);
printHandOfPlayer(players, 1);*/

//printHandOfPlayer(players, 0);
   //Tile tile;
   //tile.number = 10;
   //tile.color = 3;

   ////removeTile(players[0], tile);
   //addTile(tile, players[0]);
   //printHandOfPlayer(players, 0);

  //if tile.number == 0 this means that we haven't dealed anything
        //if (tile.number == 0) {
        //    std::cout << "You must play!";
        //    //func
        //}
   /* std::cout << players[i].number_in_hand;*/
         //std::cout << sum << ' ';


 /*  d.sizes = new int[1];
      d.sizes[0] = 2;
      d.deck = new Tile * [1];
      d.deck[0] = new Tile[2];
      d.count++;
      Tile tile1;
      tile1.number = 8;
          tile1.color = 0;
      Tile tile2;
          tile2.number = 7;
          tile2.color = 0;
          d.deck[0][0] = tile1;
          d.deck[0][1] = tile2;
          printDeck(d);
          remooveTileFromDeck(0, tile1, d);

          printDeck(d);
          addTileToDeck(0, 0, d, tile1);
          printDeck(d);*/

