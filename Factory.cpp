//This file contains all the logic for initialization and creation of the structs of player, deck, tiles and so on
#include "Factory.h"
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
