#pragma once
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

void initializeDeck(Tile* allTiles);
void printColourful(Tile& tile);
bool allTilesDealed(Tile* allTiles);
void dealing_tile_from_deck(Tile* allTiles, Tile& t);
void initializePlayers(Player* players, int n, Tile* allTiles);
void printHandOfPlayer(Player* players, int idx);
void printHandOfPlayerHelper(Player& player);
void printDeck(Deck& d);
int calculateSum(Tile* tiles, int m);
int calculating_the_winner(Player* players, int n);
bool checkingForWinner(Tile* allTiles, Player* players, int n);
bool isWinner(Player& player);

