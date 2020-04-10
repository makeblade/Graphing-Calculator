#include "rec_button.h"

/**
 * @brief Rec_Button::Rec_Button constructor
 * @param size
 * @param pos
 * @param old
 * @param _new
 * @param choice    - to have outline or not
 * @param outline
 * @param thi
 */
Rec_Button::Rec_Button(sf::Vector2f size, sf::Vector2f pos, sf::Color old,
                       sf::Color _new, int choice, sf::Color outline, float thi)
    :Button (size, pos, old, _new)
{
    have_text = false;
    button.setFillColor(old);
    if(choice != -1)
    {
        button.setOutlineColor(outline);
        button.setOutlineThickness(thi);
    }
}

/**
 * @brief Rec_Button::auto_check
 *  auto checks if the button is hovered or not
 * @param x
 * @param y
 */
void Rec_Button::auto_check(float x, float y)
{
    // if it is hovered, change its color
    if(check_hover(x, y))
        click();
    else
        unclick();
    if(have_text)
        text.auto_check(x, y);
}

/**
 * @brief Rec_Button::click
 */
void Rec_Button::click()
{
    button.setFillColor(get_new());
}

/**
 * @brief Rec_Button::unclick
 */
void Rec_Button::unclick()
{
    button.setFillColor(original());
}

/**
 * @brief Rec_Button::draw
 * @param window
 */
void Rec_Button::draw(sf::RenderWindow &window)
{
    button.setSize(get_size());
    button.setPosition(get_pos());
    window.draw(button);
    if(have_text)
        text.draw(window);
}

/**
 * @brief Rec_Button::clicked
 * @return  check if the button is hovered or not
 */
bool Rec_Button::clicked()
{
    if(have_text)
        return button.getFillColor() == get_new() && text.clicked();
    else
        return button.getFillColor() == get_new();
}

/**
 * @brief Rec_Button::add_text_to_center
 *  add a text to the center of the button
 * @param str
 * @param size
 * @param font
 * @param c
 * @param c_new
 */
void Rec_Button::add_text_to_center(string str, int size, sf::Font& font,
                                    sf::Color c, sf::Color c_new)
{
    text = Text_Button(get_size(), get_pos(), c, c_new, size, font,
                       str);
    have_text = true;
}

/**
 * @brief Rec_Button::get_text
 * @return the text added
 */
Text_Button& Rec_Button::get_text()
{
    return text;
}
