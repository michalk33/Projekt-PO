#include <SFML/Window/Mouse.hpp>

#include "consts.hpp"

graphics::graphics(){
    grass_text.loadFromFile( "graphics/grass.png" );
    wall_text.loadFromFile( "graphics/wall.png" );
    button_pr_text.loadFromFile( "graphics/button_pr.png" );
    button_unpr_text.loadFromFile( "graphics/button_unpr.png" );
    exit_text.loadFromFile( "graphics/exit.png" );
    door_green_text.loadFromFile( "graphics/door_green.png" );
    door_red_text.loadFromFile( "graphics/door_red.png" );
    door_purple_text.loadFromFile( "graphics/door_purple.png" );
    grass_spri.setTexture( grass_text );
    wall_spri.setTexture( wall_text );
    button_pr_spri.setTexture( button_pr_text );
    button_unpr_spri.setTexture( button_unpr_text );
    exit_spri.setTexture( exit_text );
    door_green_spri.setTexture( door_green_text );
    door_red_spri.setTexture( door_red_text );
    door_purple_spri.setTexture( door_purple_text );
    gate_text.loadFromFile( "graphics/gate.png" );
    red_key_text.loadFromFile( "graphics/red_key.png" );
    green_key_text.loadFromFile( "graphics/green_key.png" );
    purple_key_text.loadFromFile( "graphics/purple_key.png" );
    gate_h_text.loadFromFile( "graphics/gate_h.png" );
    gate_v_text.loadFromFile( "graphics/gate_v.png" );
    player_text.loadFromFile( "graphics/player.png" );
    enemy_text.loadFromFile( "graphics/enemy.png" );
    dirt_text.loadFromFile( "graphics/dirt.png" );
    coin_text.loadFromFile( "graphics/coin.png" );
    box_text.loadFromFile( "graphics/box.png" );
}

sf::Vector2i mousePosition( sf::RenderWindow* dest ){
    sf::Vector2i mpos = sf::Mouse::getPosition( *dest );
    sf::Vector2i wsiz( ( dest->getSize() ).x, ( dest->getSize() ).y );
    float nx = mpos.x;
    nx *= WINDOW_W;
    nx /= wsiz.x;
    float ny = mpos.y;
    ny *= WINDOW_H;
    ny /= wsiz.y;
    mpos.x = (int) nx;
    mpos.y = (int) ny;
    return mpos;
}
