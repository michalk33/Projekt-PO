#ifndef ENUMS_HPP
#define ENUMS_HPP

#include <utility>
#include <string>

std::string tostring( int x );

enum direction{
    up,
    right,
    down,
    left,
    nothing
};

enum key_colors{
    red,
    green,
    purple
};

enum entity_states{
    moving,
    staying
};

enum weight_types{
    heavy,
    light
};

enum speed_types{
    slow,
    fast
};

enum player_states{
    injured,
    normal
};

enum entity_types{
    box,
    player,
    opponent,
    dirt,
    coin,
    key
};

enum button_states{
    pressed,
    unpressed
};

enum gate_states{
    locked,
    unlocked,
    closing,
    opening
};

enum tile_types{
    grass,
    wall,
    door,
    exitt,
    gate,
    button_one_time,
    button_multiple_times
};

enum app_states{
    playing,
    main_menu,
    choosing_level,
    choosing_editor_level,
    editor,
    testing,
    creating_level,
    settings
};

enum direction clockwise( enum direction dir );
enum direction cunterclockwise( enum direction dir );
int moving_time_d( enum speed_types spd );
std::pair<int,int> new_coordinates( int x, int y, enum direction dir );
enum direction pressed_dir();
int pressed_num();
int limit( int max, int min, int val );

#endif
