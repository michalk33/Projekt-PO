#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <fstream>

#include "board.hpp"
#include "button.hpp"
#include "game_state.hpp"

class GameController{
public:
    GameController( sf::Font* font );
    ~GameController();
    graphics* GRPH;
    bool mouse_left_button_previously_pressed;
    bool going;
    Board* brd;
    enum app_states state;
    int level;
    MainMenuState mms;
    ChoosingLevelState cls;
    ChoosingLevelEditorState cles;
    PlayingState ps;
    TestingState ts;
    EditorState es;
    CreatingLvlState cnvl;
    SettingsState sets;
    void run( sf::RenderWindow* dest );
    void display( sf::RenderWindow* dest );
    void read_level();
    void save_level();
    friend class BTN;
};

const char* file_name( int i, bool e );

void WriteBool( bool b, std::ofstream* ff );
bool ReadBool(std::ifstream* ff);
void WriteChar(char c, std::ofstream* ff);
char ReadChar(std::ifstream* ff);
void WriteInt(int n, std::ofstream* ff);
int ReadInt(std::ifstream* ff);

#endif
