#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <SFML/Graphics.hpp>

const int TILE_SIZE = 60;
const int SLOW_MOVING_TIME_D = 8;
const int FAST_MOVING_TIME_D = 10;
const int BOX_MOVING_TIME_D = 10;
const int MOVING_INITIAL_STATE = 2000;
const int GATE_OPENING_TIME = 300;
const int KEY_SIZE = 30;
const int WINDOW_W = 1200;
const int WINDOW_H = 800;
const int MAX_LEVELS_PLAYING = 5;
const int MAX_LEVELS_EDITOR = 5;
const int MAX_L = 100;
const int MIN_L = 15;
const int MAX_C = 200;
const int EDITOR_WAITING_TIME = 100;
const int INJURY_TIME = 300;
const int FRAME_TIME_MS = 10;
const int ITERATION_TIME_MS = 1;

class graphics{
public:
    graphics();
    sf::Texture grass_text;
    sf::Texture wall_text;
    sf::Texture button_pr_text;
    sf::Texture button_unpr_text;
    sf::Texture exit_text;
    sf::Texture door_green_text;
    sf::Texture door_red_text;
    sf::Texture door_purple_text;
    sf::Sprite grass_spri;
    sf::Sprite wall_spri;
    sf::Sprite button_pr_spri;
    sf::Sprite button_unpr_spri;
    sf::Sprite exit_spri;
    sf::Sprite door_green_spri;
    sf::Sprite door_red_spri;
    sf::Sprite door_purple_spri;
    sf::Texture gate_text;
    sf::Texture red_key_text;
    sf::Texture green_key_text;
    sf::Texture purple_key_text;
    sf::Texture gate_h_text;
    sf::Texture gate_v_text;
    sf::Texture player_text;
    sf::Texture enemy_text;
    sf::Texture dirt_text;
    sf::Texture coin_text;
    sf::Texture box_text;
};

sf::Vector2i mousePosition( sf::RenderWindow* dest );

#endif
