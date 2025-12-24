//Here are the functions realizing the logic for the different main game moves - making combinations, rearranging the deck
#include "GameMove.h"
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
void puttingManyTiles(int& numberGotTiles1, int& numberGotTiles2, Player& player, int*& lines, Deck& d, Tile*& finalCards) {
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
void gettingFromDeckfunc(int& numberGotTiles1, Tile*& gotTilesDeck, int*& lines, Deck& d) {
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


//the function implementing the rearrange logic
void rearrangeFunctionLogic(Player& player, Deck& d) {
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
