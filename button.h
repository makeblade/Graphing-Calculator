#ifndef BUTTON_H
#define BUTTON_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

class Button
{
public:

    virtual ~Button(){}
    Button(){}
    Button(sf::Vector2f size, sf::Vector2f pos, sf::Color old, sf::Color);

    bool check_hover(float x, float y);
    virtual void click();
    virtual void unclick();
    virtual void draw(sf::RenderWindow& window);
    virtual bool clicked(){return false;}
    sf::Color original();
    sf::Color get_new();
    void set_original(sf::Color);
    void set_new(sf::Color);
    void set_pos(sf::Vector2f);
    void set_size(sf::Vector2f);
    sf::Vector2f get_pos();
    sf::Vector2f get_size();

private:
    sf::Vector2f _pos;
    sf::Vector2f _size;
    sf::Color _original;
    sf::Color _new;
};

#endif // BUTTON_H
