#include "main_controller.hpp"

main_controller::main_controller(){
    window = new sf::RenderWindow( sf::VideoMode( WINDOW_W, WINDOW_H, 32 ), "Labirynt" );
    font = new sf::Font();
    font->loadFromFile("fonts/OpenSans-Regular.ttf");
    GC = new GameController( font );
}

main_controller::~main_controller(){
    delete window;
    delete font;
    delete GC;
}

void main_controller::start(){
    sf::Clock frm_clock, itr_clock;
    sf::Time tm;
    while( GC->going )
    {
        tm = frm_clock.getElapsedTime();
        if( tm.asMilliseconds() >= FRAME_TIME_MS ){
            GC->display( window );
            window->display();
            frm_clock.restart();
        }
        tm = itr_clock.getElapsedTime();
        if( tm.asMilliseconds() >= ITERATION_TIME_MS ){
            GC->run( window );
            itr_clock.restart();
        }
    }
}
