//These are the functions defining the operations on the tiles - adding a tile, removing a tile from a hand or a deck 
#include "TileOperations.h"
//if the player enters an invalid number of players
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


  //function when a player deals tile
void dealingTile(Tile* allTiles, Player& player) {
    Tile tile;
    dealing_tile_from_deck(allTiles, tile);
    addTile(tile, player);
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
