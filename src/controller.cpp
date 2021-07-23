#include "controller.hpp"

GameController::GameController( sf::Font* font ) : GRPH(), mms( font ), cls( font ), cles( font ), ps( font ), ts( font ), es( font, &GRPH ), cnvl( font ), sets( font ) {
    going = true;
    state = main_menu;
}

GameController::~GameController(){}

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
        case 1: return "editor/001.lvl";
        case 2: return "editor/002.lvl";
        case 3: return "editor/003.lvl";
        case 4: return "editor/004.lvl";
        case 5: return "editor/005.lvl";
        }
    }else{
        switch( i ){
        case 1: return "levels/001.lvl";
        case 2: return "levels/002.lvl";
        case 3: return "levels/003.lvl";
        case 4: return "levels/004.lvl";
        case 5: return "levels/005.lvl";
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

void GameController::read_level()
{
    std::vector <std::pair<std::pair<int,int>,Button*>> btptrs;
    bool oe = ( level < 0 );
    int oi = ( level < 0 ) ? -level : level;
    std::ifstream ff(file_name(oi,oe), std::ios::binary | std::ios::in);
    int nw, nh, nc, kl, cl, dl, bl, pl, ol, px, py, col, val, wght, spd, pn;
    bool dgg, psh;
    nw = ReadInt(&ff);
    nh = ReadInt(&ff);
    nc = ReadInt(&ff);
    brd = new Board( nw, nh, nc );
    kl = ReadInt(&ff);
    cl = ReadInt(&ff);
    dl = ReadInt(&ff);
    bl = ReadInt(&ff);
    pl = ReadInt(&ff);
    ol = ReadInt(&ff);
    for( int i = 0; i < kl; i++ ){
        px = ReadInt(&ff);
        py = ReadInt(&ff);
        col = ReadInt(&ff);
        Key* ktmpptr = new Key( (enum key_colors) col, px, py );
        brd->keys.push_back( ktmpptr );
    }
    for( int i = 0; i < cl; i++ ){
        px = ReadInt(&ff);
        py = ReadInt(&ff);
        val = ReadInt(&ff);
        Coin* ctmpptr = new Coin( val, px, py );
        brd->coins.push_back( ctmpptr );
    }
    for( int i = 0; i < dl; i++ ){
        px = ReadInt(&ff);
        py = ReadInt(&ff);
        Dirt* dtmpptr = new Dirt( px, py );
        brd->dirts.push_back( dtmpptr );
    }
    for( int i = 0; i < bl; i++ ){
        px = ReadInt(&ff);
        py = ReadInt(&ff);
        wght = ReadInt(&ff);
        Box* btmpptr = new Box( (enum weight_types) wght, px, py );
        brd->boxes.push_back( btmpptr );
    }
    for( int i = 0; i < pl; i++ ){
        px = ReadInt(&ff);
        py = ReadInt(&ff);
        wght = ReadInt(&ff);
        spd = ReadInt(&ff);
        dgg = ReadBool(&ff);
        psh = ReadBool(&ff);
        Player* ptmpptr = new Player( (enum weight_types) wght, (enum speed_types) spd, dgg, psh, 3, px, py );
        brd->players.push_back( ptmpptr );
    }
    for( int i = 0; i < ol; i++ ){
        wght = ReadInt(&ff);
        spd = ReadInt(&ff);
        pn = ReadInt(&ff);
        px = ReadInt(&ff);
        py = ReadInt(&ff);
        Opponent* otmpptr = new Opponent( (enum weight_types) wght, (enum speed_types) spd, px, py );
        for( int i = 1; i < pn; i++ ){
            px = ReadInt(&ff);
            py = ReadInt(&ff);
            otmpptr->add_position( px, py );
        }
        brd->opponents.push_back( otmpptr );
    }
    int tt, btx, bty;
    bool vrt;
    ButtonMultipleTimes* bmtptr;
    ButtonOneTime* botptr;
    for( int i = 0; i < brd->width; i++ ){
        for( int j = 0; j < brd->height; j++ ){
            tt = ReadInt(&ff);
            switch( tt ){
            case door:
                col = ReadInt(&ff);
                brd->tiles[i][j] = new Door( (enum key_colors) col );
                break;
            case gate:
                btx = ReadInt(&ff);
                bty = ReadInt(&ff);
                vrt = ReadBool(&ff);
                brd->tiles[i][j] = new Gate( vrt, nullptr, btx, bty );
                break;
            case exitt:
                brd->tiles[i][j] = new Exit();
                break;
            case grass:
                brd->tiles[i][j] = new Grass();
                break;
            case wall:
                brd->tiles[i][j] = new Wall();
                break;
            case button_multiple_times:
                bmtptr = new ButtonMultipleTimes();
                brd->tiles[i][j] = (Tile*) bmtptr;
                btptrs.push_back( std::pair<std::pair<int,int>,Button*>( std::pair<int,int>( i, j ), (Button*) bmtptr ) );
                break;
            case button_one_time:
                botptr = new ButtonOneTime();
                brd->tiles[i][j] = (Tile*) botptr;
                btptrs.push_back( std::pair<std::pair<int,int>,Button*>( std::pair<int,int>( i, j ), (Button*) botptr ) );
                break;
            }
        }
    }
    for( int i = 0; i < brd->width; i++ ){
        for( int j = 0; j < brd->height; j++ ){
            if( brd->tiles[i][j]->get_type() == gate ){
                vrt = brd->tiles[i][j]->get_vert();
                btx = brd->tiles[i][j]->get_btnx();
                bty = brd->tiles[i][j]->get_btny();
                for( unsigned int k = 0; k < btptrs.size(); k++ ){
                    if( btptrs[k].first.first == btx && btptrs[k].first.second == bty ){
                        delete brd->tiles[i][j];
                        brd->tiles[i][j] = new Gate( vrt, btptrs[k].second, btx, bty );
                        break;
                    }
                }
            }
        }
    }
    for( auto& it : brd->keys ) brd->tiles[it->pos_x][it->pos_y]->entity_ptr = (Entity*) it;
    for( auto& it : brd->coins ) brd->tiles[it->pos_x][it->pos_y]->entity_ptr = (Entity*) it;
    for( auto& it : brd->dirts ) brd->tiles[it->pos_x][it->pos_y]->entity_ptr = (Entity*) it;
    for( auto& it : brd->boxes ) brd->tiles[it->pos_x][it->pos_y]->entity_ptr = (Entity*) it;
    for( auto& it : brd->players ) brd->tiles[it->pos_x][it->pos_y]->entity_ptr = (Entity*) it;
    for( auto& it : brd->opponents ) brd->tiles[it->pos_x][it->pos_y]->entity_ptr = (Entity*) it;
    btptrs.clear();
}

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
        WriteInt(it->weight,&ff);
        WriteInt(it->speed,&ff);
        WriteInt(it->positions.size(),&ff);
        for( unsigned int i = 0; i < it->positions.size(); i++ ){
            WriteInt(it->positions[i].first,&ff);
            WriteInt(it->positions[i].second,&ff);
        }
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
