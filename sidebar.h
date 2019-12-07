#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "graph_infor.h"
#include "button.h"
#include "rec_button.h"
#include "text_button.h"

const double BOX_WIDTH = 280;
const double BOX_HEIGHT = 35;

class sidebar
{

public:
    ~sidebar();
    sidebar(){}
    sidebar(graph_info* info);

    void draw(sf::RenderWindow& window);
    void update(int x, int y);
    void save_data();
    void read_history();
    void detect_box(float x, float y);
    string get_selected_equation();
    void fill_rec(sf::RectangleShape&, sf::Vector2f, sf::Vector2f,
                  sf::Color = sf::Color::White, sf::Color = sf::Color::White,
                  int=-1);
    void fill_text(sf::Text&, sf::Color, unsigned int, sf::Vector2f,
                   sf::Font&, string);
    void add_equation_to_list(string, int = 0);
    void update_equation_list();

private:
    int his_page;
    int equations_typed;
    int to_delete;
    graph_info* _info;

    sf::Text _cursor_pos;
    Text_Button _last_page;
    Text_Button _next_page;
    Text_Button _save;
    Text_Button _clear_history;
    Text_Button _mode;
    Rec_Button _save_setting;
    Rec_Button _multigraph;

    sf::RectangleShape _board;
    sf::RectangleShape _equation_buttons;       // Box contain bunch of buttons
    sf::RectangleShape _dividing_line;
    sf::RectangleShape _dividing_line2;
    sf::RectangleShape _dividing_line3;

    myvector<sf::Text> equation_list;
    myvector<Rec_Button> touch_boxes;
    myvector<Text_Button> delete_single;

};


#endif // SIDEBAR_H
