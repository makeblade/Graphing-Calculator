#include "text_button.h"

/**
 * @brief Text_Button::Text_Button
 * @param bounce
 * @param pos
 * @param old
 * @param _new
 * @param fs        -       font size
 * @param font      -       font
 * @param str       -       string to initialize
 */
Text_Button::Text_Button(sf::Vector2f bounce, sf::Vector2f pos, sf::Color old,
                    sf::Color _new, unsigned int fs, sf::Font& font, string str)
    :Button (bounce, pos, old, _new)
{
    button.setFillColor(old);
    button.setFont(font);
    button.setCharacterSize(fs);
    button.setString(str);
    // put the text in middle of give range
    sf::Vector2f middle(get_pos().x + get_size().x/2 -
                 button.getString().getSize()*button.getCharacterSize()/4,
                 get_pos().y + get_size().y/2 - button.getCharacterSize()/2);
    button.setPosition(middle);
}

/**
 * @brief Text_Button::click
 */
void Text_Button::click()
{
    button.setFillColor(get_new());
}

/**
 * @brief Text_Button::unclick
 */
void Text_Button::unclick()
{
    button.setFillColor(original());
}

/**
 * @brief Text_Button::draw
 * @param window
 */
void Text_Button::draw(sf::RenderWindow &window)
{
    set_text(get_text());
    window.draw(button);
}

/**
 * @brief Text_Button::clicked
 * @return
 */
bool Text_Button::clicked()
{
    return button.getFillColor() == get_new();
}

/**
 * @brief Text_Button::auto_check
 *  automatically check if the button is hovered
 * @param x
 * @param y
 */
void Text_Button::auto_check(float x, float y)
{
    //  if hovered, change the color
    if(check_hover(x, y))
        click();
    else
        unclick();
}

/**
 * @brief Text_Button::get_text
 * @return text added
 */
string Text_Button::get_text()
{
    return button.getString();
}

/**
 * @brief Text_Button::set_text
 *  set the string of the text
 * @param str
 */
void Text_Button::set_text(string str)
{
    button.setString(str);
    // put the text in the middle of the given range
    sf::Vector2f middle(get_pos().x + get_size().x/2 -
                 button.getString().getSize()*button.getCharacterSize()/4,
                 get_pos().y + get_size().y/2 - button.getCharacterSize()/2);
    button.setPosition(middle);
}
