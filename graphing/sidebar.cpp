#include "sidebar.h"

/**
 * @brief sidebar::~sidebar
 */
sidebar::~sidebar()
{
    // save data before delete
    save_data();
}

/**
 * @brief sidebar::sidebar constructor
 * @param info
 */
sidebar::sidebar(graph_info* info)
    :his_page(1), equations_typed(1), to_delete(-1),  _info(info)
{
    if(debug)cout << "creating sidebars..." << endl;

    // create a side bar rectange and lines
    fill_rec(_board,sf::Vector2f(_info->_sidebar_width, _info->_sidebar_height),
             sf::Vector2f(info->_window_width, 0), _info->bg_color,
             sf::Color::White, 2);
    fill_rec(_equation_buttons, sf::Vector2f(_info->_sidebar_width, 70),
             sf::Vector2f(_info->_window_width, 220), sf::Color::Black,
             sf::Color::White, 2);
    fill_rec(_dividing_line,
             sf::Vector2f(2, _info->_window_heigh-
                          _equation_buttons.getPosition().y),
             sf::Vector2f(_info->_window_width+_info->_sidebar_width/2,
                          _equation_buttons.getPosition().y));
    fill_rec(_dividing_line2,
             sf::Vector2f(_equation_buttons.getSize().x, 2),
             sf::Vector2f(_info->_window_width,
                          _equation_buttons.getPosition().y+
                          _equation_buttons.getSize().y/2));
    fill_rec(_dividing_line3,
             sf::Vector2f(2, _equation_buttons.getSize().y/2),
             sf::Vector2f(_info->_window_width+_equation_buttons.getSize().x*3/4
                         ,_equation_buttons.getPosition().y+
                          _equation_buttons.getSize().y/2));

    // create text where it shows the answer
    fill_text(_cursor_pos, sf::Color::White, 17,
              sf::Vector2f(_info->_window_width,0), _info->font, "N/A");

    // create all the buttons and set their attributes
    _last_page = Text_Button(
                sf::Vector2f(_equation_buttons.getSize().x/4,
                             _equation_buttons.getSize().y/2),
                sf::Vector2f(_dividing_line.getPosition().x,
                             _dividing_line2.getPosition().y),
                sf::Color::White, sf::Color(253, 250, 162), 35,_info->font,"<<");
    _next_page = Text_Button(_last_page.get_size(),
                sf::Vector2f(_dividing_line3.getPosition().x,
                             _dividing_line2.getPosition().y),
                sf::Color::White, sf::Color(253, 250, 162), 35,_info->font,">>");
    _save = Text_Button(
                sf::Vector2f(_equation_buttons.getSize().x/2,
                             _equation_buttons.getSize().y/2),
                sf::Vector2f(_info->_window_width,
                             _equation_buttons.getPosition().y),
                sf::Color::White, sf::Color(253, 250, 162), 25, _info->font, "Save");
    _clear_history = Text_Button(_save.get_size(),
                 sf::Vector2f(_dividing_line.getPosition().x,
                              _equation_buttons.getPosition().y),
                 sf::Color::White, sf::Color(253, 250, 162), 25, _info->font,
                 "Clear Hishtory");
    _mode = Text_Button(_save.get_size(),
                sf::Vector2f(_info->_window_width,
                             _dividing_line2.getPosition().y),
                sf::Color::White, sf::Color(253, 250, 162), 25, _info->font,
                "Polar");
    _save_setting = Rec_Button(sf::Vector2f(_info->_sidebar_width/2, 30),
                               sf::Vector2f(_info->_window_width, _equation_buttons.getPosition().y-29),
                               sf::Color::Black, sf::Color(253, 250, 162),
                               2, sf::Color::White);
    _save_setting.add_text_to_center("Save Setting", 25, _info->font,
                                        sf::Color::White, sf::Color(253, 250, 162));
    _save_setting.set_new(sf::Color::Black);


    _multigraph = Rec_Button(sf::Vector2f(_info->_sidebar_width/2, 30),
                               sf::Vector2f(_info->_window_width+_info->_sidebar_width/2, _equation_buttons.getPosition().y-29),
                               sf::Color::Black, sf::Color(253, 250, 162),
                               2, sf::Color::White);
    _multigraph.add_text_to_center("Enable Multigraph", 25, _info->font,
                                        sf::Color::White, sf::Color(253, 250, 162));
    _multigraph.set_new(sf::Color::Black);

    // load from file
    read_history();

    // add a default equation
    add_equation_to_list(_info->_equation);
}

/**
 * @brief sidebar::draw all the object
 * @param window
 */
void sidebar::draw(sf::RenderWindow& window)
{
    // update page number shwon on the screen
    _clear_history.set_text("Clear History (" +
                            to_string(his_page) + "/" +
                            to_string((equation_list.size()-equations_typed)/15
                                      +1) + ")");
    int box_gap = 40;
    window.draw(_board);
    window.draw(_cursor_pos);
    window.draw(_equation_buttons);
    window.draw(_dividing_line);
    window.draw(_dividing_line2);
    window.draw(_dividing_line3);

    // draw all the buttons
    _save.draw(window);
    _clear_history.draw(window);
    _next_page.draw(window);
    _last_page.draw(window);
    _mode.draw(window);
    _save_setting.draw(window);
    _multigraph.draw(window);

    // display all the equation in the history panel
    for(int i=(his_page-1)*15; i<his_page*15 &&
        i<equation_list.size()-equations_typed; i++)
    {
        // display the box
        touch_boxes.at(i).set_pos(
                    sf::Vector2f(_info->_window_width+(_info->_sidebar_width/2+10),
                                    _info->_window_heigh/3+((i-(his_page-1)*15)*
                                                            box_gap)));
        // display text
        equation_list.at(i).setPosition(touch_boxes.at(i).get_pos().x+5,
                                    _info->_window_heigh/3+((i-(his_page-1)*15)*
                                                            box_gap));
        // display delete sign
        delete_single.at(i).set_pos(sf::Vector2f(
                    _info->_window_width+_info->_sidebar_width-40,
                    _info->_window_heigh/3+((i-(his_page-1)*15)*box_gap)));
        touch_boxes.at(i).draw(window);
        window.draw(equation_list.at(i));

        // if is in mutigraph mode, change equation color if it is being drawn
        if(_multigraph.get_text().get_text() != "Disable Multigraph" &&
                equation_list.at(i).getString() != _info->_equation)
            equation_list.at(i).setFillColor(sf::Color::Black);
        else if(equation_list.at(i).getString() == _info->_equation)
            equation_list.at(i).setFillColor(sf::Color(183,179,42));
    }
    // display all the equation in the temperory saving panel
    for(int i=equation_list.size()-equations_typed;
        i<equation_list.size(); i++)
    {
        touch_boxes.at(i).set_pos(sf::Vector2f(
                    _info->_window_width+10,
                    _info->_window_heigh/3+
                    ((i-(equation_list.size()-equations_typed))*box_gap)));
        equation_list.at(i).setPosition(
                    touch_boxes.at(i).get_pos().x+5,
                    _info->_window_heigh/3+
                    ((i-(equation_list.size()-equations_typed))*box_gap));
        delete_single.at(i).set_pos(sf::Vector2f(
                    _info->_window_width+(_info->_sidebar_width/2-40),
                    _info->_window_heigh/3+
                    ((i-(equation_list.size()-equations_typed))*box_gap)));
        touch_boxes.at(i).draw(window);
        window.draw(equation_list.at(i));

        // if is in mutigraph mode, change equation color if it is being drawn
        if(_multigraph.get_text().get_text() != "Disable Multigraph" &&
                equation_list.at(i).getString() != _info->_equation)
            equation_list.at(i).setFillColor(sf::Color::Black);
        else if(equation_list.at(i).getString() == _info->_equation)
            equation_list.at(i).setFillColor(sf::Color(183,179,42));
    }

    // if the delete sign is clicked, delte the found equation
    if(to_delete != -1)
        if(touch_boxes.at(to_delete).clicked())
            delete_single.at(to_delete).draw(window);
}

/**
 * @brief sidebar::update the mouse position shown on the screen
 * @param x
 * @param y
 */
void sidebar::update(int x, int y)
{
    _cursor_pos.setString("x: " + to_string(x) + ",   " +
                          "y: " + to_string(y));
}

/**
 * @brief sidebar::read_history
 *  read from history file while backup the read content
 */
void sidebar::read_history()
{
    ifstream read;
    ofstream write;
    string temp;

    read.open("../Data/History.txt");
    write.open("../Data/Backup.txt");
    if(!read || !write)
    {
        cout << "Fail to load from History/backup file \nline: 107 sidebar.h";
        cin.get();
        exit(-1);
    }
    while(!read.eof()) {
        getline(read, temp);
        if(temp!= "")
        {
            add_equation_to_list(temp);
            write << temp << endl;
        }
    }
    read.close();
    write.close();
}

/**
 * @brief sidebar::save_data save the equations to a file
 */
void sidebar::save_data()
{
    ofstream write;
    string temp;
    int i = 0;

    write.open("../Data/History.txt");
    if(!write)
    {
        cout << "Fail to load from History file \nline: 59 sidebar.h";
        cin.get();
        exit(-1);
    }
    if(equation_list.size() == 0) return;

    for(i=0; i<equation_list.size()-equations_typed-1; i++)
    {
        temp = equation_list.at(i).getString();
        if(temp != "")
            write << temp  << endl;
    }
    temp = equation_list.at(i).getString();
    if(temp != "")
        write << temp;
    write.close();

}

/**
 * @brief sidebar::detect_box
 *  check which box is hovered and do the animation
 * @param x
 * @param y
 */
void sidebar::detect_box(float x, float y)
{
    bool i_incremented = false;

    // which box in the history or temporary saving panel is hovered
    for(int i=(his_page-1)*15; i<equation_list.size(); i++)
    {
        if(i >= his_page*15 && equations_typed != 0 && !i_incremented)
        {
            i = equation_list.size()-equations_typed;
            i_incremented = true;
        }
        else if(i >= his_page*15 && !i_incremented) break;
        if(touch_boxes.at(i).check_hover(x, y))
        {
            touch_boxes.at(i).click();
            to_delete = i;
            delete_single.at(to_delete).auto_check(x, y);
        }
        else
        {
            touch_boxes.at(i).unclick();
        }
    }

    // call the auto check for all buttons
    _last_page.auto_check(x, y);
    _next_page.auto_check(x, y);
    _save.auto_check(x, y);
    _clear_history.auto_check(x, y);
    _mode.auto_check(x, y);
    _save_setting.auto_check(x,y);
    _multigraph.auto_check(x, y);

}

/**
 * @brief sidebar::get_selected_equation
 * @return which equation is being clicked
 */
string sidebar::get_selected_equation()
{
    // check which equation in the list is clicked
    for(int i=0; i<touch_boxes.size(); i++)
    {
        if(touch_boxes.at(i).clicked())
        {
            // if the deleted sign is clicked
            if(to_delete != -1 &&
                delete_single.at(to_delete).clicked())
            {
                equation_list.at(to_delete).setString("");
                to_delete = -1;
                update_equation_list();
            }else if(equation_list.at(i).getFillColor() != sf::Color(183,179,42))
            {
                equation_list.at(i).setFillColor(sf::Color(183,179,42));
                return equation_list.at(i).getString();
            }else{
                if(equation_list.at(i).getString() != _info->_equation)
                {
                    equation_list.at(i).setFillColor(sf::Color::Black);
                    return "delete " + equation_list.at(i).getString();
                }
                return "empty";
            }
        }
    }
    if(_last_page.clicked() && his_page > 1)
        his_page -= 1;
    else if(_next_page.clicked() && his_page*15 < equation_list.size()-
            equations_typed)
    {
        his_page += 1;
    }
    else if(_save.clicked())
        equations_typed = 0;
    else if(_clear_history.clicked())
    {
        for(int i=(his_page-1)*15;
            i<equation_list.size()-equations_typed; i++)
            equation_list.at(i).setString("");
        update_equation_list();
        to_delete = -1;
    }
    else if(_mode.clicked())
    {
        _mode.get_text()=="Polar" ?
                    _mode.set_text("Normal"):_mode.set_text("Polar");
        return "mode";
    }
    else if(_save_setting.clicked())
    {
        _info->save_data();
    }
    if(_multigraph.clicked())
    {
        _multigraph.get_text().get_text()=="Enable Multigraph"?
                    _multigraph.get_text().set_text("Disable Multigraph"):
                    _multigraph.get_text().set_text("Enable Multigraph");
        return "graph";
    }

    return "empty";
}

/**
 * @brief sidebar::fill_rec
 *  initialize the given rectange with given attributes
 * @param rec
 * @param size
 * @param loc
 * @param fill_c
 * @param out_c
 * @param out_thi
 */
void sidebar::fill_rec(sf::RectangleShape& rec, sf::Vector2f size,
                       sf::Vector2f loc, sf::Color fill_c, sf::Color out_c,
                       int out_thi)
{
    rec.setSize(size);
    rec.setPosition(loc);
    rec.setFillColor(fill_c);
    if(out_thi != -1)
    {
        rec.setOutlineColor(out_c);
        rec.setOutlineThickness(out_thi);
    }
}

/**
 * @brief sidebar::fill_text
 *  initialize given text with give attributes
 * @param text1
 * @param color
 * @param size
 * @param pos
 * @param font
 * @param str
 */
void sidebar::fill_text(sf::Text& text1, sf::Color color, unsigned int size,
                        sf::Vector2f pos,sf::Font& font, string str)
{
    text1.setFillColor(color);
    text1.setCharacterSize(size);
    text1.setPosition(pos);
    text1.setFont(font);
    text1.setString(str);
}

/**
 * @brief sidebar::add_equation_to_list
 *  add equation to the list shown in the panel
 * @param str
 * @param typed
 */
void sidebar::add_equation_to_list(string str, int typed)
{
    equations_typed += typed;
    sf::Text t;
    // create two buttons and added them
    Text_Button d(sf::Vector2f(30, BOX_HEIGHT), sf::Vector2f(0,0),
                  sf::Color::Black, sf::Color::Red, 24, _info->QuickSand_font, "X");
    Rec_Button but(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT), sf::Vector2f(0,0),
                   sf::Color(225,231,249), sf::Color(253, 250, 162));

    fill_text(t, sf::Color::Black, 24, sf::Vector2f(0,0), _info->QuickSand_font, str);

    equation_list.push_back(t);
    touch_boxes.push_back(but);
    delete_single.push_back(d);
}

/**
 * @brief sidebar::update_equation_list
 *  update the list, remove the equation that is deleted
 */
void sidebar::update_equation_list()
{
    myvector<sf::Text> result(equation_list);
    myvector<Rec_Button> result2(touch_boxes);
    touch_boxes.clear();
    equation_list.clear();

    for(int i=0; i<result.size(); i++)
    {
        if(result.at(i).getString() != "")
        {
            equation_list.push_back(result.at(i));
            touch_boxes.push_back(result2.at(i));
        }
        else if(i >= result.size()-equations_typed)
            equations_typed--;
    }
}
