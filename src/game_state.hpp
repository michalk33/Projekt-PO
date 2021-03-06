#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "button.hpp"
#include "enums.hpp"
#include "consts.hpp"

class GameState{
protected:
    sf::RectangleShape background;
    BTN** buttons;
    int btn_num;
public:
    GameState();
    ~GameState();
    virtual void run( GameController* gc, sf::RenderWindow* dest ) = 0;
    virtual void display( GameController* gc, sf::RenderWindow* dest ) = 0;
};

class PlayingState : public GameState{
private:
    sf::Text tmpsft;
    sf::RectangleShape background2;
public:
    PlayingState( sf::Font* font );
    ~PlayingState();
    void run( GameController* gc, sf::RenderWindow* dest ) override;
    void display( GameController* gc, sf::RenderWindow* dest ) override;
};

class TestingState : public GameState{
private:
    sf::Text tmpsft;
    sf::RectangleShape background2;
public:
    TestingState( sf::Font* font );
    ~TestingState();
    void run( GameController* gc, sf::RenderWindow* dest ) override;
    void display( GameController* gc, sf::RenderWindow* dest ) override;
};

class MainMenuState : public GameState{
private:
    sf::Text tmpsft;
public:
    MainMenuState( sf::Font* font );
    ~MainMenuState();
    void run( GameController* gc, sf::RenderWindow* dest ) override;
    void display( GameController* gc, sf::RenderWindow* dest ) override;
};

class ChoosingLevelState : public GameState{
private:
    sf::Text tmpsft;
public:
    ChoosingLevelState( sf::Font* font );
    ~ChoosingLevelState();
    void run( GameController* gc, sf::RenderWindow* dest ) override;
    void display( GameController* gc, sf::RenderWindow* dest ) override;
};

class ChoosingLevelEditorState : public GameState{
private:
    sf::Text tmpsft;
public:
    ChoosingLevelEditorState( sf::Font* font );
    ~ChoosingLevelEditorState();
    void run( GameController* gc, sf::RenderWindow* dest ) override;
    void display( GameController* gc, sf::RenderWindow* dest ) override;
};

class CreatingLvlState : public GameState{
private:
    sf::Text tmpsft;
public:
    int nw, nh, nc;
    CreatingLvlState( sf::Font* font );
    ~CreatingLvlState();
    void run( GameController* gc, sf::RenderWindow* dest ) override;
    void display( GameController* gc, sf::RenderWindow* dest ) override;
};

class SettingsState : public GameState{
private:
    sf::Text tmpsft;
public:
    SettingsState( sf::Font* font );
    ~SettingsState();
    void run( GameController* gc, sf::RenderWindow* dest ) override;
    void display( GameController* gc, sf::RenderWindow* dest ) override;
};

#endif
