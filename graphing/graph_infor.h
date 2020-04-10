#ifndef GRAPH_INFOR_H
#define GRAPH_INFOR_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include "constant.h"
#include <SFML/Window.hpp>
#include "../../../include/myvector.h"

struct graph_info
{
    string _equation = "tan(sin(x^2))";

    float _x_min = -(-10);
    float _x_max = 10;
    float _domain = _x_max+_x_min;
    float _window_width = 1250;
    float _window_heigh = 900;
    float _sidebar_width = 600;
    float _sidebar_height = _window_heigh;
    float _scale = 0;
    float _points = 10000;
    float _horizontal_zoom = 1;

    int actual_points = 10000;

    double _angle = 0;

    sf::Vector2f _orgin = sf::Vector2f(_window_width*(_x_min/_domain),_window_heigh/2);
    sf::Font font;
    sf::Font QuickSand_font;
    sf::Color bg_color = sf::Color(75, 71, 75);

    graph_info();
    bool constant();
    void save_data();
    void load_data();
};

#endif // GRAPH_INFOR_H
