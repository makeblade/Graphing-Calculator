#ifndef GRAPH_H
#define GRAPH_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "plot.h"

class Graph
{
public:
    Graph(){}
    Graph(graph_info* _info);

    float get_answer();

    int Random(int lo, int hi);
    int get_number_of_additionals();

    void draw(sf::RenderWindow& window, int type = 1);
    void delete_from_graphs(string equation);
    void add_to_graph(string);
    void clear_additional_graphs();
    void FillShapes(int type, sf::RectangleShape&);
    void update_property(sf::RenderWindow& window);

private:
    graph_info* _info;
    plot _plot;

    sf::RectangleShape singleRectangle;
    sf::RectangleShape x_axis;
    sf::RectangleShape y_axis;

    myvector<sf::Vector2f> cords;
    myvector<string> additional_graphs;

};

#endif // GRAPH_H
