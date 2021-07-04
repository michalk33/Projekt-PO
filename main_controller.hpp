#ifndef MAIN_CONTROLLER_HPP
#define MAIN_CONTROLLER_HPP

#include "controller.hpp"

class main_controller{
private:
    sf::RenderWindow* window;
    sf::Font* font;
    GameController* GC;
public:
    main_controller();
    ~main_controller();
    void start();
};

#endif
