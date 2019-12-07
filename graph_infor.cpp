#include "graph_infor.h"

/**
 * @brief graph_info::constant
 * @return if current equation is solvable
 */
bool graph_info::constant()
{
    return _equation.find('x') == string::npos;
}

/**
 * @brief graph_info::graph_info constructor
 */
graph_info::graph_info()
{
    load_data();
    if(debug)cout << "reading ttf file..." << endl;

    // load fonts
    if(!font.loadFromFile("../Font/PlayfairDisplay-Black.otf"))
    {
        cout << "fail to load playfairdisplay-black file at line 43, anime.h";
        cout << endl;
        cin.get();
        exit(-1);
    }
    if(!QuickSand_font.loadFromFile("../Share_Font/Share-Tech.otf"))
    {
        cout << "fail to load playfairdisplay-black file at line 43, anime.h";
        cout << endl;
        cin.get();
        exit(-1);
    }
}

/**
 * @brief graph_info::save_data
 *  save all current setting
 */
void graph_info::save_data()
{
    ofstream write("../Data/Setting.txt");
    if(!write)
    {
        cout << "Fail to load from Setting file \nline: 49 graph_infor.h";
        cin.get();
        exit(-1);
    }

    write << _x_min << endl << _x_max << endl << _domain << endl << _equation
          << endl << _window_width << endl << _window_heigh << endl
          << _sidebar_width << endl << _sidebar_height << endl << _scale
          << endl << _angle << endl << _points << endl << actual_points
          << _horizontal_zoom << endl;
    write.close();
}

/**
 * @brief graph_info::load_data
 *  load the last saved data
 */
void graph_info::load_data()
{
    ifstream read("../Data/Setting.txt");
    if(!read)
    {
        cout << "Fail to load from Setting file \nline: 67 graph_infor.h";
        cin.get();
        exit(-1);
    }
    read >> _x_min >> _x_max >> _domain >> _equation
          >> _window_width >> _window_heigh
          >> _sidebar_width >> _sidebar_height >> _scale
          >> _angle >> _points >> actual_points
          >> _horizontal_zoom;

    _orgin = sf::Vector2f(_window_width*(_x_min/_domain),_window_heigh/2);
    read.close();
}
