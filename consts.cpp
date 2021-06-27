#include "consts.hpp"

graphics* load_textures(){
    graphics* GRPH = new graphics();
    GRPH->grass_text.loadFromFile( "graphics/grass.png" );
    GRPH->wall_text.loadFromFile( "graphics/wall.png" );
    GRPH->button_pr_text.loadFromFile( "graphics/button_pr.png" );
    GRPH->button_unpr_text.loadFromFile( "graphics/button_unpr.png" );
    GRPH->exit_text.loadFromFile( "graphics/exit.png" );
    GRPH->door_green_text.loadFromFile( "graphics/door_green.png" );
    GRPH->door_red_text.loadFromFile( "graphics/door_red.png" );
    GRPH->door_purple_text.loadFromFile( "graphics/door_purple.png" );
    GRPH->grass_spri.setTexture( GRPH->grass_text );
    GRPH->wall_spri.setTexture( GRPH->wall_text );
    GRPH->button_pr_spri.setTexture( GRPH->button_pr_text );
    GRPH->button_unpr_spri.setTexture( GRPH->button_unpr_text );
    GRPH->exit_spri.setTexture( GRPH->exit_text );
    GRPH->door_green_spri.setTexture( GRPH->door_green_text );
    GRPH->door_red_spri.setTexture( GRPH->door_red_text );
    GRPH->door_purple_spri.setTexture( GRPH->door_purple_text );
    GRPH->gate_text.loadFromFile( "graphics/gate.png" );
    GRPH->red_key_text.loadFromFile( "graphics/red_key.png" );
    GRPH->green_key_text.loadFromFile( "graphics/green_key.png" );
    GRPH->purple_key_text.loadFromFile( "graphics/purple_key.png" );
    return GRPH;
}
