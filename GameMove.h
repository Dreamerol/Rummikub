#pragma once
#include "Factory.h"
#include "Validators.h"
#include "TileOperations.h"

void puttingOnlyOneTile(Player& player, Deck& d);
void puttingManyTiles(int& numberGotTiles1, int& numberGotTiles2, Player& player, int*& lines, Deck& d, Tile*& finalCards);
void CombinationLogicFunc(Player& player, Deck& d, Tile*& allTiles);
void createFinalCardsToAddToDeck(Tile*& finalCards, int& numberGotTiles1, int& numberGotTiles2, Tile*& gotTilesDeck, Tile*& gotTilesHand);
void gettingFromDeckfunc(int& numberGotTiles1, Tile*& gotTilesDeck, int*& lines, Deck& d);
void gettingTilesFromHandfunc(int& numberGotTiles2, Player& player, Tile*& gotTilesHand);
void rearrangeFunctionLogic(Player& player, Deck& d);
void moveOfPlayerInTheGame(Player& player, Tile* allTiles, Deck& d);

