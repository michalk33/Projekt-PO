#include "board.hpp"

Board::Board( int w, int h, int c ){
    tiles = new Tile** [ w ];
    for( int i = 0; i < w; i++ )
        tiles [ i ] = new Tile* [ h ];
    for( int i = 0; i < w; i++ )
        for( int j = 0; j < h; j++ )
            tiles [ i ] [ j ] = nullptr;
    needed_coins = c;
    player_focus = 0;
    width = w;
    height = h;
}

Board::~Board(){
    for( int i = 0; i < width; i++ )
        for( int j = 0; j < height; j++ )
            if( tiles [ i ] [ j ] )
                delete tiles [ i ] [ j ];
    for( int i = 0; i < width; i++ )
        delete[] tiles [ i ];
    delete[] tiles;
    for( auto& it : keys ) delete it;
    for( auto& it : coins ) delete it;
    for( auto& it : dirts ) delete it;
    for( auto& it : boxes ) delete it;
    for( auto& it : players ) delete it;
    for( auto& it : opponents ) delete it;
    keys.clear();
    coins.clear();
    dirts.clear();
    boxes.clear();
    players.clear();
    opponents.clear();
}

bool Board::end_of_game(){
    for( unsigned int i = 0; i < players.size(); i++ )
        if( players[ i ]->get_lifes() <= 0 )
            return true;
    for( unsigned int i = 0; i < players.size(); i++ )
        if( players[ i ]->state != staying || tiles[players[ i ]->pos_x][players[ i ]->pos_y]->get_type() != exitt )
            return false;
    if( needed_coins > 0 ) return false;
    return true;
}

bool Board::lost_game(){
    for( unsigned int i = 0; i < players.size(); i++ )
        if( players[ i ]->get_lifes() <= 0 )
            return true;
    return false;
}

void Board::run(){
    if( pressed_num() != -1 )
        player_focus = pressed_num();
    if( player_focus >= players.size() ) player_focus = players.size() - 1;
    if( player_focus < 0 ) player_focus = 0;
    for( int i = 0; i < width; i++ )
        for( int j = 0; j < height; j++ )
            tiles[i][j]->run( i, j, this );
    for( auto& it : keys ) it->run( this, false );
    for( auto& it : coins ) it->run( this, false );
    for( auto& it : dirts ) it->run( this, false );
    for( auto& it : boxes ) it->run( this, false );
    for( int i = 0; i < players.size(); i++ ) players[i]->run( this, i == player_focus );
    for( auto& it : opponents ) it->run( this, false );
}

void Board::display( sf::RenderWindow* dest, int x, int y, int w, int h, graphics* GRPH, int tile_size ){
    int cx = players[player_focus]->pos_x;
    int cy = players[player_focus]->pos_y;
    float f = players[player_focus]->moving_state;
    f /= MOVING_INITIAL_STATE;
    f *= tile_size;
    f = tile_size - f;
    if( players[player_focus]->get_state() == staying ) f = 0;
    float bx = x;
    bx += w / 2;
    bx -= tile_size / 2;
    bx -= cx * tile_size;
    if( players[player_focus]->dir == right )     bx -= f;
    else if( players[player_focus]->dir == left ) bx += f;
    float by = y;
    by += h / 2;
    by -= tile_size / 2;
    by -= cy * tile_size;
    if( players[player_focus]->dir == down )    by -= f;
    else if( players[player_focus]->dir == up ) by += f;
    int bxi = bx;
    int byi = by;
    bxi = limit( x, x - width * tile_size, bxi );
    byi = limit( y, y - height * tile_size, byi );
    for( int i = 0; i < width; i++ )
        for( int j = 0; j < height; j++ )
            tiles[i][j]->display( dest, bxi, byi, i, j, tile_size, x, y, w, h, GRPH );
    for( auto& it : keys ) it->display( dest, bxi, byi, tile_size, x, y, w, h, GRPH );
    for( auto& it : coins ) it->display( dest, bxi, byi, tile_size, x, y, w, h, GRPH );
    for( auto& it : dirts ) it->display( dest, bxi, byi, tile_size, x, y, w, h, GRPH );
    for( auto& it : boxes ) it->display( dest, bxi, byi, tile_size, x, y, w, h, GRPH );
    for( auto& it : players ) it->display( dest, bxi, byi, tile_size, x, y, w, h, GRPH );
    for( auto& it : opponents ) it->display( dest, bxi, byi, tile_size, x, y, w, h, GRPH );
}

Board* create_new_board( int w, int h, int c ){
    Board* ret = new Board( w, h, c );
    for( int i = 0; i < w; i++ ){
        for( int j = 0; j < h; j++ ){
            if( i == 0 || i == w - 1 || j == 0 || j == h - 1 )
                ret->tiles[i][j] = new Wall();
            else
                ret->tiles[i][j] = new Grass();
        }
    }
    Player* plyrptr = new Player( heavy, fast, true, true, 3, 4, 4 );
    ret->players.push_back( plyrptr );
    return ret;
}

void Board::display2( sf::RenderWindow* dest, int x, int y, int w, int h, graphics* GRPH, int tile_size, int dx, int dy ){
    int bx = x + dx;
    int by = y + dy;
    for( int i = 0; i < width; i++ )
        for( int j = 0; j < height; j++ )
            tiles[i][j]->display( dest, bx, by, i, j, tile_size, x, y, w, h, GRPH );
    for( auto& it : keys ) it->display( dest, bx, by, tile_size, x, y, w, h, GRPH );
    for( auto& it : coins ) it->display( dest, bx, by, tile_size, x, y, w, h, GRPH );
    for( auto& it : dirts ) it->display( dest, bx, by, tile_size, x, y, w, h, GRPH );
    for( auto& it : boxes ) it->display( dest, bx, by, tile_size, x, y, w, h, GRPH );
    for( auto& it : players ) it->display( dest, bx, by, tile_size, x, y, w, h, GRPH );
    for( auto& it : opponents ) it->display( dest, bx, by, tile_size, x, y, w, h, GRPH );
}

void Board::remove_entity( int x, int y ){
    for( int i = 0; i < players.size(); i++ ){
        if( players[i]->pos_x == x && players[i]->pos_y == y ){
            delete players[i];
            players[i] = players[players.size()-1];
            players.pop_back();
            break;
        }
    }
    for( int i = 0; i < keys.size(); i++ ){
        if( keys[i]->pos_x == x && keys[i]->pos_y == y ){
            delete keys[i];
            keys[i] = keys[keys.size()-1];
            keys.pop_back();
            break;
        }
    }
    for( int i = 0; i < opponents.size(); i++ ){
        if( opponents[i]->pos_x == x && opponents[i]->pos_y == y ){
            delete opponents[i];
            opponents[i] = opponents[opponents.size()-1];
            opponents.pop_back();
            break;
        }
    }
    for( int i = 0; i < boxes.size(); i++ ){
        if( boxes[i]->pos_x == x && boxes[i]->pos_y == y ){
            delete boxes[i];
            boxes[i] = boxes[boxes.size()-1];
            boxes.pop_back();
            break;
        }
    }
    for( int i = 0; i < coins.size(); i++ ){
        if( coins[i]->pos_x == x && coins[i]->pos_y == y ){
            delete coins[i];
            coins[i] = coins[coins.size()-1];
            coins.pop_back();
            break;
        }
    }
    for( int i = 0; i < dirts.size(); i++ ){
        if( dirts[i]->pos_x == x && dirts[i]->pos_y == y ){
            delete dirts[i];
            dirts[i] = dirts[dirts.size()-1];
            dirts.pop_back();
            break;
        }
    }
    tiles[x][y]->unset_entity();
}
