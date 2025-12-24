// Rummikub.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Factory.h"
#include "Validators.h"
#include "GameMove.h"
#include "TileOperations.h"
#include "FirstMove.h"
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

