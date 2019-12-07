#include "graph.h"

/**
 * @brief Graph::Graph constructor
 * @param info
 */
Graph::Graph(graph_info* info)
{

    if(debug)cout << "creating graphs..." << endl;
    _info = info;

    // create plot to get points
    _plot = plot(_info);

    x_axis.setSize(sf::Vector2f(_info->_window_width, 1));
    FillShapes(10, x_axis);

    y_axis.setSize(sf::Vector2f(1, _info->_window_heigh));
    FillShapes(10, y_axis);

    singleRectangle.setSize(sf::Vector2f(1, 1));


}

/**
 * @brief Graph::draw
 *  draw all the object
 * @param window
 * @param type
 */
void Graph::draw(sf::RenderWindow &window, int type)
{
    // it is in polar, set it to have a even horizontal and vertical zoom
    if(type != 1) _info->_horizontal_zoom = 1.3;
    cords.clear();
    cords = _plot.get_coords(type);

    // draw the primary graph
    for(int i=0; i<cords.size(); i++)
    {
        singleRectangle.setPosition(cords.at(i));
        FillShapes(1, singleRectangle);
        window.draw(singleRectangle);
    }

    // if there are more graphs, just draw them
    float point_contain = _info->_points;
    if(additional_graphs.size() > 0)
        _info->_points = point_contain/additional_graphs.size();
    for(int i=0; i<additional_graphs.size(); i++)
    {
        FillShapes(i+2, singleRectangle);
        cords.clear();
        cords = _plot.get_coords(type, additional_graphs.at(i));
        for(int i=0; i<cords.size(); i++)
        {
            singleRectangle.setPosition(cords.at(i));
            window.draw(singleRectangle);
        }
    }
    _info->_points = point_contain;
}

/**
 * @brief Graph::FillShapes
 *  draw the given shapes with selected color
 * @param type
 * @param r
 */
void Graph::FillShapes(int type, sf::RectangleShape& r){

    switch (type) {
    case 1:
        r.setFillColor(sf::Color(173, 169, 239));
        break;
    case 2:
        r.setFillColor(sf::Color::Red);
        break;
    case 3:
        r.setFillColor(sf::Color::Green);
        break;
    case 4:
        r.setFillColor(sf::Color::Cyan);
        break;
    case 5:
        r.setFillColor(sf::Color::Magenta);
        break;
    case 6:
        r.setFillColor(sf::Color::Yellow);
        break;
    default:
        r.setFillColor(sf::Color::White);
    }

}

/**
 * @brief Graph::Random
 * @param lo
 * @param hi
 * @return random two number between given to gaps
 */
int Graph::Random(int lo, int hi)
{
    int r = rand()%(hi+1)+lo+1;
    return r;
}

/**
 * @brief Graph::update_property
 * @param window
 */
void Graph::update_property(sf::RenderWindow &window)
{
    // update axis according to shift
    x_axis.setPosition(sf::Vector2f(0, _info->_orgin.y));
    if(_info->_orgin.x <= _info->_window_width && _info->_orgin.x >= 0)
        y_axis.setPosition(sf::Vector2f(_info->_orgin.x, 0));

    window.draw(x_axis);
    if(_info->_orgin.x >= 0)
        window.draw(y_axis);

    // draw the number along the axis
    sf::Text t("", _info->font, 15);
    sf::RectangleShape r(sf::Vector2f(2,8));
    r.setFillColor(sf::Color::White);
    double i=-static_cast<int>(_info->_x_min);
    unsigned long deci = 0;
    double incre = 1;
    int max_unit = -1;

    // the the delta of those number acooding to it zoom
    if(_info->_domain >= 10){
        if(_info->_domain>=20)
            max_unit = static_cast<int>(_info->_domain/20);
    }
    else if(_info->_domain < 10 && _info->_domain >=3)
    {
        i-=0.5;
        deci = 2;
        incre = 0.5;
    }
    else if(_info->_domain < 3 && _info->_domain >=0)
    {
        i-=1.1;
        deci = 2;
        incre = 0.1;
    }
    else
    {
        i=-static_cast<double>(_info->_x_min);
        deci = 3;
        incre = 0.1;
    }
    // graph the number one by one with given delta and initail value
    for(; i<=static_cast<double>(_info->_x_max); i+=incre)
    {
        t.setPosition(static_cast<float>(i)*(_info->_window_width/_info->_domain)
                      +_info->_orgin.x,_info->_orgin.y);
        r.setPosition(static_cast<float>(i)*(_info->_window_width/_info->_domain)
                      +_info->_orgin.x,_info->_orgin.y-4);
        t.setString(to_string(i).substr(0,to_string(i).find('.')+deci));
        if(max_unit == -1)
        {
            window.draw(t);
            window.draw(r);
        }
        else if(static_cast<int>(i) % max_unit == 0)
        {
            window.draw(t);
            window.draw(r);
        }
    }
}

/**
 * @brief Graph::get_answer
 * @return the answer of equation if it is solvable
 */
float Graph::get_answer()
{
    return _plot.get_result();
}

/**
 * @brief Graph::delete_from_graphs
 * @param equation
 */
void Graph::delete_from_graphs(string equation)
{
    additional_graphs.erase(additional_graphs.index_of(equation));
}

/**
 * @brief Graph::get_number_of_additionals
 * @return
 */
int Graph::get_number_of_additionals()
{
    return additional_graphs.size();
}

/**
 * @brief Graph::add_to_graph
 * @param equation
 */
void Graph::add_to_graph(string equation)
{
    additional_graphs.push_back(equation);
}

/**
 * @brief Graph::clear_additional_graphs
 */
void Graph::clear_additional_graphs()
{
    additional_graphs.clear();
}
