#pragma once

#include <SFML/Graphics.hpp>

// Responsible for displaying the main menu text and buttons.
class Menu
{
public:
    Menu();
    void setFontAndTexture(const sf::Font& font, const sf::Texture& texture);
    void draw(sf::RenderWindow& window);

    bool isWithinButtonMode1(const sf::Vector2f& mousePos);
    bool isWithinButtonMode2(const sf::Vector2f& mousePos);
    bool isWithinButtonMystery(const sf::Vector2f& mousePos);

    void setMystery(bool isMysteryEnabled);
    void setMessage(const sf::String& message, const sf::Color& color);
private:
    // Text
    sf::Text m_title;
    sf::Text m_by;
    sf::Text m_message;
    sf::Text m_again;
    sf::Sprite m_info;
    // Buttons
    sf::RectangleShape m_buttonMode1Rect;
    sf::Text m_buttonMode1Text;
    sf::RectangleShape m_buttonMode2Rect;
    sf::Text m_buttonMode2Text;
    sf::RectangleShape m_buttonMysteryRect;
    sf::Text m_buttonMysteryText;
};
