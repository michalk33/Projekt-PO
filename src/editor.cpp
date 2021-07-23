#include "editor.hpp"
#include "button_onclicks.hpp"

EditorState::EditorState( sf::Font* font, graphics* GRPH ) : GameState(), background2( sf::Vector2f( 300, WINDOW_H ) ),
    posf( TILE_SIZE / 3 ), posl( TILE_SIZE / 3 ){
        opptr = nullptr;
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
        btn_num = 23;
        buttons = new BTN* [ btn_num ];
        int bxs[18], bys[18];
        for( int i = 0; i < 6; i++ )
            bys[i] = bys[6+i] = bys[12+i] = 300 + 68 * i;
        for( int i = 0; i < 6; i++ ){
            bxs[i] = 950;
            bxs[6+i] = 1018;
            bxs[12+i] = 1086;
        }
        buttons [ 0 ] = new BTN_CC( font, 1000, 40, 80, 20, go_to_crt_nvl, "NEW" );
        buttons [ 1 ] = new BTN_CC( font, 1000, 65, 80, 20, save_lvl, "SAVE" );
        buttons [ 2 ] = new BTN_CC( font, 1000, 90, 80, 20, go_to_testing, "TEST" );
        buttons [ 3 ] = new BTN_CC( font, 1000, 115, 80, 20, return_to_cel, "RETURN" );
        buttons [ 4 ] = new BTN_BMP( &(GRPH->grass_text), bxs[0], bys[0], 68, 68, grass_chs );
        buttons [ 5 ] = new BTN_BMP( &(GRPH->wall_text), bxs[1], bys[1], 68, 68, wall_chs );
        buttons [ 6 ] = new BTN_BMP( &(GRPH->gate_h_text), bxs[2], bys[2], 68, 68, gate_h_chs );
        buttons [ 7 ] = new BTN_BMP( &(GRPH->gate_v_text), bxs[3], bys[3], 68, 68, gate_v_chs );
        buttons [ 8 ] = new BTN_BMP( &(GRPH->exit_text), bxs[4], bys[4], 68, 68, exit_chs );
        buttons [ 9 ] = new BTN_BMP( &(GRPH->button_unpr_text), bxs[5], bys[5], 68, 68, button_chs );
        buttons [ 10 ] = new BTN_BMP( &(GRPH->door_green_text), bxs[6], bys[6], 68, 68, dg_chs );
        buttons [ 11 ] = new BTN_BMP( &(GRPH->green_key_text), bxs[7], bys[7], 68, 68, kg_chs );
        buttons [ 12 ] = new BTN_BMP( &(GRPH->door_purple_text), bxs[8], bys[8], 68, 68, dp_chs );
        buttons [ 13 ] = new BTN_BMP( &(GRPH->purple_key_text), bxs[9], bys[9], 68, 68, kp_chs );
        buttons [ 14 ] = new BTN_BMP( &(GRPH->door_red_text), bxs[10], bys[10], 68, 68, dr_chs );
        buttons [ 15 ] = new BTN_BMP( &(GRPH->red_key_text), bxs[11], bys[11], 68, 68, kr_chs );
        buttons [ 16 ] = new BTN_BMP( &(GRPH->button_pr_text), bxs[12], bys[12], 68, 68, bot_chs );
        buttons [ 17 ] = new BTN_BMP( &(GRPH->player_text), bxs[13], bys[13], 68, 68, pl_chs );
        buttons [ 18 ] = new BTN_BMP( &(GRPH->enemy_text), bxs[14], bys[14], 68, 68, en_chs );
        buttons [ 19 ] = new BTN_BMP( &(GRPH->dirt_text), bxs[15], bys[15], 68, 68, dirt_chs );
        buttons [ 20 ] = new BTN_BMP( &(GRPH->coin_text), bxs[16], bys[16], 68, 68, coin_chs );
        buttons [ 21 ] = new BTN_BMP( &(GRPH->box_text), bxs[17], bys[17], 68, 68, box_chs );
        buttons [ 22 ] = new BTN_CC( font, 1000, 140, 80, 20, enemy_done, "DONE" );
        background2.setFillColor( sf::Color( 200, 200, 200 ) );
        background2.setPosition( 900, 0 );
        posf.setOutlineThickness( 4 );
        posf.setFillColor( sf::Color( 50, 200, 80, 200 ) );
        posf.setOutlineColor( sf::Color( 20, 150, 30, 200 ) );
        posl.setOutlineThickness( 4 );
        posl.setFillColor( sf::Color( 200, 50, 80, 200 ) );
        posl.setOutlineColor( sf::Color( 150, 20, 30, 200 ) );
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
    sf::Vector2i mpos = mousePosition( dest );
    int tx = ( mpos.x - dx ) / TILE_SIZE;
    int ty = ( mpos.y - dy ) / TILE_SIZE;
    if( chs_tile_type != gate || !chs_tile ) gate_placed = false;
    if( chs_ent_type != opponent || chs_tile ) opponent_placed = false;
    if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && !(gc->mouse_left_button_previously_pressed) && gate_placed ){
        if( tx > 0 && tx < gc->brd->width - 1 && ty > 0 && ty < gc->brd->height - 1 && mpos.x < 900 ){
            if( gc->brd->tiles[tx][ty]->get_type() == button_multiple_times ||
                gc->brd->tiles[tx][ty]->get_type() == button_one_time ){
                    delete gc->brd->tiles[gx][gy];
                    gc->brd->tiles[gx][gy] = new Gate( vert, nullptr, tx, ty );
                }
        }
        gate_placed = false;
    }else if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && !(gc->mouse_left_button_previously_pressed) && opponent_placed ){
        if( tx > 0 && tx < gc->brd->width - 1 && ty > 0 && ty < gc->brd->height - 1 && mpos.x < 900 &&
            ( opptr->positions[opptr->positions.size()-1].first == tx || opptr->positions[opptr->positions.size()-1].second == ty ) ){
            opptr->add_position( tx, ty );
        }
    }else if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && !(gc->mouse_left_button_previously_pressed) ){
        if( tx > 0 && tx < gc->brd->width - 1 && ty > 0 && ty < gc->brd->height - 1 && mpos.x < 900 ){
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
            }else if( gc->brd->tiles[tx][ty]->walkable( nullptr ) ){
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
                    if( !opponent_placed ){
                        opponent_placed = true;
                        if( opptr ) delete opptr;
                        opptr = new Opponent( accwght, accspd, tx, ty );
                    }
                    break;
                }
            }
        }
    }
}

void EditorState::display( GameController* gc, sf::RenderWindow* dest ){
    dest->draw( background );
    gc->brd->display2( dest, 0, 0, 1000, WINDOW_H, &(gc->GRPH), TILE_SIZE, dx, dy );
    if( opponent_placed ){
        posf.setPosition( opptr->positions[0].first * TILE_SIZE + TILE_SIZE / 6 + dx,
                          opptr->positions[0].second * TILE_SIZE + TILE_SIZE / 6 + dy );
        posl.setPosition( opptr->positions[opptr->positions.size()-1].first * TILE_SIZE + TILE_SIZE / 6 + dx,
                          opptr->positions[opptr->positions.size()-1].second * TILE_SIZE + TILE_SIZE / 6 + dy );
        dest->draw( posf );
        dest->draw( posl );
    }
    if( gate_placed ){
        posf.setPosition( gx * TILE_SIZE + TILE_SIZE / 6 + dx,
                          gy * TILE_SIZE + TILE_SIZE / 6 + dy );
        dest->draw( posf );
    }
    dest->draw( background2 );
    for( int i = 0; i < btn_num; i++ )
        if( i != 22 || opponent_placed ) buttons[i]->display( dest );
}
