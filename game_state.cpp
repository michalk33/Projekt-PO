#include "game_state.hpp"
#include "controller.hpp"

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

void return_from_playing( GameController* gc ){
    delete gc->brd;
    gc->state = choosing_level;
}

void restart_playing( GameController* gc ){
    delete gc->brd;
    gc->read_level();
}

void go_to_cpl( GameController* gc ){
    gc->level = 1;
    gc->state = choosing_level;
}

void go_to_cel( GameController* gc ){
    gc->level = -1;
    gc->state = choosing_editor_level;
}

void exit_all( GameController* gc ){
    gc->going = false;
}

void plus_lvl_ed( GameController* gc ){
    gc->level -= 1;
    if( gc->level < -MAX_LEVELS_EDITOR )
        gc->level = -MAX_LEVELS_EDITOR;
}

void minus_lvl_ed( GameController* gc ){
    gc->level += 1;
    if( gc->level > -1 )
        gc->level = -1;
}

void choose_lvl_ed( GameController* gc ){
    gc->state = editor;
    gc->read_level();
}

void plus_lvl_pl( GameController* gc ){
    gc->level += 1;
    if( gc->level > MAX_LEVELS_PLAYING )
        gc->level = MAX_LEVELS_PLAYING;
}

void minus_lvl_pl( GameController* gc ){
    gc->level -= 1;
    if( gc->level < 1 )
        gc->level = 1;
}

void choose_lvl_pl( GameController* gc ){
    gc->state = playing;
    gc->read_level();
}

void return_to_mm( GameController* gc ){
    gc->state = main_menu;
}

void return_from_testing( GameController* gc ){
    delete gc->brd;
    gc->state = editor;
    gc->read_level();
}

void next_level_playing( GameController* gc ){
    if( gc->brd->end_of_game() && !(gc->brd->lost_game()) ){
        delete gc->brd;
        gc->level++;
        if( gc->level > MAX_LEVELS_PLAYING ) gc->level = MAX_LEVELS_PLAYING;
        gc->read_level();
    }
}

void go_to_crt_nvl( GameController* gc ){
    gc->state = creating_level;
}

void save_lvl( GameController* gc ){
    gc->save_level();
}

void go_to_testing( GameController* gc ){
    gc->save_level();
    gc->state = testing;
}

void return_to_cel( GameController* gc ){
    delete gc->brd;
    gc->state = choosing_editor_level;
}

void grass_chs( GameController* gc ){
    gc->es.chs_tile = true;
    gc->es.chs_tile_type = grass;
}

void wall_chs( GameController* gc ){
    gc->es.chs_tile = true;
    gc->es.chs_tile_type = wall;
}

void button_chs( GameController* gc ){
    gc->es.chs_tile = true;
    gc->es.chs_tile_type = button_multiple_times;
}

void exit_chs( GameController* gc ){
    gc->es.chs_tile = true;
    gc->es.chs_tile_type = exitt;
}

void gate_v_chs( GameController* gc ){
    gc->es.vert = true;
    gc->es.chs_tile = true;
    gc->es.chs_tile_type = gate;
}

void gate_h_chs( GameController* gc ){
    gc->es.vert = false;
    gc->es.chs_tile = true;
    gc->es.chs_tile_type = gate;
}

void kr_chs( GameController* gc ){
    gc->es.chs_tile = false;
    gc->es.color = red;
    gc->es.chs_ent_type = key;
}

void kp_chs( GameController* gc ){
    gc->es.chs_tile = false;
    gc->es.color = purple;
    gc->es.chs_ent_type = key;
}

void kg_chs( GameController* gc ){
    gc->es.chs_tile = false;
    gc->es.color = green;
    gc->es.chs_ent_type = key;
}

void dirt_chs( GameController* gc ){
    gc->es.chs_tile = false;
    gc->es.chs_ent_type = dirt;
}

void coin_chs( GameController* gc ){
    gc->es.chs_tile = false;
    gc->es.chs_ent_type = coin;
}

void box_chs( GameController* gc ){
    gc->es.chs_tile = false;
    gc->es.chs_ent_type = box;
    gc->state = settings;
}

void pl_chs( GameController* gc ){
    gc->es.chs_tile = false;
    gc->es.chs_ent_type = player;
    gc->state = settings;
}

void en_chs( GameController* gc ){
    gc->es.chs_tile = false;
    gc->es.chs_ent_type = opponent;
    gc->state = settings;
}

void dr_chs( GameController* gc ){
    gc->es.chs_tile = true;
    gc->es.color = red;
    gc->es.chs_tile_type = door;
}

void dp_chs( GameController* gc ){
    gc->es.chs_tile = true;
    gc->es.color = purple;
    gc->es.chs_tile_type = door;
}

void dg_chs( GameController* gc ){
    gc->es.chs_tile = true;
    gc->es.color = green;
    gc->es.chs_tile_type = door;
}

void bot_chs( GameController* gc ){
    gc->es.chs_tile = true;
    gc->es.chs_tile_type = button_one_time;
}

void ret_to_ed( GameController* gc ){
    gc->state = editor;
}

void crt_nvl( GameController* gc ){
    gc->state = editor;
    delete gc->brd;
    gc->brd = create_new_board( gc->cnvl.nw, gc->cnvl.nh, gc->cnvl.nc );
}

void plus_nw( GameController* gc ){
    gc->cnvl.nw += 1;
    if( gc->cnvl.nw > MAX_L )
        gc->cnvl.nw = MAX_L;
}

void minus_nw( GameController* gc ){
    gc->cnvl.nw -= 1;
    if( gc->cnvl.nw < MIN_L )
        gc->cnvl.nw = MIN_L;
}

void plus_nh( GameController* gc ){
    gc->cnvl.nh += 1;
    if( gc->cnvl.nh > MAX_L )
        gc->cnvl.nh = MAX_L;
}

void minus_nh( GameController* gc ){
    gc->cnvl.nh -= 1;
    if( gc->cnvl.nh < MIN_L )
        gc->cnvl.nh = MIN_L;
}

void plus_nc( GameController* gc ){
    gc->cnvl.nc += 1;
    if( gc->cnvl.nc > MAX_C )
        gc->cnvl.nc = MAX_C;
}

void minus_nc( GameController* gc ){
    gc->cnvl.nc -= 1;
    if( gc->cnvl.nc < 0 )
        gc->cnvl.nc = 0;
}

void psh_set( GameController* gc ){
    gc->es.accpsh = !(gc->es.accpsh);
}

void dig_set( GameController* gc ){
    gc->es.accdgg = !(gc->es.accdgg);
}

void spd_set( GameController* gc ){
    gc->es.accspd = ( gc->es.accspd == fast ) ? slow : fast;
}

void wght_set( GameController* gc ){
    gc->es.accwght = ( gc->es.accwght == heavy ) ? light : heavy;
}

void done_set( GameController* gc ){
    gc->state = editor;
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

EditorState::EditorState( sf::Font* font, graphics* GRPH ) : GameState(), background2( sf::Vector2f( 200, WINDOW_H ) ){
    accwght = heavy;
    accspd = fast;
    accpsh = true;
    accdgg = true;
    chs_tile = true;
    vert = false;
    gate_placed = false;
    chs_tile_type = grass;
    chs_ent_type = dirt;
    time = 0;
    dx = 0;
    dy = 0;
    btn_num = 22;
    buttons = new BTN* [ btn_num ];
    buttons [ 0 ] = new BTN_CC( font, 1060, 50, 80, 20, go_to_crt_nvl, "NEW" );
    buttons [ 1 ] = new BTN_CC( font, 1060, 80, 80, 20, save_lvl, "SAVE" );
    buttons [ 2 ] = new BTN_CC( font, 1060, 110, 80, 20, go_to_testing, "TEST" );
    buttons [ 3 ] = new BTN_CC( font, 1060, 140, 80, 20, return_to_cel, "RETURN" );
    buttons [ 4 ] = new BTN_BMP( 1032, 180, 68, 68, grass_chs );
    buttons [ 4 ]->txt.loadFromFile( "graphics/grass.png" );
    buttons [ 4 ]->sprt.setTexture( buttons [ 4 ]->txt );
    buttons [ 4 ]->sprt.setPosition( 1036, 184 );
    buttons [ 5 ] = new BTN_BMP( 1100, 180, 68, 68, wall_chs );
    buttons [ 5 ]->txt.loadFromFile( "graphics/wall.png" );
    buttons [ 5 ]->sprt.setTexture( buttons [ 5 ]->txt );
    buttons [ 5 ]->sprt.setPosition( 1104, 184 );
    buttons [ 6 ] = new BTN_BMP( 1032, 250, 68, 68, gate_h_chs );
    buttons [ 6 ]->txt.loadFromFile( "graphics/gate_h.png" );
    buttons [ 6 ]->sprt.setTexture( buttons [ 6 ]->txt );
    buttons [ 6 ]->sprt.setPosition( 1036, 254 );
    buttons [ 7 ] = new BTN_BMP( 1100, 250, 68, 68, gate_v_chs );
    buttons [ 7 ]->txt.loadFromFile( "graphics/gate_v.png" );
    buttons [ 7 ]->sprt.setTexture( buttons [ 7 ]->txt );
    buttons [ 7 ]->sprt.setPosition( 1104, 254 );
    buttons [ 8 ] = new BTN_BMP( 1032, 320, 68, 68, exit_chs );
    buttons [ 8 ]->txt.loadFromFile( "graphics/exit.png" );
    buttons [ 8 ]->sprt.setTexture( buttons [ 8 ]->txt );
    buttons [ 8 ]->sprt.setPosition( 1036, 324 );
    buttons [ 9 ] = new BTN_BMP( 1100, 320, 68, 68, button_chs );
    buttons [ 9 ]->txt.loadFromFile( "graphics/button_unpr.png" );
    buttons [ 9 ]->sprt.setTexture( buttons [ 9 ]->txt );
    buttons [ 9 ]->sprt.setPosition( 1104, 324 );
    buttons [ 10 ] = new BTN_BMP( 1032, 390, 68, 68, dg_chs );
    buttons [ 10 ]->txt.loadFromFile( "graphics/door_green.png" );
    buttons [ 10 ]->sprt.setTexture( buttons [ 10 ]->txt );
    buttons [ 10 ]->sprt.setPosition( 1036, 394 );
    buttons [ 11 ] = new BTN_BMP( 1100, 390, 68, 68, kg_chs );
    buttons [ 11 ]->txt.loadFromFile( "graphics/green_key.png" );
    buttons [ 11 ]->sprt.setTexture( buttons [ 11 ]->txt );
    buttons [ 11 ]->sprt.setPosition( 1104, 394 );
    buttons [ 12 ] = new BTN_BMP( 1032, 460, 68, 68, dp_chs );
    buttons [ 12 ]->txt.loadFromFile( "graphics/door_purple.png" );
    buttons [ 12 ]->sprt.setTexture( buttons [ 12 ]->txt );
    buttons [ 12 ]->sprt.setPosition( 1036, 464 );
    buttons [ 13 ] = new BTN_BMP( 1100, 460, 68, 68, kp_chs );
    buttons [ 13 ]->txt.loadFromFile( "graphics/purple_key.png" );
    buttons [ 13 ]->sprt.setTexture( buttons [ 13 ]->txt );
    buttons [ 13 ]->sprt.setPosition( 1104, 464 );
    buttons [ 14 ] = new BTN_BMP( 1032, 530, 68, 68, dr_chs );
    buttons [ 14 ]->txt.loadFromFile( "graphics/door_red.png" );
    buttons [ 14 ]->sprt.setTexture( buttons [ 14 ]->txt );
    buttons [ 14 ]->sprt.setPosition( 1036, 534 );
    buttons [ 15 ] = new BTN_BMP( 1100, 530, 68, 68, kr_chs );
    buttons [ 15 ]->txt.loadFromFile( "graphics/red_key.png" );
    buttons [ 15 ]->sprt.setTexture( buttons [ 15 ]->txt );
    buttons [ 15 ]->sprt.setPosition( 1104, 534 );
    buttons [ 16 ] = new BTN_BMP( 1032, 600, 68, 68, bot_chs );
    buttons [ 16 ]->txt.loadFromFile( "graphics/button_pr.png" );
    buttons [ 16 ]->sprt.setTexture( buttons [ 16 ]->txt );
    buttons [ 16 ]->sprt.setPosition( 1036, 604 );
    buttons [ 17 ] = new BTN_BMP( 1100, 600, 68, 68, pl_chs );
    buttons [ 17 ]->txt.loadFromFile( "graphics/player.png" );
    buttons [ 17 ]->sprt.setTexture( buttons [ 17 ]->txt );
    buttons [ 17 ]->sprt.setPosition( 1104, 604 );
    buttons [ 18 ] = new BTN_BMP( 1032, 670, 68, 68, en_chs );
    buttons [ 18 ]->txt.loadFromFile( "graphics/enemy.png" );
    buttons [ 18 ]->sprt.setTexture( buttons [ 18 ]->txt );
    buttons [ 18 ]->sprt.setPosition( 1036, 674 );
    buttons [ 19 ] = new BTN_BMP( 1100, 670, 68, 68, dirt_chs );
    buttons [ 19 ]->txt.loadFromFile( "graphics/dirt.png" );
    buttons [ 19 ]->sprt.setTexture( buttons [ 19 ]->txt );
    buttons [ 19 ]->sprt.setPosition( 1104, 674 );
    buttons [ 20 ] = new BTN_BMP( 1032, 740, 68, 68, coin_chs );
    buttons [ 20 ]->txt.loadFromFile( "graphics/coin.png" );
    buttons [ 20 ]->sprt.setTexture( buttons [ 20 ]->txt );
    buttons [ 20 ]->sprt.setPosition( 1036, 744 );
    buttons [ 21 ] = new BTN_BMP( 1100, 740, 68, 68, box_chs );
    buttons [ 21 ]->txt.loadFromFile( "graphics/box.png" );
    buttons [ 21 ]->sprt.setTexture( buttons [ 21 ]->txt );
    buttons [ 21 ]->sprt.setPosition( 1104, 744 );
    background2.setFillColor( sf::Color( 200, 200, 200 ) );
    background2.setPosition( 1000, 0 );
}

EditorState::~EditorState(){}

void EditorState::run( GameController* gc, sf::RenderWindow* dest ){
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->run( gc, dest );
    time--;
    if( time < 0 ) time = 0;
    if( time == 0 ){
        enum direction tmp = pressed_dir();
        if( tmp != nothing ){
            time = EDITOR_WAITING_TIME;
            switch( tmp ){
            case up:
                dy += TILE_SIZE;
                break;
            case down:
                dy -= TILE_SIZE;
                break;
            case right:
                dx -= TILE_SIZE;
                break;
            case left:
                dx += TILE_SIZE;
                break;
            }
            if( dy <= -gc->brd->width * TILE_SIZE )
                dy = -gc->brd->width * TILE_SIZE + TILE_SIZE;
            if( dx <= -gc->brd->height * TILE_SIZE )
                dx = -gc->brd->height * TILE_SIZE + TILE_SIZE;
            if( dy >= 0 )
                dy = 0;
            if( dx >= 0 )
                dx = 0;
        }
    }
    if( chs_tile_type != gate || !chs_tile ) gate_placed = false;
    if( chs_ent_type != opponent || chs_tile ) opponent_placed = false;
    if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && !(gc->mouse_left_button_previously_pressed) && gate_placed ){
        sf::Vector2i mpos = sf::Mouse::getPosition( *dest );
        int tx = ( mpos.x - dx ) / TILE_SIZE;
        int ty = ( mpos.y - dy ) / TILE_SIZE;
        if( tx > 0 && tx < gc->brd->width - 1 && ty > 0 && ty < gc->brd->height - 1 ){
            if( gc->brd->tiles[tx][ty]->get_type() == button_multiple_times ||
                gc->brd->tiles[tx][ty]->get_type() == button_one_time ){
                    delete gc->brd->tiles[gx][gy];
                    if( gc->brd->tiles[tx][ty]->get_type() == button_one_time ){
                        ButtonOneTime* btptr = new ButtonOneTime();
                        delete gc->brd->tiles[tx][ty];
                        gc->brd->tiles[tx][ty] = (Tile*) btptr;
                        gc->brd->tiles[gx][gy] = new Gate( vert, (Button*) btptr, tx, ty );
                    }else{
                        ButtonMultipleTimes* btptr = new ButtonMultipleTimes();
                        delete gc->brd->tiles[tx][ty];
                        gc->brd->tiles[tx][ty] = (Tile*) btptr;
                        gc->brd->tiles[gx][gy] = new Gate( vert, (Button*) btptr, tx, ty );
                    }
                }
        }
        gate_placed = false;
    }
    bool optmp = false;
    if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && !(gc->mouse_left_button_previously_pressed) && opponent_placed ){
        sf::Vector2i mpos = sf::Mouse::getPosition( *dest );
        int tx = ( mpos.x - dx ) / TILE_SIZE;
        int ty = ( mpos.y - dy ) / TILE_SIZE;
        if( tx > 0 && tx < gc->brd->width - 1 && ty > 0 && ty < gc->brd->height - 1 ){
            Opponent* ptr = new Opponent( accwght, accspd, gx, gy, tx, ty );
            gc->brd->opponents.push_back( ptr );
            optmp = true;
        }
        opponent_placed = false;
    }
    if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && !(gc->mouse_left_button_previously_pressed) ){
        gate_placed = false;
        opponent_placed = false;
        sf::Vector2i mpos = sf::Mouse::getPosition( *dest );
        int tx = ( mpos.x - dx ) / TILE_SIZE;
        int ty = ( mpos.y - dy ) / TILE_SIZE;
        if( tx > 0 && tx < gc->brd->width - 1 && ty > 0 && ty < gc->brd->height - 1 && mpos.x < 1000 ){
            gc->brd->remove_entity( tx, ty );
            if( chs_tile ){
                switch( chs_tile_type ){
                case grass:
                    delete gc->brd->tiles[tx][ty];
                    gc->brd->tiles[tx][ty] = new Grass();
                    break;
                case wall:
                    delete gc->brd->tiles[tx][ty];
                    gc->brd->tiles[tx][ty] = new Wall();
                    break;
                case gate:
                    gate_placed = true;
                    gx = tx;
                    gy = ty;
                    break;
                case button_multiple_times:
                    delete gc->brd->tiles[tx][ty];
                    gc->brd->tiles[tx][ty] = new ButtonMultipleTimes();
                    break;
                case button_one_time:
                    delete gc->brd->tiles[tx][ty];
                    gc->brd->tiles[tx][ty] = new ButtonOneTime();
                    break;
                case door:
                    delete gc->brd->tiles[tx][ty];
                    gc->brd->tiles[tx][ty] = new Door( color );
                    break;
                case exitt:
                    delete gc->brd->tiles[tx][ty];
                    gc->brd->tiles[tx][ty] = new Exit();
                    break;
                }
            }else{
                Key* kptr;
                Dirt* dptr;
                Coin* cptr;
                Player* pptr;
                Box* bptr;
                switch( chs_ent_type ){
                case key:
                    kptr = new Key( color, tx, ty );
                    gc->brd->keys.push_back( kptr );
                    break;
                case dirt:
                    dptr = new Dirt( tx, ty );
                    gc->brd->dirts.push_back( dptr );
                    break;
                case coin:
                    cptr = new Coin( 1, tx, ty );
                    gc->brd->coins.push_back( cptr );
                    break;
                case player:
                    pptr = new Player( accwght, accspd, accdgg, accpsh, 3, tx, ty );
                    gc->brd->players.push_back( pptr );
                    break;
                case box:
                    bptr = new Box( accwght, tx, ty );
                    gc->brd->boxes.push_back( bptr );
                    break;
                case opponent:
                    if( !optmp ){
                        opponent_placed = true;
                        gx = tx;
                        gy = ty;
                    }
                    break;
                }
            }
        }
    }
}

void EditorState::display( GameController* gc, sf::RenderWindow* dest ){
    dest->draw( background );
    gc->brd->display2( dest, 0, 0, 1000, WINDOW_H, gc->GRPH, TILE_SIZE, dx, dy );
    dest->draw( background2 );
    for( int i = 0; i < btn_num; i++ )
        buttons[i]->display( dest );
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
