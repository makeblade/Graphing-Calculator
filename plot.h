#ifndef PLOT_H
#define PLOT_H
#include "graph_infor.h"
#include "../../../include/myqueue.h"
#include "../../../include/myvector.h"
#include "../../../RPN/RPN/shunting_yard.h"

class plot
{
public:
    plot(){}
    plot(graph_info* g);

    float get_result();
    float dtof(double);

    myvector<sf::Vector2f> get_coords(int type = 1, string e = "N/A");
    sf::Vector2f transform(float x, float y);

private:
    graph_info* _info;
    Queue<Token*> _postfix;
    myvector<sf::Vector2f> cords;
    shuntingYard s;
    RPN rpn;
    float to_radian(float degree);
};

#endif // PLOT_H
