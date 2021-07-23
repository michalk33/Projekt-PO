#include "entity.hpp"
#include "board.hpp"

enum entity_types Box::type(){return box;}
enum entity_types Key::type(){return key;}
enum entity_types Coin::type(){return coin;}
enum entity_types Dirt::type(){return dirt;}
enum entity_types Player::type(){return player;}
enum entity_types Opponent::type(){return opponent;}

enum weight_types Box::weight_type(){return weight;}
enum weight_types Player::weight_type(){return weight;}
enum weight_types Opponent::weight_type(){return weight;}
enum weight_types Collectible::weight_type(){return light;}

enum entity_states Entity::get_state(){return state;}

Entity::~Entity(){}
Collectible::~Collectible(){}
Key::~Key(){}
Coin::~Coin(){}
Dirt::~Dirt(){}
Opponent::~Opponent(){ positions.clear(); }
Player::~Player(){}
Box::~Box(){}

void Entity::go( Board* brd, int time_d ){
    moving_state -= time_d;
    if( moving_state < 0 ) moving_state = 0;
    std::pair<int,int> tmp = new_coordinates( pos_x, pos_y, dir );
    if( moving_state == 0 ){
        brd->tiles[pos_x][pos_y]->unset_entity();
        pos_x = tmp.first;
        pos_y = tmp.second;
        state = staying;
        brd->tiles[pos_x][pos_y]->set_entity( this );
    }else{
        brd->tiles[pos_x][pos_y]->set_entity( this );
        brd->tiles[tmp.first][tmp.second]->set_entity( this );
    }
}

bool Entity::try_moving( enum direction ndr, Board* brd, bool dg, bool cl, bool ps, Player* pl_ptr ){
    std::pair<int,int> temp = new_coordinates( pos_x, pos_y, ndr );
    if( !( brd->tiles[temp.first][temp.second]->walkable( pl_ptr ) ) )
        return false;
    if( brd->tiles[temp.first][temp.second]->get_entity_ptr() != nullptr ){
        enum entity_types ent = brd->tiles[temp.first][temp.second]->get_entity_ptr()->type();
        switch( ent ){
        case key:
            if( cl ){
                for( unsigned int i = 0; i < brd->keys.size(); i++ ){
                    if( brd->keys[i]->pos_x == temp.first &&
                        brd->keys[i]->pos_y == temp.second ){
                            brd->players[brd->player_focus]->keys.push_back( brd->keys[i]->get_color() );
                            delete brd->keys[i];
                            brd->keys[i] = brd->keys[brd->keys.size()-1];
                            brd->keys.pop_back();
                            break;
                    }
                }
                start_moving( ndr, brd );
                return true;
            }
            break;
        case dirt:
            if( dg ){
                for( unsigned int i = 0; i < brd->dirts.size(); i++ ){
                    if( brd->dirts[i]->pos_x == temp.first &&
                        brd->dirts[i]->pos_y == temp.second ){
                            delete brd->dirts[i];
                            brd->dirts[i] = brd->dirts[brd->dirts.size()-1];
                            brd->dirts.pop_back();
                            break;
                    }
                }
                start_moving( ndr, brd );
                return true;
            }
            break;
        case coin:
            if( cl ){
                for( unsigned int i = 0; i < brd->coins.size(); i++ ){
                    if( brd->coins[i]->pos_x == temp.first &&
                        brd->coins[i]->pos_y == temp.second ){
                            brd->needed_coins -= brd->coins[i]->get_value();
                            if( brd->needed_coins < 0 ) brd->needed_coins = 0;
                            delete brd->coins[i];
                            brd->coins[i] = brd->coins[brd->coins.size()-1];
                            brd->coins.pop_back();
                            break;
                    }
                }
                start_moving( ndr, brd );
                return true;
            }
            break;
        case box:
            if( ps ){
                for( unsigned int i = 0; i < brd->boxes.size(); i++ ){
                    if( brd->boxes[i]->pos_x == temp.first &&
                        brd->boxes[i]->pos_y == temp.second ){
                            std::pair<int,int> temp2 = new_coordinates( temp.first, temp.second, ndr );
                            if( brd->boxes[i]->get_state() == staying && brd->tiles[temp2.first][temp2.second]->pushable() && brd->boxes[i]->try_moving( ndr, brd, false, false, false, nullptr ) ){
                                start_moving( ndr, brd );
                                return true;
                            }
                            break;
                    }
                }
            }
            break;
        case player:
            if( this->type() == opponent ){
                for( int i = 0; i < brd->players.size(); i++ ){
                    std::pair<int,int> temppl = new_coordinates( brd->players[i]->pos_x, brd->players[i]->pos_y, brd->players[i]->dir );
                    if( ( brd->players[i]->pos_x == temp.first && brd->players[i]->pos_y == temp.second ) ||
                        ( temppl.first == temp.first && temppl.second == temp.second && brd->players[i]->get_state() == moving ) ){
                        if( brd->players[i]->player_state == normal ){
                            brd->players[i]->player_state = injured;
                            brd->players[i]->player_state_time = INJURY_TIME;
                            brd->players[i]->lifes -= 1;
                        }
                        break;
                    }
                }
            }
            break;
        default:
            break;
        }
    }else{
        start_moving( ndr, brd );
        return true;
    }
    return false;
}

void Entity::start_moving( enum direction ndr, Board* brd ){
    std::pair<int,int> temp = new_coordinates( pos_x, pos_y, ndr );
    dir = ndr;
    moving_state = MOVING_INITIAL_STATE;
    state = moving;
    brd->tiles[temp.first][temp.second]->set_entity( this );
}

void Collectible::run( Board* brd, bool focus ){
    brd->tiles[pos_x][pos_y]->set_entity( this );
}

void Box::run( Board* brd, bool focus ){
    switch( state ){
    case staying:
        brd->tiles[pos_x][pos_y]->set_entity( this );
        break;
    case moving:
        go( brd, BOX_MOVING_TIME_D );
        break;
    }
}

void Opponent::run( Board* brd, bool focus ){
    int next_pos = clockwise ? ( current_position + 1 ) % positions.size() : current_position;
    switch( state ){
    case staying:
        brd->tiles[pos_x][pos_y]->set_entity( this );
        if( pos_x == positions[next_pos].first && pos_y == positions[next_pos].second ){
            current_position = clockwise ? next_pos : ( current_position - 1 + positions.size() ) % positions.size();
            next_pos = clockwise ? ( current_position + 1 ) % positions.size() : current_position;
        }
        clockwise ^= !try_moving( pos_x == positions[next_pos].first ?
                                 ( pos_y > positions[next_pos].second ? up : down ) :
                                 ( pos_x > positions[next_pos].first ? left : right ), brd, false, false, false, nullptr );
        break;
    case moving:
        go( brd, moving_time_d( speed ) );
        break;
    }
}

void Player::run( Board* brd, bool focus ){
    player_state_time--;
    if( player_state_time < 0 ) player_state_time = 0;
    if( player_state_time == 0 ) player_state = normal;
    switch( state ){
    case staying:
        brd->tiles[pos_x][pos_y]->set_entity( this );
        if( focus ){
            enum direction tmp = pressed_dir();
            if( tmp != nothing ){
                try_moving( tmp, brd, digging, true, pushing, this );
            }
        }
        break;
    case moving:
        go( brd, moving_time_d( speed ) );
        break;
    }
}

float Entity::dist( int tile_size ){
    float f = moving_state;
    f /= MOVING_INITIAL_STATE;
    f *= tile_size;
    f = tile_size - f;
    return f;
}

void Player::display( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){
    float radf = tile_size * ( weight == heavy ? 0.45 : 0.33 );
    int radi = (int) radf;
    float redf = ( ( player_state == injured ? 140 : 0 ) + ( digging ? 300 : 0 ) ) * ( digging ? 0.5 : 1 );
    int redi = (int) redf;
    float greenf = 200 * ( digging ? 0.5 : 1 );
    int greeni = (int) greenf;
    int bluei = ( digging ? 80 : 20 );
    int alphai = ( player_state == injured ? 180 : 255 );
    int thicknessi = ( pushing ? 5 : 2 );
    float f = ( state == moving ) ? dist( tile_size ) : 0;
    int fi = f;
    int x = bx + pos_x * tile_size;
    int y = by + pos_y * tile_size;
    if( dir == right ) x += fi;
    if( dir == left )  x -= fi;
    if( dir == down )  y += fi;
    if( dir == up )    y -= fi;
    if( x + 2 * tile_size >= brx && x - tile_size <= brx + w &&
        y + 2 * tile_size >= bry && y - tile_size <= bry + h ){
            sf::CircleShape circle( radi );
            circle.setPosition( x + tile_size / 2 - radi, y + tile_size / 2 - radi );
            circle.setOutlineThickness( thicknessi );
            circle.setFillColor( sf::Color( redi, greeni, bluei, alphai ) );
            circle.setOutlineColor( sf::Color( redi / 2, greeni / 2, bluei / 2, alphai ) );
            dest->draw( circle );
        }
}

void Player::display_focus( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){;
    float f = ( state == moving ) ? dist( tile_size ) : 0;
    int fi = f;
    int x = bx + pos_x * tile_size;
    int y = by + pos_y * tile_size;
    if( dir == right ) x += fi;
    if( dir == left )  x -= fi;
    if( dir == down )  y += fi;
    if( dir == up )    y -= fi;
    if( x + 2 * tile_size >= brx && x - tile_size <= brx + w &&
        y + 2 * tile_size >= bry && y - tile_size <= bry + h ){
            sf::CircleShape circle( tile_size / 12 );
            circle.setPosition( x + ( tile_size * 5 ) / 12, y + ( tile_size * 5 ) / 12 );
            circle.setFillColor( sf::Color( 180, 140, 20, 120 ) );
            dest->draw( circle );
        }
}

void Opponent::display( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){
    float radf = tile_size * ( weight == heavy ? 0.45 : 0.33 );
    int radi = (int) radf;
    float f = ( state == moving ) ? dist( tile_size ) : 0;
    int fi = f;
    int x = bx + pos_x * tile_size;
    int y = by + pos_y * tile_size;
    if( dir == right ) x += fi;
    if( dir == left )  x -= fi;
    if( dir == down )  y += fi;
    if( dir == up )    y -= fi;
    if( x + 2 * tile_size >= brx && x - tile_size <= brx + w &&
        y + 2 * tile_size >= bry && y - tile_size <= bry + h ){
            sf::CircleShape circle( radi );
            circle.setPosition( x + tile_size / 2 - radi, y + tile_size / 2 - radi );
            circle.setOutlineThickness( 2 );
            circle.setOutlineColor( sf::Color( 200, 50, 20 ) );
            circle.setFillColor( sf::Color( 200, 50, 20 ) );
            dest->draw( circle );
        }
}

void Box::display( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){
    float f = ( state == moving ) ? dist( tile_size ) : 0;
    int fi = f;
    int x = bx + pos_x * tile_size;
    int y = by + pos_y * tile_size;
    if( dir == right ) x += fi;
    if( dir == left )  x -= fi;
    if( dir == down )  y += fi;
    if( dir == up )    y -= fi;
    float sidef = tile_size * ( weight == heavy ? 0.85 : 0.70 );
    int sidei = (int) sidef;
    if( x + 2 * tile_size >= brx && x - tile_size <= brx + w &&
        y + 2 * tile_size >= bry && y - tile_size <= bry + h ){
            sf::RectangleShape rect( sf::Vector2f( sidei, sidei ) );
            rect.setPosition( x + tile_size / 2 - sidei / 2, y + tile_size / 2 - sidei / 2 );
            rect.setOutlineThickness( 2 );
            rect.setOutlineColor( sf::Color( 20, 10, 5 ) );
            rect.setFillColor( sf::Color( 80, 40, 15 ) );
            dest->draw( rect );
        }
}

void Key::display( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){
    int x = bx + pos_x * tile_size;
    int y = by + pos_y * tile_size;
    if( x + 2 * tile_size >= brx && x - tile_size <= brx + w &&
        y + 2 * tile_size >= bry && y - tile_size <= bry + h ){
            sf::RectangleShape rect( sf::Vector2f( KEY_SIZE, KEY_SIZE ) );
            rect.setPosition( x + ( tile_size - KEY_SIZE ) / 2, y + ( tile_size - KEY_SIZE ) / 2);
            switch( color ){
            case red:
                rect.setTexture( &(GRPH->red_key_text) );
                break;
            case green:
                rect.setTexture( &(GRPH->green_key_text) );
                break;
            case purple:
                rect.setTexture( &(GRPH->purple_key_text) );
                break;
            }
            dest->draw( rect );
        }
}

void Coin::display( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){
    int x = bx + pos_x * tile_size;
    int y = by + pos_y * tile_size;
    if( x + 2 * tile_size >= brx && x - tile_size <= brx + w &&
        y + 2 * tile_size >= bry && y - tile_size <= bry + h ){
            sf::CircleShape circle( tile_size / 3 );
            circle.setOutlineThickness( 2 );
            circle.setOutlineColor( sf::Color( 100, 85, 5 ) );
            circle.setFillColor( sf::Color( 200, 170, 10 ) );
            circle.setPosition( x + tile_size / 6, y + tile_size / 6 );
            dest->draw( circle );
        }
}

void Dirt::display( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){
    int x = bx + pos_x * tile_size;
    int y = by + pos_y * tile_size;
    if( x + 2 * tile_size >= brx && x - tile_size <= brx + w &&
        y + 2 * tile_size >= bry && y - tile_size <= bry + h ){
            sf::CircleShape circle( tile_size / 4 );
            circle.setOutlineThickness( 2 );
            circle.setOutlineColor( sf::Color( 50, 25, 15 ) );
            circle.setFillColor( sf::Color( 80, 50, 35 ) );
            circle.setPosition( x, y );
            dest->draw( circle );
            circle.setPosition( x + tile_size / 2, y );
            dest->draw( circle );
            circle.setPosition( x, y + tile_size / 2 );
            dest->draw( circle );
            circle.setPosition( x + tile_size / 2, y + tile_size / 2 );
            dest->draw( circle );
        }
}

Entity::Entity( int x, int y ){
    pos_x = x;
    pos_y = y;
    moving_state = 0;
    dir = up;
    state = staying;
}

Collectible::Collectible( int x, int y ) : Entity( x, y ){}
Key::Key( enum key_colors clr, int x, int y ) : Collectible( x, y ){color = clr;}
Coin::Coin( int val, int x, int y ) : Collectible( x, y ){value = val;}
Dirt::Dirt( int x, int y ) : Collectible( x, y ){}
Box::Box( enum weight_types wght, int x, int y ) : Entity( x, y ){weight = wght;}

Opponent::Opponent( enum weight_types wght, enum speed_types spd, int x, int y ) : Entity( x, y ){
    weight = wght; speed = spd; clockwise = true; add_position( x, y ); current_position = 0;
}

Player::Player( enum weight_types wght, enum speed_types spd, bool dgg, bool psh, int lfs, int x, int y ) : Entity( x, y ){
    weight = wght; speed = spd; digging = dgg; pushing = psh; lifes = lfs; player_state = normal;}

enum key_colors Key::get_color(){return color;}
int Player::get_lifes(){return lifes;}
int Coin::get_value(){return value;}

bool Player::have_key( enum key_colors key_color ){
    for( unsigned int i = 0; i < keys.size(); i++ )
        if( keys[i] == key_color )
            return true;
    return false;
}

void Opponent::add_position( int nx, int ny ){
    positions.push_back( std::pair<int,int>( nx, ny ) );
}
