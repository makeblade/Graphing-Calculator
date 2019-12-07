#ifndef REC_BUTTON_H
#define REC_BUTTON_H
#include "button.h"
#include "text_button.h"

class Rec_Button:public Button
{

public:
    Rec_Button(){}
    Rec_Button(sf::Vector2f size, sf::Vector2f pos, sf::Color old,
               sf::Color _new, int = -1, sf::Color outline = sf::Color::White,
               float thick = 2);
    void click();
    void unclick();
    void draw(sf::RenderWindow& window);
    void auto_check(float x, float y);
    void add_text_to_center(string, int size, sf::Font&, sf::Color, sf::Color);
    Text_Button& get_text();
    bool clicked();

private:
    sf::RectangleShape button;
    Text_Button text;
    bool have_text;
};

#endif // REC_BUTTON_H
