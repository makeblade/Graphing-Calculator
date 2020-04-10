#ifndef ANIME_H
#define ANIME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include "sidebar.h"
#include "graph.h"

class Anim{
public:
    Anim();
    void run();
    void processEvents();
    void update_page();
    void render();
    void update_graph_property();
private:
    sf::RenderWindow window;

    // Current Equation of the graph
    sf::RectangleShape equation_box;
    sf::Text current_equation;
    sf::Text _typing_equation;
    sf::Text _answer;
    sf::Text _graph_property;
    string current;
    bool typing;
    bool multigraph;
    int type;

    // Other part implementations
    graph_info* _info;
    sidebar sb;
    Graph graph;
    sf::Text cursor_pos;
    char letter_container;
    sf::Vector2f mouse_pos;
    sf::RectangleShape background;

};


#endif // ANIME_H
