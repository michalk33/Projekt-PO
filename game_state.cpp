#include "button_onclicks.hpp"

GameState::GameState() : background( sf::Vector2f( WINDOW_W, WINDOW_H ) ){
    btn_num = 0;
    buttons = nullptr;
    background.setFillColor( sf::Color( 200, 200, 200 ) );
    background.setPosition( 0, 0 );
}

GameState::~GameState(){
    if( buttons ){
        for( int i = 0; i < btn_num; i++ )
            delete buttons [ i ];
        delete[] buttons;
    }
}

PlayingState::PlayingState( sf::Font* font ) : GameState(), background2( sf::Vector2f( 200, WINDOW_H ) ){
    btn_num = 3;
    buttons = new BTN* [ btn_num ];
    buttons [ 0 ] = new BTN_CC( font, 1040, 50, 110, 20, return_from_playing, "RETURN" );
    buttons [ 1 ] = new BTN_CC( font, 1040, 80, 110, 20, restart_playing, "RESTART" );
    buttons [ 2 ] = new BTN_CC( font, 1040, 110, 110, 20, next_level_playing, "NEXT LEVEL" );
    background2.setFillColor( sf::Color( 200, 200, 200 ) );
    background2.setPosition( 1000, 0 );
    tmpsft.setFont(*font);
    tmpsft.setCharacterSize( 20 );
}

PlayingState::~PlayingState(){}

void PlayingState::run( GameController* gc, sf::RenderWindow* dest ){
    if( !(gc->brd->end_of_game()) )
        gc->brd->run();
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->run( gc, dest );
}

void PlayingState::display( GameController* gc, sf::RenderWindow* dest ){
    dest->draw( background );
    gc->brd->display( dest, 0, 0, 1000, WINDOW_H, gc->GRPH, TILE_SIZE );
    dest->draw( background2 );
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->display( dest );
    tmpsft.setString( "Lifes:" );
    tmpsft.setPosition( 1080, 140 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
    tmpsft.setString( sf::String( tostring( gc->brd->players[gc->brd->player_focus]->get_lifes() ) ) );
    tmpsft.setPosition( 1080, 160 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
    tmpsft.setString( "Coins:" );
    tmpsft.setPosition( 1080, 180 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
    tmpsft.setString( sf::String( tostring( gc->brd->needed_coins ) ) );
    tmpsft.setPosition( 1080, 200 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
}

TestingState::TestingState( sf::Font* font ) : GameState(), background2( sf::Vector2f( 200, WINDOW_H ) ){
    btn_num = 2;
    buttons = new BTN* [ btn_num ];
    buttons [ 0 ] = new BTN_CC( font, 1060, 50, 80, 20, return_from_testing, "RETURN" );
    buttons [ 1 ] = new BTN_CC( font, 1060, 80, 80, 20, restart_playing, "RESTART" );
    background2.setFillColor( sf::Color( 200, 200, 200 ) );
    background2.setPosition( 1000, 0 );
    tmpsft.setFont(*font);
    tmpsft.setCharacterSize( 20 );
}

TestingState::~TestingState(){}

void TestingState::run( GameController* gc, sf::RenderWindow* dest ){
    if( !(gc->brd->end_of_game()) )
        gc->brd->run();
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->run( gc, dest );
}

void TestingState::display( GameController* gc, sf::RenderWindow* dest ){
    dest->draw( background );
    gc->brd->display( dest, 0, 0, 1000, WINDOW_H, gc->GRPH, TILE_SIZE );
    dest->draw( background2 );
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->display( dest );
    tmpsft.setString( "Lifes:" );
    tmpsft.setPosition( 1080, 140 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
    tmpsft.setString( sf::String( tostring( gc->brd->players[gc->brd->player_focus]->get_lifes() ) ) );
    tmpsft.setPosition( 1080, 160 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
    tmpsft.setString( "Coins:" );
    tmpsft.setPosition( 1080, 180 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
    tmpsft.setString( sf::String( tostring( gc->brd->needed_coins ) ) );
    tmpsft.setPosition( 1080, 200 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
}

MainMenuState::MainMenuState( sf::Font* font ) : GameState(){
    btn_num = 3;
    buttons = new BTN* [ btn_num ];
    buttons [ 0 ] = new BTN_CC( font, 560, 330, 80, 20, go_to_cpl, "PLAY" );
    buttons [ 1 ] = new BTN_CC( font, 560, 370, 80, 20, go_to_cel, "EDIT" );
    buttons [ 2 ] = new BTN_CC( font, 560, 400, 80, 20, exit_all, "EXIT" );
}

MainMenuState::~MainMenuState(){}

void MainMenuState::run( GameController* gc, sf::RenderWindow* dest ){
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->run( gc, dest );
}

void MainMenuState::display( GameController* gc, sf::RenderWindow* dest ){
    dest->draw( background );
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->display( dest );
}

ChoosingLevelEditorState::ChoosingLevelEditorState( sf::Font* font ) : GameState(){
    btn_num = 4;
    buttons = new BTN* [ btn_num ];
    buttons [ 0 ] = new BTN_CC( font, 540, 380, 20, 20, plus_lvl_ed, "+" );
    buttons [ 1 ] = new BTN_CC( font, 640, 380, 20, 20, minus_lvl_ed, "-" );
    buttons [ 2 ] = new BTN_CC( font, 500, 420, 80, 20, choose_lvl_ed, "CHOOSE" );
    buttons [ 3 ] = new BTN_CC( font, 620, 420, 80, 20, return_to_mm, "RETURN" );
    tmpsft.setFont(*font);
    tmpsft.setCharacterSize( 20 );
}

ChoosingLevelEditorState::~ChoosingLevelEditorState(){}

void ChoosingLevelEditorState::run( GameController* gc, sf::RenderWindow* dest ){
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->run( gc, dest );
}

void ChoosingLevelEditorState::display( GameController* gc, sf::RenderWindow* dest ){
    dest->draw( background );
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->display( dest );
    tmpsft.setString( sf::String( tostring( -(gc->level) ) ) );
    tmpsft.setPosition( 590, 380 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
}

ChoosingLevelState::ChoosingLevelState( sf::Font* font ) : GameState(){
    btn_num = 4;
    buttons = new BTN* [ btn_num ];
    buttons [ 0 ] = new BTN_CC( font, 540, 380, 20, 20, plus_lvl_pl, "+" );
    buttons [ 1 ] = new BTN_CC( font, 640, 380, 20, 20, minus_lvl_pl, "-" );
    buttons [ 2 ] = new BTN_CC( font, 500, 420, 80, 20, choose_lvl_pl, "CHOOSE" );
    buttons [ 3 ] = new BTN_CC( font, 620, 420, 80, 20, return_to_mm, "RETURN" );
    tmpsft.setFont(*font);
    tmpsft.setCharacterSize( 20 );
}

ChoosingLevelState::~ChoosingLevelState(){}

void ChoosingLevelState::run( GameController* gc, sf::RenderWindow* dest ){
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->run( gc, dest );
}

void ChoosingLevelState::display( GameController* gc, sf::RenderWindow* dest ){
    dest->draw( background );
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->display( dest );
    tmpsft.setString( sf::String( tostring( gc->level ) ) );
    tmpsft.setPosition( 590, 380 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
}

CreatingLvlState::CreatingLvlState( sf::Font* font ) : GameState(){
    nw = 30;
    nh = 30;
    btn_num = 8;
    buttons = new BTN* [ btn_num ];
    buttons [ 0 ] = new BTN_CC( font, 540, 380, 20, 20, plus_nw, "+" );
    buttons [ 1 ] = new BTN_CC( font, 640, 380, 20, 20, minus_nw, "-" );
    buttons [ 2 ] = new BTN_CC( font, 540, 420, 20, 20, plus_nh, "+" );
    buttons [ 3 ] = new BTN_CC( font, 640, 420, 20, 20, minus_nh, "-" );
    buttons [ 4 ] = new BTN_CC( font, 540, 460, 20, 20, plus_nc, "+" );
    buttons [ 5 ] = new BTN_CC( font, 640, 460, 20, 20, minus_nc, "-" );
    buttons [ 6 ] = new BTN_CC( font, 500, 500, 80, 20, crt_nvl, "CREATE" );
    buttons [ 7 ] = new BTN_CC( font, 620, 500, 80, 20, ret_to_ed, "RETURN" );
    tmpsft.setFont(*font);
    tmpsft.setCharacterSize( 20 );
}

CreatingLvlState::~CreatingLvlState(){}

void CreatingLvlState::run( GameController* gc, sf::RenderWindow* dest ){
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->run( gc, dest );
}

void CreatingLvlState::display( GameController* gc, sf::RenderWindow* dest ){
    dest->draw( background );
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->display( dest );
    tmpsft.setString( sf::String( tostring( nw ) ) );
    tmpsft.setPosition( 590, 380 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
    tmpsft.setString( sf::String( tostring( nh ) ) );
    tmpsft.setPosition( 590, 420 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
    tmpsft.setString( sf::String( tostring( nc ) ) );
    tmpsft.setPosition( 590, 460 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
}

SettingsState::SettingsState( sf::Font* font ) : GameState(){
    btn_num = 5;
    buttons = new BTN* [ btn_num ];
    buttons [ 0 ] = new BTN_CC( font, 500, 380, 200, 20, wght_set, "CHANGE WEIGHT" );
    buttons [ 1 ] = new BTN_CC( font, 500, 440, 200, 20, spd_set, "CHANGE SPEED" );
    buttons [ 2 ] = new BTN_CC( font, 500, 500, 200, 20, dig_set, "CHANGE DIGGING" );
    buttons [ 3 ] = new BTN_CC( font, 500, 560, 200, 20, psh_set, "CHANGE PUSHING" );
    buttons [ 4 ] = new BTN_CC( font, 560, 620, 80, 20, done_set, "DONE" );
    tmpsft.setFont(*font);
    tmpsft.setCharacterSize( 20 );
}

SettingsState::~SettingsState(){}

void SettingsState::run( GameController* gc, sf::RenderWindow* dest ){
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->run( gc, dest );
}

void SettingsState::display( GameController* gc, sf::RenderWindow* dest ){
    dest->draw( background );
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->display( dest );
    if( gc->es.accwght == heavy )
        tmpsft.setString( sf::String( "Heavy" ) );
    if( gc->es.accwght == light )
        tmpsft.setString( sf::String( "Light" ) );
    tmpsft.setPosition( 500, 410 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
    if( gc->es.accspd == fast )
        tmpsft.setString( sf::String( "Fast" ) );
    if( gc->es.accspd == slow )
        tmpsft.setString( sf::String( "Slow" ) );
    tmpsft.setPosition( 500, 470 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
    if( gc->es.accdgg )
        tmpsft.setString( sf::String( "Digging" ) );
    else
        tmpsft.setString( sf::String( "Not digging" ) );
    tmpsft.setPosition( 500, 530 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
    if( gc->es.accpsh )
        tmpsft.setString( sf::String( "Pushing" ) );
    else
        tmpsft.setString( sf::String( "Not pushing" ) );
    tmpsft.setPosition( 500, 590 );
    tmpsft.setFillColor( sf::Color( 1, 1, 1 ) );
    dest->draw( tmpsft );
}
