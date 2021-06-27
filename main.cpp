#include <SFML/Window.hpp>

#include "controller.hpp"

int main()
{
    sf::RenderWindow main_window( sf::VideoMode( WINDOW_W, WINDOW_H, 32 ), "Labirynt" );
    sf::Font font;
    font.loadFromFile("fonts/OpenSans-Regular.ttf");
    GameController* MGC = new GameController( &font );
    while( MGC->going )
    {
        MGC->run( &main_window );
        MGC->display( &main_window );
        main_window.display();
    }
    return 0;
}
