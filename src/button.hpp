#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <SFML/Graphics.hpp>
#include "tile.hpp"

class GameController;

class BTN{
protected:
    int x, y, w, h;
    std::function <void(GameController*)> onclick;
    bool pressed;
public:
    BTN( int nx, int ny, int nw, int nh, std::function <void(GameController*)> no );
    ~BTN();
    virtual void display( sf::RenderWindow* dest ) = 0;
    bool mouse_on( sf::RenderWindow* dest );
    void run( GameController* gc, sf::RenderWindow* dest );
};

class BTN_CC : public BTN{
protected:
    sf::Text name;
    sf::RectangleShape rect;
public:
    BTN_CC( sf::Font* font, int nx, int ny, int nw, int nh, std::function <void(GameController*)> no, const char* nname );
    ~BTN_CC();
    void display( sf::RenderWindow* dest ) override;
};

class BTN_BMP : public BTN{
protected:
    sf::Sprite sprt;
    sf::RectangleShape rect;
public:
    BTN_BMP( sf::Texture* txt, int nx, int ny, int nw, int nh, std::function <void(GameController*)> no );
    ~BTN_BMP();
    void display( sf::RenderWindow* dest ) override;
};

#endif
