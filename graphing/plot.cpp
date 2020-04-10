#include "plot.h"

/**
 * @brief plot::plot constructor
 * @param g
 */
plot::plot(graph_info* g)
{
    if(debug)cout << "creating plots.." << endl;
    _info = g;
    s = shuntingYard(g->_equation);
    _postfix = s.postFix();
}

/**
 * @brief plot::get_coords
 * @param type
 * @param equation
 * @return the converted coordinate with given equation and type of graph
 */
myvector<sf::Vector2f> plot::get_coords(int type, string equation)
{
    cords.clear();
    if(equation == "N/A")
        s.infix(_info->_equation);
    else
        s.infix(equation);
    rpn = RPN(s.postFix());
    float x;
    float y;
    float distance;
    float min = -_info->_x_min;
    float max = _info->_x_max;

    // check if it is polar or normal
    if(type == 1)
    {
        if(_info->_angle != 0.0) min*=2.f;
        for(float i=min;
            i<=max;
            i+=_info->_domain/_info->_points)
        {
            // use rpn to evalue the y
            x = i;
            y = rpn.evaluate(i);

            if(transform(x,y).x <= _info->_window_width)
                cords.push_back(transform(x,y));
            if(transform(x,y).x <= _info->_window_width &&
                    max < _info->_x_max*2)
                max += _info->_domain/_info->_points;
        }
    }
    else
    {
        // get the points of polar
        float max_degree = 360;
        for(float i=0; i<max_degree; i+=max_degree/_info->_points)
        {
            // covert them to polar points
            distance = rpn.evaluate(to_radian(i));
            x = distance*cos(to_radian(i));
            y = distance*sin(to_radian(i));
            if(transform(x,y).x <= _info->_window_width)
                cords.push_back(transform(x,y));

            if(transform(x,y).x <= _info->_window_width && max_degree <= 2000)
                max_degree += max_degree/_info->_points;
        }
    }
    _info->actual_points = cords.size();
    return cords;
}

/**
 * @brief plot::get_result
 * @return the result of solvable equation
 */
float plot::get_result()
{
    s.infix(_info->_equation);
    RPN rpn(s.postFix());
    return rpn.evaluate();
}

/**
 * @brief plot::to_radian
 * @param degree
 * @return covert given degree to radian
 */
float plot::to_radian(float degree)
{
    return (degree * static_cast<float>(M_PI))/180.f;
}

/**
 * @brief plot::transform
 * @param x
 * @param y
 * @return convert given x y to the screen coordinate
 */
sf::Vector2f plot::transform(float x, float y)
{
    float vectorX;
    float vectorY;

    // change the x and y acoording to the angle
    vectorX = x*dtof(cos(_info->_angle)) + y*dtof(sin(_info->_angle));
    vectorY = -x*dtof(sin(_info->_angle)) + y*dtof(cos(_info->_angle));
    vectorX=vectorX*(_info->_window_width/_info->_domain)+_info->_orgin.x;
    vectorY=vectorY*_info->_horizontal_zoom*
            (_info->_window_heigh/_info->_domain)-_info->_orgin.y;

    return sf::Vector2f(vectorX, -vectorY);

}

/**
 * @brief plot::dtof
 * @param d
 * @return convert given double to float
 */
float plot::dtof(double d)
{
    return static_cast<float>(d);
}
