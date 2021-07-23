#ifndef TILE_HPP
#define TILE_HPP

#include "enums.hpp"
#include "consts.hpp"
#include "entity.hpp"

class Tile{
protected:
    Entity* entity_ptr;
public:
    Tile();
    ~Tile();
    virtual bool pushable() = 0;
    virtual bool walkable( Player* player_ptr ) = 0;
    virtual void run( int x, int y, Board* brd ) = 0;
    virtual void display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) = 0;
    virtual enum tile_types get_type() = 0;
    virtual enum key_colors get_color() = 0;
    virtual int get_btnx() = 0;
    virtual int get_btny() = 0;
    virtual bool get_vert() = 0;
    void set_entity( Entity* ent_ptr );
    void unset_entity();
    Entity* get_entity_ptr();
    friend class GameController;
};

class Grass : public Tile{
public:
    Grass();
    ~Grass();
    bool pushable() override;
    bool walkable( Player* player_ptr ) override;
    void run( int x, int y, Board* brd ) override;
    void display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) override;
    enum tile_types get_type() override;
    enum key_colors get_color() override;
    int get_btnx() override;
    int get_btny() override;
    bool get_vert() override;
};

class Wall : public Tile{
public:
    Wall();
    ~Wall();
    bool pushable() override;
    bool walkable( Player* player_ptr ) override;
    void run( int x, int y, Board* brd ) override;
    void display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) override;
    enum tile_types get_type() override;
    enum key_colors get_color() override;
    int get_btnx() override;
    int get_btny() override;
    bool get_vert() override;
};

class Door : public Tile{
private:
    enum key_colors color;
public:
    Door( enum key_colors clr );
    ~Door();
    bool pushable() override;
    bool walkable( Player* player_ptr ) override;
    void run( int x, int y, Board* brd ) override;
    void display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) override;
    enum tile_types get_type() override;
    enum key_colors get_color() override;
    int get_btnx() override;
    int get_btny() override;
    bool get_vert() override;
};

class Exit : public Tile{
public:
    Exit();
    ~Exit();
    bool pushable() override;
    bool walkable( Player* player_ptr ) override;
    void run( int x, int y, Board* brd ) override;
    void display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) override;
    enum tile_types get_type() override;
    enum key_colors get_color() override;
    int get_btnx() override;
    int get_btny() override;
    bool get_vert() override;
};

class Button : public Tile{
protected:
    enum button_states state;
public:
    Button();
    ~Button();
    bool pushable() override;
    bool walkable( Player* player_ptr ) override;
    enum button_states get_state();
};

class ButtonOneTime : public Button{
public:
    ButtonOneTime();
    ~ButtonOneTime();
    void run( int x, int y, Board* brd ) override;
    void display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) override;
    enum tile_types get_type() override;
    enum key_colors get_color() override;
    int get_btnx() override;
    int get_btny() override;
    bool get_vert() override;
};

class ButtonMultipleTimes : public Button{
public:
    ButtonMultipleTimes();
    ~ButtonMultipleTimes();
    void run( int x, int y, Board* brd ) override;
    void display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) override;
    enum tile_types get_type() override;
    enum key_colors get_color() override;
    int get_btnx() override;
    int get_btny() override;
    bool get_vert() override;
};

class Gate : public Tile{
private:
    enum gate_states state;
    int time, btnx, btny;
    bool vertical;
    Button* button_ptr;
public:
    Gate( bool vert, Button* bptr, int btx, int bty );
    ~Gate();
    bool pushable() override;
    bool walkable( Player* player_ptr ) override;
    void run( int x, int y, Board* brd ) override;
    void display( sf::RenderWindow* dest, int bx, int by, int x, int y, int tile_size, int brx, int bry, int w, int h, graphics* GRPH ) override;
    enum tile_types get_type() override;
    enum key_colors get_color() override;
    int get_btnx() override;
    int get_btny() override;
    bool get_vert() override;
};

#endif
