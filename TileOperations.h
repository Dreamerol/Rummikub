#pragma once
#include "Factory.h"
#include "Validators.h"
bool Move();
void addTile(Tile tile, Player& player);
void removeTileByIdx(Tile* tiles, int idx, Player& player);
bool EqualTiles(Tile& t1, Tile& t2);
void removeTile(Player& player, Tile tile);
int sumOfPassedTilesFirstMove(int* indxs, int k, Player& player);
void swapTiles(Tile& tile1, Tile& tile2);
void swapInt(int& a, int& b);
void SelectionSortTiles(Tile* playerTile, int* indxs, int size);
void SelectionSortTilesPassedTiles(Tile* playerTile, int size);
bool sameColor(int* indxs, int k, Player& player);
bool sameColorPassedTiles(int k, Tile* tiles, Player& player);
bool sameNumbers(int k, Player& player, int* indxs);
bool sameNumbersPassedTiles(int k, Tile* cards);
void addCombinationToDeck(Deck& d, Tile* newComb, int k);
void dealingTile(Tile* allTiles, Player& player);

//getting the objects behind those coordinates
Tile getTileFromDeck(int x, int y, Deck& d);
Tile getTileFromHand(int idx, Player& player);
void addTileToDeck(int x, int y, Deck& d, Tile& newTile);
void removeTileFromDeck(int row, Tile& tile, Deck& d);
void gettingCombinationInGame(int* indxs, Player& player, int k, Tile* cards, Deck& d, Tile* allTiles);
void updateDeck(Tile* cards, Player& player, Deck& d, int k);
void gettingIdxs(int k, Player& player, int* indxs);
