#include "button.hpp"
#include "controller.hpp"

#include <SFML/Window/Mouse.hpp>


bool BTN::mouse_on( sf::RenderWindow* dest ){
    sf::Vector2i mpos = sf::Mouse::getPosition( *dest );
    return ( mpos.x >= x && mpos.x < x + w &&
             mpos.y >= y && mpos.y < y + h );
}

void BTN::run( GameController* gc, sf::RenderWindow* dest ){
    if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && !(gc->mouse_left_button_previously_pressed) && mouse_on( dest ) )
        pressed = true;
    else if( !sf::Mouse::isButtonPressed( sf::Mouse::Left ) && pressed ){
        if( mouse_on( dest ) )
            onclick( gc );
        pressed = false;
    }
}

BTN::BTN( int nx, int ny, int nw, int nh, std::function <void(GameController*)> no ){
    x = nx;
    y = ny;
    w = nw;
    h = nh;
    onclick = no;
    pressed = false;
}

BTN::~BTN(){}

BTN_CC::BTN_CC( sf::Font* font, int nx, int ny, int nw, int nh, std::function <void(GameController*)> no, const char* nname ) : BTN( nx, ny, nw, nh, no ), rect( sf::Vector2f( nw, nh ) ){
    name.setString( nname );
    name.setPosition( x + 1, y + 1 );
    name.setFillColor( sf::Color( 1, 1, 1 ) );
    name.setFont(*font);
    name.setCharacterSize( 20 );
    name.setOrigin( sf::Vector2f( name.getGlobalBounds().width/2, name.getGlobalBounds().height/2 ) );
    name.setPosition( x + w / 2, y + h / 2 - 5 );
    rect.setPosition( x, y );
    rect.setOutlineThickness( 1 );
    rect.setOutlineColor( sf::Color( 1, 1, 1 ) );
}

BTN_CC::~BTN_CC(){}

void BTN_CC::display( sf::RenderWindow* dest ){
    if( pressed )
        rect.setFillColor( sf::Color( 100, 100, 100 ) );
    else
        rect.setFillColor( sf::Color( 170, 170, 170 ) );
    dest->draw( rect );
    dest->draw( name );
}

BTN_BMP::BTN_BMP( int nx, int ny, int nw, int nh, std::function <void(GameController*)> no ) : BTN( nx, ny, nw, nh, no ),
    rect1( sf::Vector2f( nw, nh ) ){
    rect1.setPosition( x, y );
    rect1.setOutlineThickness( 1 );
    rect1.setOutlineColor( sf::Color( 1, 1, 1 ) );
}

BTN_BMP::~BTN_BMP(){}

void BTN_BMP::display( sf::RenderWindow* dest ){
    if( pressed )
        rect1.setFillColor( sf::Color( 100, 100, 100 ) );
    else
        rect1.setFillColor( sf::Color( 170, 170, 170 ) );
    dest->draw( rect1 );
    dest->draw( sprt );
}
