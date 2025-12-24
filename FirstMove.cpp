//Functions for the first round of the game - checking for sum >= 30 od the passed tiles from the player
//to the deck - here the specific part is that we will keep the indexes, because in the end we want to see if the combination is valid
//if is not valid we will do nothing
//but if is valid thanks to the fact that we have kept the indexes of the taken tiles than we can remove them
//because we have kept their indexes and by their indxs we can reach the tile
#include "FirstMove.h"
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

//a function to remove the added tiles to the deck from our hand
void updateDeck(Tile* cards, Player& player, Deck& d, int k) {
    for (int h = 0;h < k;h++) {
        removeTile(player, cards[h]);
    }
    addCombinationToDeck(d, cards, k);

}
