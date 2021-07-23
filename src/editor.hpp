#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "game_state.hpp"

class EditorState : public GameState{
protected:
    sf::CircleShape posf, posl;
public:
    sf::Text tmpsft;
    sf::RectangleShape background2;
    int time, dx, dy, gx, gy;
    enum key_colors color;
    bool vert;
    bool gate_placed, opponent_placed;;
    bool chs_tile;
    bool accdgg, accpsh;
    Opponent* opptr;
    enum weight_types accwght;
    enum speed_types accspd;
    enum tile_types chs_tile_type;
    enum entity_types chs_ent_type;
    EditorState( sf::Font* font, graphics* GRPH );
    ~EditorState();
    void run( GameController* gc, sf::RenderWindow* dest ) override;
    void display( GameController* gc, sf::RenderWindow* dest ) override;
};

#endif
