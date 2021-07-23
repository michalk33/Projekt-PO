#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

#include "enums.hpp"
#include "consts.hpp"
#include "tile.hpp"
#include "entity.hpp"

class Board{
public:
    Tile*** tiles;
    int width, height, needed_coins;
    unsigned int player_focus;
    std::vector<Opponent*> opponents;
    std::vector<Player*  > players;
    std::vector<Key*     > keys;
    std::vector<Coin*    > coins;
    std::vector<Dirt*    > dirts;
    std::vector<Box*     > boxes;
    Board( int w, int h, int c );
    ~Board();
    void run();
    bool lost_game();
    bool end_of_game();
    void display( sf::RenderWindow* dest, int x, int y, int w, int h, graphics* GRPH, int tile_size = TILE_SIZE );
    void display2( sf::RenderWindow* dest, int x, int y, int w, int h, graphics* GRPH, int tile_size, int dx, int dy );
    void remove_entity( int x, int y );
};

Board* create_new_board( int w, int h, int c );

#endif
