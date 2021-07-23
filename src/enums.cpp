#include "enums.hpp"
#include "consts.hpp"

#include <SFML/Window/Keyboard.hpp>

std::string tostring( int x )
{
    char tab[10];
    sprintf( tab, "%i", x );
    return tab;
}

enum direction clockwise( enum direction dir ){
    switch( dir ){
    case up:    return right;
    case right: return down;
    case down:  return left;
    case left:  return up;
    default:    return nothing;
    }
    return nothing;
}

enum direction cunterclockwise( enum direction dir ){
    switch( dir ){
    case up:    return left;
    case right: return up;
    case down:  return right;
    case left:  return down;
    default:    return nothing;
    }
    return nothing;
}

int moving_time_d( enum speed_types spd ){
    switch( spd ){
    case slow: return SLOW_MOVING_TIME_D;
    case fast: return FAST_MOVING_TIME_D;
    }
    return 0;
}

std::pair<int,int> new_coordinates( int x, int y, enum direction dir ){
    switch( dir ){
    case up:    return std::pair<int,int>( x, y - 1 );
    case right: return std::pair<int,int>( x + 1, y );
    case down:  return std::pair<int,int>( x, y + 1 );
    case left:  return std::pair<int,int>( x - 1, y );
    default:    return std::pair<int,int>( x, y );
    }
    return std::pair<int,int>( x, y );
}

enum direction pressed_dir(){
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )    return up;
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) return right;
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )  return down;
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )  return left;
    return nothing;
}

int pressed_num(){
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num0 ) ) return 0;
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num1 ) ) return 1;
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num2 ) ) return 2;
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num3 ) ) return 3;
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num4 ) ) return 4;
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num5 ) ) return 5;
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num6 ) ) return 6;
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num7 ) ) return 7;
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num8 ) ) return 8;
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Num9 ) ) return 9;
    return -1;
}

int limit( int max, int min, int val ){
    if( val < min ) return min;
    if( val > max ) return max;
    return val;
}
