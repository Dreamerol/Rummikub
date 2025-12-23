#pragma once
#include "Factory.h"
void numberOfPlayersCinLogic(int& n);
void validateKinputTilesForMakingCombination(Player& player, int& k);
void validateNumberOfCombinations(Player& player, int& k);
void validateNumberOfMoves(int& k);
void validateIndx(Player& player, int& idx);
void validateMove(char& move, char* moves, int len);
void validateGettingDec(int& dec);
bool validCoordsTilePuttingInDeck(int& x, int& y, Deck& d, Tile& tile);
bool validCoordsTileGettingInDeck(int& x, int& y, Deck& d, Tile& tile);
void validateOperationOnDeck(int& x, int& y, Tile& tile, Deck& d, bool (*func)(int&, int&, Deck&, Tile&));
void validationChoosingMove(char& move);
