#pragma once

#include <SFML/Graphics.hpp>

class Menu
{
public:
    Menu();
    void setFont(const sf::Font& font);
    void draw(sf::RenderWindow& window);
    bool isWithinButton1(const sf::Vector2f& mousePos);
    bool isWithinButton2(const sf::Vector2f& mousePos);
    void setMessage(const sf::String& message, const sf::Color& color = sf::Color::Black);
private:
    sf::Text m_title;
    sf::Text m_by;
    sf::Text m_message;
    sf::Text m_again;
    sf::RectangleShape m_button1;
    sf::Text m_button1Text;
    sf::RectangleShape m_button2;
    sf::Text m_button2Text;
};