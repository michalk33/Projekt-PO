#include "button_onclicks.hpp"

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
