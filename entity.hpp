#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "enums.hpp"
#include "consts.hpp"

class Board;

class Entity{
protected:
    int pos_x, pos_y, moving_state;
    enum direction dir;
    enum entity_states state;
    void go( Board* brd, int time_d );
    bool try_moving( enum direction ndr, Board* brd, bool dg, bool cl, bool ps );
    void start_moving( enum direction ndr, Board* brd );
    float dist( int tile_size );
public:
    Entity( int x, int y );
    ~Entity();
    virtual void run( Board* brd, bool focus ) = 0;
    virtual enum entity_types type() = 0;
    virtual void display( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) = 0;
    virtual enum weight_types weight_type() = 0;
    enum entity_states get_state();
    friend class Board;
    friend class GameController;
};

class Collectible : public Entity{
public:
    Collectible( int x, int y );
    ~Collectible();
    void run( Board* brd, bool focus ) override;
    enum weight_types weight_type() override;
};

class Key : public Collectible{
private:
    enum key_colors color;
public:
    Key( enum key_colors clr, int x, int y );
    ~Key();
    enum key_colors get_color();
    void display( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) override;
    enum entity_types type() override;
};

class Coin : public Collectible{
private:
    int value;
public:
    Coin( int val, int x, int y );
    ~Coin();
    int get_value();
    void display( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) override;
    enum entity_types type() override;
};

class Dirt : public Collectible{
public:
    Dirt( int x, int y );
    ~Dirt();
    void display( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) override;
    enum entity_types type() override;
};

class Box : public Entity{
protected:
    enum weight_types weight;
public:
    Box( enum weight_types wght, int x, int y );
    ~Box();
    void run( Board* brd, bool focus ) override;
    void display( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) override;
    enum entity_types type() override;
    enum weight_types weight_type() override;
};

class Opponent : public Entity{
protected:
    enum weight_types weight;
    enum speed_types speed;
    int pos1_x, pos2_x, pos1_y, pos2_y;
    bool to_first;
public:
    Opponent( enum weight_types wght, enum speed_types spd, int x, int y, int pos2x, int pos2y );
    ~Opponent();
    void run( Board* brd, bool focus ) override;
    void display( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) override;
    enum entity_types type() override;
    enum weight_types weight_type() override;
    friend class GameController;
};

class Player : public Entity{
protected:
    enum player_states player_state;
    enum weight_types weight;
    enum speed_types speed;
    bool digging, pushing;
    int lifes, player_state_time;
    std::vector<enum key_colors> keys;
public:
    Player( enum weight_types wght, enum speed_types spd, bool dgg, bool psh, int lfs, int x, int y );
    ~Player();
    void run( Board* brd, bool focus ) override;
    void display( sf::RenderWindow* dest, int bx, int by, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) override;
    enum entity_types type() override;
    bool have_key( enum key_colors key_color );
    enum weight_types weight_type() override;
    int get_lifes();
    friend class Entity;
    friend class GameController;
};

#endif
