#include "controller.hpp"

GameController::GameController( sf::Font* font ) : mms( font ), cls( font ), cles( font ), ps( font ), ts( font ), es( font, GRPH ), cnvl( font ), sets( font ) {
    GRPH = load_textures();
    going = true;
    state = main_menu;
}

GameController::~GameController(){
    if( brd ) delete brd;
    //delete GRPH; ????
}

void GameController::run( sf::RenderWindow* dest ){
    switch( state ){
    case main_menu:
        mms.run( this, dest );
        break;
    case choosing_level:
        cls.run( this, dest );
        break;
    case choosing_editor_level:
        cles.run( this, dest );
        break;
    case testing:
        ts.run( this, dest );
        break;
    case playing:
        ps.run( this, dest );
        break;
    case editor:
        es.run( this, dest );
        break;
    case creating_level:
        cnvl.run( this, dest );
        break;
    case settings:
        sets.run( this, dest );
        break;
    }
    sf::Event tmpev;
    while( dest->pollEvent( tmpev ) )
    {
        if( tmpev.type == sf::Event::Closed )
            going = false;
    }
    if( !going )
        dest->close();
    mouse_left_button_previously_pressed = sf::Mouse::isButtonPressed( sf::Mouse::Left );
}

void GameController::display( sf::RenderWindow* dest ){
    switch( state ){
    case main_menu:
        mms.display( this, dest );
        break;
    case choosing_level:
        cls.display( this, dest );
        break;
    case choosing_editor_level:
        cles.display( this, dest );
        break;
    case testing:
        ts.display( this, dest );
        break;
    case playing:
        ps.display( this, dest );
        break;
    case editor:
        es.display( this, dest );
        break;
    case creating_level:
        cnvl.display( this, dest );
        break;
    case settings:
        sets.display( this, dest );
        break;
    }
}

const char* file_name( int i, bool e ){
    if( e ){
        switch( i ){
        case 1: return "001.lvl";
        case 2: return "002.lvl";
        case 3: return "003.lvl";
        case 4: return "004.lvl";
        case 5: return "005.lvl";
        }
    }else{
        switch( i ){
        case 1: return "001p.lvl";
        case 2: return "002p.lvl";
        case 3: return "003p.lvl";
        case 4: return "004p.lvl";
        case 5: return "005p.lvl";
        }
    }
    return "temp.lvl";
}

void WriteBool( bool b, std::ofstream* ff )
{
    char c;
    if (b) {c = 127;}
    else {c = -128;}
    ff->write((const char*)&c, sizeof c);
}

bool ReadBool(std::ifstream* ff)
{
    char c;
    ff->read((char*)&c, sizeof c);
    return c >= 0;
}

void WriteChar(char c, std::ofstream* ff){ ff->write((const char*)&c, sizeof c); }

char ReadChar(std::ifstream* ff)
{
    char c;
    ff->read((char*)&c, sizeof c);
    return c;
}

void WriteInt(int n, std::ofstream* ff)
{
    int r;
    char c;
    bool z = true;
    if (n < 0) {
        z = false;
        n = -n;
    }
    WriteBool(z, ff);
    for (int i = 0; i < 4; i++)
    {
        r = n % 256;
        if (r > 127)
            r -= 256;
        c = r;
        n /= 256;
        WriteChar(c, ff);
    }
}

int ReadInt(std::ifstream* ff)
{
    int r, n = 0;
    char c;
    bool z = ReadBool(ff);
    for (int i = 0; i < 4; i++)
    {
        c = ReadChar(ff);
        r = c;
        if (r < 0)
            r += 256;
        for (int j = 0; j < i; j++)
            r *= 256;
        n += r;
    }
    return z ? n : -n;
}

void GameController::read_level(){brd = create_new_board( 10, 10, 0 );}

void GameController::save_level(){
    std::ofstream ff(file_name(-level,true), std::ios::binary | std::ios::trunc | std::ios::out);
    WriteInt(brd->width,&ff);
    WriteInt(brd->height,&ff);
    WriteInt(brd->needed_coins,&ff);
    WriteInt(brd->keys.size(),&ff);
    WriteInt(brd->coins.size(),&ff);
    WriteInt(brd->dirts.size(),&ff);
    WriteInt(brd->boxes.size(),&ff);
    WriteInt(brd->players.size(),&ff);
    WriteInt(brd->opponents.size(),&ff);
    for( auto& it : brd->keys ){
        WriteInt(it->pos_x,&ff);
        WriteInt(it->pos_y,&ff);
        WriteInt(it->get_color(),&ff);
    }
    for( auto& it : brd->coins ){
        WriteInt(it->pos_x,&ff);
        WriteInt(it->pos_y,&ff);
        WriteInt(it->get_value(),&ff);
    }
    for( auto& it : brd->dirts ){
        WriteInt(it->pos_x,&ff);
        WriteInt(it->pos_y,&ff);
    }
    for( auto& it : brd->boxes ){
        WriteInt(it->pos_x,&ff);
        WriteInt(it->pos_y,&ff);
        WriteInt(it->weight_type(),&ff);
    }
    for( auto& it : brd->players ){
        WriteInt(it->pos_x,&ff);
        WriteInt(it->pos_y,&ff);
        WriteInt(it->weight,&ff);
        WriteInt(it->speed,&ff);
        WriteBool(it->digging,&ff);
        WriteBool(it->pushing,&ff);
    }
    for( auto& it : brd->opponents ){
        WriteInt(it->pos_x,&ff);
        WriteInt(it->pos_y,&ff);
        WriteInt(it->pos2_x,&ff);
        WriteInt(it->pos2_y,&ff);
        WriteInt(it->weight,&ff);
        WriteInt(it->speed,&ff);
    }
    for( int i = 0; i < brd->width; i++ ){
        for( int j = 0; j < brd->height; j++ ){
            WriteInt(brd->tiles[i][j]->get_type(),&ff);
            switch( brd->tiles[i][j]->get_type() ){
            case door:
                WriteInt(brd->tiles[i][j]->get_color(),&ff);
                break;
            case gate:
                WriteInt(brd->tiles[i][j]->get_btnx(),&ff);
                WriteInt(brd->tiles[i][j]->get_btny(),&ff);
                WriteBool(brd->tiles[i][j]->get_vert(),&ff);
                break;
            }
        }
    }
}
