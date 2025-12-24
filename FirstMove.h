#pragma once
#include "Factory.h"
#include "Validators.h"
#include "GameMove.h"
//first move functions
//getting the Indxs of the tiles that the player wants to add
void gettingIdxs(int k, Player& player, int* indxs);
//creating and checking the combinations
void gettingEachCombination(int* indxs, Player& player, int k, int& y1, Tile** finalCards, int* sizes, int& sum);

void moveOfPlayerFirstMove(Player& player, Tile* allTiles, Deck& d);
void moveOfPlayerInTheGame(Player& player, Tile* allTiles, Deck& d);
//checking for valid first move
void checkingStartingTileCombinationSum(int& sum, Player& player, Tile** finalCards, int* sizes, Deck& d, int& y1, Tile* allTiles);
void gettingCombinationInGame(int* indxs, Player& player, int k, Tile* cards, Deck& d, Tile* allTiles);
//the realiation of the logic of first move
void moveOfPlayerFirstMove(Player& player, Tile* allTiles, Deck& d);
void updateDeck(Tile* cards, Player& player, Deck& d, int k);
