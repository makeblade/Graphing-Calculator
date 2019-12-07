#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H
#include "button.h"

class Text_Button:public Button
{

public:
    Text_Button(){}
    Text_Button(sf::Vector2f size, sf::Vector2f pos, sf::Color old,
               sf::Color _new, unsigned int font_size, sf::Font&, string str);
    void click();
    void unclick();
    void draw(sf::RenderWindow& window);
    bool clicked();
    void auto_check(float x, float y);
    string get_text();
    void set_text(string str);

private:
    sf::Text button;
};

#endif // TEXT_BUTTON_H
