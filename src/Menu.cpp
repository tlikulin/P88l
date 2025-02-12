#include "Menu.hpp"

Menu::Menu()
{
    m_title.setCharacterSize(80);
    m_title.setString("P88l");
    m_title.setPosition(550.0f, 25.0f);
    m_title.setFillColor(sf::Color::Black);

    m_by.setCharacterSize(30);
    m_by.setString("by tlikulin");
    m_by.setPosition(755.0f, 75.0f);
    m_by.setFillColor(sf::Color::Black);

    m_message.setCharacterSize(40);
    m_message.setString("Welcome to the game!");
    m_message.setPosition(420.0f, 130.0f);
    m_message.setFillColor(sf::Color::Black);

    m_button1.setPosition(320.0f, 350.0f);
    m_button1.setSize(sf::Vector2f{240.0f, 80.0f});
    m_button1.setFillColor(sf::Color::White);
    m_button1.setOutlineColor(sf::Color::Black);
    m_button1.setOutlineThickness(1.2f);

    m_button1Text.setCharacterSize(30);
    m_button1Text.setString("2 Players");
    m_button1Text.setPosition(358.0f, 370.0f);
    m_button1Text.setFillColor(sf::Color::Black);

    m_button2.setPosition(700.0f, 350.0f);
    m_button2.setSize(sf::Vector2f{310.0f, 80.0f});
    m_button2.setFillColor(sf::Color::White);
    m_button2.setOutlineColor(sf::Color::Black);
    m_button2.setOutlineThickness(1.2f);

    m_button2Text.setCharacterSize(30);
    m_button2Text.setString("Versus Computer");
    m_button2Text.setPosition(722.0f, 370.0f);
    m_button2Text.setFillColor(sf::Color::Black);
}

void Menu::setFont(const sf::Font& font)
{
    m_title.setFont(font);
    m_by.setFont(font);
    m_message.setFont(font);
    m_button1Text.setFont(font);
    m_button2Text.setFont(font);
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(m_title);
    window.draw(m_by);
    window.draw(m_message);
    window.draw(m_button1);
    window.draw(m_button1Text);
    window.draw(m_button2);
    window.draw(m_button2Text);
}

bool Menu::isWithinButton1(const sf::Vector2f& mousePos)
{
    return (320.0f <= mousePos.x && mousePos.x <= 320.0f + 240.0f) && (350.0f <= mousePos.y && mousePos.y <= 350.0f + 80.0f);
}

bool Menu::isWithinButton2(const sf::Vector2f& mousePos)
{
    return (700.0f <= mousePos.x && mousePos.x <= 700.0f + 310.0f) && (350.0f <= mousePos.y && mousePos.y <= 350.0f + 80.0f);
}

void Menu::setMessage(const sf::String& message, const sf::Color& color)
{
    m_message.setString(message);
    m_message.setFillColor(color);
    m_message.setPosition(500.0f, 130.0f);
}
