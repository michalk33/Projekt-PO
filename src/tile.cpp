#include "tile.hpp"

enum tile_types Grass::get_type(){return grass;}
enum tile_types Wall::get_type(){return wall;}
enum tile_types Exit::get_type(){return exitt;}
enum tile_types Door::get_type(){return door;}
enum tile_types Gate::get_type(){return gate;}
enum tile_types ButtonOneTime::get_type(){return button_one_time;}
enum tile_types ButtonMultipleTimes::get_type(){return button_multiple_times;}

void Tile::set_entity( Entity* ent_ptr ){
    entity_ptr = ent_ptr;
}

void Tile::unset_entity(){
    entity_ptr = nullptr;
}

Entity* Tile::get_entity_ptr(){
    return entity_ptr;
}

bool Grass::pushable(){
    return true;
}

bool Grass::walkable( Player* player_ptr ){
    return true;
}

void Grass::run( int x, int y, Board* brd ){}

void Grass::display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){
    if( bx + ( x + 1 ) * tile_size >= brx && bx + x * tile_size <= brx + w &&
        by + ( y + 1 ) * tile_size >= bry && by + y * tile_size <= bry + h ){
            GRPH->grass_spri.setPosition( bx + x * tile_size, by + y * tile_size );
            dest->draw( GRPH->grass_spri );
        }
}

bool Wall::pushable(){
    return false;
}

bool Wall::walkable( Player* player_ptr ){
    return false;
}

void Wall::run( int x, int y, Board* brd ){}

void Wall::display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){
    if( bx + ( x + 1 ) * tile_size >= brx && bx + x * tile_size <= brx + w &&
        by + ( y + 1 ) * tile_size >= bry && by + y * tile_size <= bry + h ){
            GRPH->wall_spri.setPosition( bx + x * tile_size, by + y * tile_size );
            dest->draw( GRPH->wall_spri );
        }
}

bool Door::pushable(){
    return false;
}

bool Door::walkable( Player* player_ptr ){
    if( player_ptr )
        return player_ptr->have_key( color );
    return false;
}

void Door::run( int x, int y, Board* brd ){}

void Door::display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){
    if( bx + ( x + 1 ) * tile_size >= brx && bx + x * tile_size <= brx + w &&
        by + ( y + 1 ) * tile_size >= bry && by + y * tile_size <= bry + h )
        switch( color ){
        case red:
            GRPH->door_red_spri.setPosition( bx + x * tile_size, by + y * tile_size );
            dest->draw( GRPH->door_red_spri );
            break;
        case green:
            GRPH->door_green_spri.setPosition( bx + x * tile_size, by + y * tile_size );
            dest->draw( GRPH->door_green_spri );
            break;
        case purple:
            GRPH->door_purple_spri.setPosition( bx + x * tile_size, by + y * tile_size );
            dest->draw( GRPH->door_purple_spri );
            break;
        default:
            break;
        }
}

bool Exit::pushable(){
    return true;
}

bool Exit::walkable( Player* player_ptr ){
    return true;
}

void Exit::run( int x, int y, Board* brd ){}

void Exit::display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){
    if( bx + ( x + 1 ) * tile_size >= brx && bx + x * tile_size <= brx + w &&
        by + ( y + 1 ) * tile_size >= bry && by + y * tile_size <= bry + h ){
            GRPH->exit_spri.setPosition( bx + x * tile_size, by + y * tile_size );
            dest->draw( GRPH->exit_spri );
        }
}

bool Button::pushable(){
    return true;
}

bool Button::walkable( Player* player_ptr ){
    return true;
}

enum button_states Button::get_state(){
    return state;
}

void ButtonOneTime::run( int x, int y, Board* brd ){
    if( entity_ptr && state == unpressed && entity_ptr->weight_type() == heavy )
        state = pressed;
}

void ButtonOneTime::display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){
    if( bx + ( x + 1 ) * tile_size >= brx && bx + x * tile_size <= brx + w &&
        by + ( y + 1 ) * tile_size >= bry && by + y * tile_size <= bry + h ){
        switch( state ){
        case pressed:
            GRPH->button_pr_spri.setPosition( bx + x * tile_size, by + y * tile_size );
            dest->draw( GRPH->button_pr_spri );
            break;
        case unpressed:
            GRPH->button_unpr_spri.setPosition( bx + x * tile_size, by + y * tile_size );
            dest->draw( GRPH->button_unpr_spri );
            break;
        default:
            break;
        }
    }
}

void ButtonMultipleTimes::run( int x, int y, Board* brd ){
    if( entity_ptr ){
        if( entity_ptr->weight_type() == heavy )
            state = pressed;
        else
            state = unpressed;
    }else
        state = unpressed;
}

void ButtonMultipleTimes::display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){
    if( bx + ( x + 1 ) * tile_size >= brx && bx + x * tile_size <= brx + w &&
        by + ( y + 1 ) * tile_size >= bry && by + y * tile_size <= bry + h ){
        switch( state ){
        case pressed:
            GRPH->button_pr_spri.setPosition( bx + x * tile_size, by + y * tile_size );
            dest->draw( GRPH->button_pr_spri );
            break;
        case unpressed:
            GRPH->button_unpr_spri.setPosition( bx + x * tile_size, by + y * tile_size );
            dest->draw( GRPH->button_unpr_spri );
            break;
        default:
            break;
        }
    }
}

bool Gate::pushable(){
    return ( state == unlocked );
}

bool Gate::walkable( Player* player_ptr ){
    return ( state == unlocked );
}

void Gate::run( int x, int y, Board* brd ){
    if( button_ptr ){
        time--;
        if( time < 0 ) time = 0;
        switch( state ){
        case unlocked:
            if( button_ptr->get_state() == unpressed && entity_ptr == nullptr ){
                time = GATE_OPENING_TIME;
                state = closing;
            }
            break;
        case locked:
            if( button_ptr->get_state() == pressed ){
                time = GATE_OPENING_TIME;
                state = opening;
            }
            break;
        case opening:
            if( time <= 0 ) state = unlocked;
            if( button_ptr->get_state() == unpressed ){
                time = GATE_OPENING_TIME - time;
                state = closing;
            }
            break;
        case closing:
            if( time <= 0 ) state = locked;
            if( button_ptr->get_state() == pressed ){
                time = GATE_OPENING_TIME - time;
                state = opening;
            }
            break;
        }
    }
}

void Gate::display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ){
    if( bx + ( x + 1 ) * tile_size >= brx && bx + x * tile_size <= brx + w &&
        by + ( y + 1 ) * tile_size >= bry && by + y * tile_size <= bry + h ){
        GRPH->grass_spri.setPosition( bx + x * tile_size, by + y * tile_size );
        dest->draw( GRPH->grass_spri );
        float r;
        switch( state ){
        case locked:
            r = 1;
            break;
        case opening:
            r = time;
            r /= GATE_OPENING_TIME;
            break;
        case closing:
            r = GATE_OPENING_TIME - time;
            r /= GATE_OPENING_TIME;
            break;
        default:
            r = 0;
            break;
        }
        if( vertical ){
            sf::RectangleShape rect1( sf::Vector2f( tile_size / 2, ( tile_size / 2 ) * r ) );
            sf::RectangleShape rect2( sf::Vector2f( tile_size / 2, ( tile_size / 2 ) * r ) );
            rect1.setPosition( bx + x * tile_size + tile_size / 4, by + y * tile_size );
            rect2.setPosition( bx + x * tile_size + tile_size / 4, by + ( y + 1 ) * tile_size - ( tile_size / 2 ) * r );
            rect1.setTexture( &(GRPH->gate_text) );
            rect2.setTexture( &(GRPH->gate_text) );
            dest->draw( rect1 );
            dest->draw( rect2 );
        }else{
            sf::RectangleShape rect1( sf::Vector2f( ( tile_size / 2 ) * r, tile_size / 2 ) );
            sf::RectangleShape rect2( sf::Vector2f( ( tile_size / 2 ) * r, tile_size / 2 ) );
            rect1.setPosition( bx + x * tile_size, by + y * tile_size + tile_size / 4 );
            rect2.setPosition( bx + ( x + 1 ) * tile_size - ( tile_size / 2 ) * r, by + y * tile_size + tile_size / 4 );
            rect1.setTexture( &(GRPH->gate_text) );
            rect2.setTexture( &(GRPH->gate_text) );
            dest->draw( rect1 );
            dest->draw( rect2 );
        }
    }
}

Tile::Tile(){entity_ptr = nullptr;}
Grass::Grass() : Tile(){}
Wall::Wall() : Tile(){}
Door::Door( enum key_colors clr ) : Tile(){color = clr;}
Exit::Exit() : Tile(){}
Button::Button() : Tile(){state = unpressed;}
ButtonOneTime::ButtonOneTime() : Button(){}
ButtonMultipleTimes::ButtonMultipleTimes() : Button(){}
Gate::Gate( bool vert, Button* bptr, int btx, int bty ) : Tile(){time = 0; state = locked; vertical = vert; button_ptr = bptr; btnx = btx; btny = bty;}

Tile::~Tile(){}
Grass::~Grass(){}
Wall::~Wall(){}
Door::~Door(){}
Exit::~Exit(){}
Button::~Button(){}
ButtonOneTime::~ButtonOneTime(){}
ButtonMultipleTimes::~ButtonMultipleTimes(){}
Gate::~Gate(){}

enum key_colors Grass::get_color(){return red;};
int Grass::get_btnx(){return 0;}
int Grass::get_btny(){return 0;}
bool Grass::get_vert(){return false;}

enum key_colors Wall::get_color(){return red;};
int Wall::get_btnx(){return 0;}
int Wall::get_btny(){return 0;}
bool Wall::get_vert(){return false;}

enum key_colors Door::get_color(){return color;};
int Door::get_btnx(){return 0;}
int Door::get_btny(){return 0;}
bool Door::get_vert(){return false;}

enum key_colors Exit::get_color(){return red;};
int Exit::get_btnx(){return 0;}
int Exit::get_btny(){return 0;}
bool Exit::get_vert(){return false;}

enum key_colors ButtonOneTime::get_color(){return red;};
int ButtonOneTime::get_btnx(){return 0;}
int ButtonOneTime::get_btny(){return 0;}
bool ButtonOneTime::get_vert(){return false;}

enum key_colors ButtonMultipleTimes::get_color(){return red;};
int ButtonMultipleTimes::get_btnx(){return 0;}
int ButtonMultipleTimes::get_btny(){return 0;}
bool ButtonMultipleTimes::get_vert(){return false;}

enum key_colors Gate::get_color(){return red;};
int Gate::get_btnx(){return btnx;}
int Gate::get_btny(){return btny;}
bool Gate::get_vert(){return vertical;}
