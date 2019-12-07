#include "button.h"

/**
 * @brief Button::Button constructor to intialize the button
 * @param size
 * @param pos
 * @param old
 * @param n
 */
Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Color old, sf::Color n)
{
    _pos = pos;
    _size = size;
    _original = old;
    _new = n;
}

/**
 * @brief Button::check_hover
 * @param x
 * @param y
 * @return if mouse is hovered over the button
 */
bool Button::check_hover(float x, float y)
{
    return (x >= _pos.x &&
            x <= (_pos.x + _size.x) &&
            y >= _pos.y &&
            y <= (_pos.y + _size.y));
}

/**
 * @brief Button::original
 * @return the original color
 */
sf::Color Button::original()
{
    return _original;
}

/**
 * @brief Button::get_new
 * @return  the color after hovered
 */
sf::Color Button::get_new()
{
    return _new;
}

/**
 * @brief Button::set_pos
 *  set the position of button
 * @param p
 */
void Button::set_pos(sf::Vector2f p)
{
    _pos = p;
}

void Button::set_size(sf::Vector2f s)
{
    _size = s;
}

/**
 * @brief Button::get_pos
 * @return position of button
 */
sf::Vector2f Button::get_pos()
{
    return _pos;
}

/**
 * @brief Button::get_size
 * @return size of button
 */
sf::Vector2f Button::get_size()
{
    return _size;
}

/**
 * @brief Button::set_original
 * @param c
 */
void Button::set_original(sf::Color c)
{
    _original = c;
}

/**
 * @brief Button::set_new
 * @param c
 */
void Button::set_new(sf::Color c)
{
    _new = c;
}
void Button::click(){}

void Button::unclick(){}

void Button::draw(sf::RenderWindow &window){}

