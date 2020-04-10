#include "anime.h"


Anim::Anim(){

    window.setFramerateLimit(60);   // windows
    letter_container = '~';         // contain the letter that blocked by '_'
    _info = new graph_info();       // graph info pointer
    mouse_pos = sf::Vector2f(0,0);  //  mouse position holder

    if(debug)cout << "creating windows..." << endl;
    window.create(sf::VideoMode(
        static_cast<unsigned int>(_info->_window_width+_info->_sidebar_width),
        static_cast<unsigned int>(_info->_window_heigh)),
                  "GRAPHING CALCULATOR");

    // current equation contains the equation shown on the window
    current_equation.setFillColor(sf::Color(145,138,242));
    current_equation.setCharacterSize(27);
    current_equation.setPosition(_info->_window_width+20, 50);
    current_equation.setString("F(x) = " + _info->_equation);
    current_equation.setFont(_info->font);
    current = "tan(sin(x^2))";

    // answer contains the result calculated fron current equation
    _answer.setFillColor((sf::Color(145,138,242)));
    _answer.setCharacterSize(20);
    _answer.setPosition(_info->_window_width+_info->_sidebar_width-200, 80);
    _answer.setFont(_info->font);
    _answer.setString("= N/A");

    // equation box contain the used typing equation, appear when press enter
    equation_box.setSize(sf::Vector2f(_info->_window_width-20, 100));
    equation_box.setPosition(10, 10);
    equation_box.setFillColor(sf::Color::Black);
    equation_box.setOutlineColor(sf::Color::Yellow);
    equation_box.setOutlineThickness(3);

    // typing equation is the text shows what user is typing
    _typing_equation.setFillColor(sf::Color::White);
    _typing_equation.setCharacterSize(30);
    _typing_equation.setPosition(20, 40);
    _typing_equation.setString("F(x) = " + _info->_equation);
    _typing_equation.setFont(_info->QuickSand_font);

    // create a backgroud rectange in order to change background color manually
    background.setFillColor(_info->bg_color);
    background.setSize(sf::Vector2f(_info->_window_width+_info->_sidebar_width,
                                    _info->_window_heigh));

    // iniailize sidebar, graph
    sb = sidebar(_info);
    graph = Graph(_info);
    typing = false;         // if user is typing
    multigraph = false;     // if is in mutigraph mode
    type = 1;               // normal mode or polar mode

    // call sidebar's equation to initialize graph property
    sb.fill_text(_graph_property, sf::Color::White, 20,
                      sf::Vector2f(0,0), _info->QuickSand_font, "");

    if(debug)cout << "All preparation are ready!" << endl;

}

/**
 * @brief Anim::update_page
 *  draws all of the object
 */
void Anim::update_page()
{
    window.draw(background);
    // update the cuurent text if it is in typing mode
    if(typing)
        _typing_equation.setString("F(x) = " + current);
    graph.update_property(window);


    sb.draw(window);
    graph.draw(window, type);
    window.draw(current_equation);
    window.draw(_answer);

    // draw the box if is in typing mode
    if(typing)
    {
        window.draw(equation_box);
        window.draw(_typing_equation);
    }

    update_graph_property();
}

/**
 * @brief Anim::render
 *  render the page
 */
void Anim::render()
{
   window.clear();
   update_page();
   window.display();
}

/**
 * @brief Anim::run
 */
void Anim::run()
{
   while (window.isOpen())
   {
       processEvents();
       render();
   }
}

/**
 * @brief Anim::processEvents
 *  handle all the event within this window
 */
void Anim::processEvents()
{
    // how much should be shifted
    float shift_factor = _info->_domain/_info->_window_width*5.f;
    // how much should be zoomed
    float zoom_factor = _info->_domain/_info->_window_width*10.f;
    // index of '_' in current text if in typing mode
    unsigned long index = static_cast<unsigned long>(current.find("_"));
    string selected_button = "";
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {

            // window closed
            // "close requested" event: we close the window
            case sf::Event::Closed:
                window.close();
                break;

            // key pressed
            case sf::Event::KeyPressed:
            if(!typing){
                // zoom in or out
                if(event.key.code == sf::Keyboard::Z)
                {
                    _info->_x_min-=shift_factor;
                    _info->_x_max-=shift_factor;
                    if(_info->_orgin.y < _info->_window_heigh/2)
                    {
                        _info->_orgin.y -= zoom_factor/3.0f*
                                _info->_window_width/_info->_domain;
                    }
                    else if(_info->_orgin.y > _info->_window_heigh/2)
                    {
                        _info->_orgin.y += zoom_factor/3.0f*
                                _info->_window_width/_info->_domain;
                    }
                }
                else if(event.key.code == sf::Keyboard::X)
                {
                    _info->_x_min+=shift_factor;
                    _info->_x_max+=shift_factor;
                    if(_info->_orgin.y < _info->_window_heigh/2)
                    {
                        _info->_orgin.y += zoom_factor/3.0f*_info->_window_width
                                /_info->_domain;
                        // the y aixs if needed
                        if(_info->_orgin.y >= _info->_window_heigh/2)
                            _info->_orgin.y = _info->_window_heigh/2;
                    }
                    else if(_info->_orgin.y > _info->_window_heigh/2)
                    {
                        _info->_orgin.y -= zoom_factor/3.0f*_info->_window_width
                                /_info->_domain;
                        if(_info->_orgin.y <= _info->_window_heigh/2)
                            _info->_orgin.y = _info->_window_heigh/2;
                    }
                }
                // shift left or right
                else if(event.key.code == 71)
                {
                    _info->_x_min+=zoom_factor;
                    _info->_x_max-=zoom_factor;
                }
                else if(event.key.code == 72)
                {
                    _info->_x_min-=zoom_factor;
                    _info->_x_max+=zoom_factor;
                }
                // shift up or down
                else if(event.key.code == 73)
                    _info->_orgin.y += 10.f;
                else if(event.key.code == 74)
                    _info->_orgin.y -= 10.f;
                // reset the graph to its default position
                else if(event.key.code == 57)
                {
                    _info->_x_min = 10.f;
                    _info->_x_max = 10.f;
                    _info->_orgin.x = _info->_window_width/2;
                    _info->_orgin.y = _info->_window_heigh/2;
                    _info->_angle = 0;
                }
                // horizontally zoom in or out
                else if(event.key.code == 2)
                    _info->_horizontal_zoom += zoom_factor;
                else if(event.key.code == 21)
                    _info->_horizontal_zoom -= zoom_factor;
                // rotate graph clockwise or counterclockwise
                else if(event.key.code == sf::Keyboard::A)
                {
                    _info->_angle+=M_PI/12;
                    if(_info->_angle >= 2*M_PI-M_PI/12) _info->_angle = 0;
                }
                else if(event.key.code == sf::Keyboard::S)
                {
                    _info->_angle-=M_PI/12;
                    if(_info->_angle <= M_PI/12) _info->_angle = 2*M_PI;
                }
                _info->_domain = _info->_x_max + _info->_x_min;
                _info->_orgin.x = _info->_window_width*(_info->_x_min/
                                                        _info->_domain);
            }
            else
            {
                // if it is in typing mode, left and right arror will move the
                //  position of '_' in current text
                if(event.key.code == 71)
                {
                    if(index != 0)
                    {
                        if(index == current.size()-1)
                            current.replace(index, 1, string(1, ' '));
                        else
                            current.replace(index,1,string(1,letter_container));
                        letter_container = current.at(index-1);
                        current.replace(index-1, 1, string(1, '_'));
                    }

                }
                else if(event.key.code == 72)
                {
                    if(index != current.size()-1)
                    {
                        current.replace(index, 1, string(1, letter_container));
                        letter_container = current.at(index+1);
                        current.replace(index+1, 1, string(1, '_'));
                    }
                }
            }
                break;
        case sf::Event::MouseButtonReleased:
            // if mouse is clicked, call the get selection equation from sb
            //  to know what is clicked and graph acoordingly
            selected_button = sb.get_selected_equation();
            if(selected_button == "mode")
                type == 1?type = 2:type = 1;
            else if(selected_button.substr(0, 6) == "delete")
                graph.delete_from_graphs(selected_button.substr(7, selected_button.size()-7));
            else if(selected_button == "graph")
            {
                multigraph?multigraph=false:multigraph=true;
                if(!multigraph)
                    graph.clear_additional_graphs();
            }
            else if(selected_button != "empty")
            {
                // if is mutigraph, add mutiple graph
                if(multigraph)
                {
                    graph.add_to_graph(selected_button);
                    break;
                }
                _info->_equation = selected_button;
                current = _info->_equation + "_";
                current_equation.setString("F(x) = " + _info->_equation);
            }
            break;
        case sf::Event::MouseMoved:
            // update the mouse position shown
            sb.update(event.mouseMove.x, event.mouseMove.y);
            // update the box if they are getting hovered
            sb.detect_box(event.mouseMove.x, event.mouseMove.y);
            mouse_pos.x = event.mouseMove.x;
            mouse_pos.y = event.mouseMove.y;
            break;
        case sf::Event::TextEntered:
            if(event.text.unicode == 13)
            {
                // if user is typing
                if(typing)
                {
                    // remove the '_' from equation
                    if(index == current.size()-1) current.pop_back();
                    else current.replace(index, 1, string(1, letter_container));

                    // remove spaces
                    if(current.find(" ") != string::npos)
                        current.erase(current.find(" "), 1);

                    // change the equation shown
                    _info->_equation = current;
                    _typing_equation.setString("F(x) = " + _info->_equation);
                    current_equation.setString("F(x) = " + _info->_equation);

                    // if given equation is solvable, show the answer
                    if(_info->constant())
                        _answer.setString("= " +
                                    to_string(graph.get_answer()).substr(0,
                                    to_string(graph.get_answer()).find('.')+3));
                    else
                        _answer.setString("= N/A");
                    sb.add_equation_to_list(_info->_equation, 1);
                }
                else if(current.at(current.size()-1) != '_')
                    current += "_";
                typing ? typing = false:typing = true;
            }
            else if(event.text.unicode == 8 && typing)
            {
                // delete a character if user is typing acoording to '_'
                if(current.size() > 1)
                {
                    if(index == current.size()-1)
                        current.erase(current.size()-2, 1);
                    else
                    {
                        letter_container = current.at(index +1);
                        current.replace(index+1, 1, "_");
                        current.erase(index, 1);
                    }
                }
            }
            else if(typing)
            {
                // input a character according to '_'
                char input = static_cast<char>(event.text.unicode);
                if(index == current.size()-1)
                {
                    current.pop_back();
                    current += input;
                    current += "_";
                }
                else
                {
                    current.replace(index, 1, string(1, input));
                    letter_container = current.at(index +1);
                    current.replace(index+1, 1, "_");
                }
            }

            break;
        // zoom in or out acoording the mouse wheeler
        case sf::Event::MouseWheelMoved:
            shift_factor *= 5;
            zoom_factor *= 5;
            if(event.mouseWheel.delta > 0)
            {
                _info->_x_min-=shift_factor;
                _info->_x_max-=shift_factor;
                if(_info->_orgin.y < _info->_window_heigh/2)
                {
                    _info->_orgin.y -= zoom_factor/1.5f*
                            _info->_window_width/_info->_domain;
                }
                else if(_info->_orgin.y > _info->_window_heigh/2)
                {
                    _info->_orgin.y += zoom_factor/1.5f*
                            _info->_window_width/_info->_domain;
                }
            }
            else if(event.mouseWheel.delta < 0)
            {
                _info->_x_min+=shift_factor;
                _info->_x_max+=shift_factor;
                if(_info->_orgin.y < _info->_window_heigh/2)
                {
                    _info->_orgin.y += zoom_factor/1.5f*_info->_window_width
                            /_info->_domain;
                    if(_info->_orgin.y >= _info->_window_heigh/2)
                        _info->_orgin.y = _info->_window_heigh/2;
                }
                else if(_info->_orgin.y > _info->_window_heigh/2)
                {
                    _info->_orgin.y -= zoom_factor/1.5f*_info->_window_width
                            /_info->_domain;
                    if(_info->_orgin.y <= _info->_window_heigh/2)
                        _info->_orgin.y = _info->_window_heigh/2;
                }
            }
            _info->_domain = _info->_x_max + _info->_x_min;
            _info->_orgin.x = _info->_window_width*(_info->_x_min/
                                                    _info->_domain);
            break;
            default:
                break;
        }
    }
}

/**
 * @brief Anim::update_graph_property
 *  update the angle, doman, and density on the screen
 */
void Anim::update_graph_property()
{

    _graph_property.setPosition(_info->_window_width-160,
                                _info->_window_heigh-80);
    _graph_property.setString("Angle    : " +
                              to_string(_info->_angle*(180/M_PI)).
                              substr(0,to_string(_info->_angle*(180/M_PI)).
                                     find('.')+2));
    window.draw(_graph_property);

    _graph_property.setPosition(_info->_window_width-160,
                                _info->_window_heigh-60);
    _graph_property.setString("Domain : " +
                              to_string(_info->_domain).
                              substr(0,to_string(_info->_domain).
                                     find('.')+4));
    window.draw(_graph_property);

    _graph_property.setPosition(_info->_window_width-160,
                                _info->_window_heigh-40);
    _graph_property.setString("Density : " + to_string(_info->actual_points));
    window.draw(_graph_property);


    _graph_property.setPosition(0,_info->_window_heigh-22);
    _graph_property.setString("@Shawn Zhang");
    window.draw(_graph_property);

}
