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

    m_again.setCharacterSize(30);
    m_again.setString("Play again?");
    m_again.setPosition(540.0f, 290.0f);
    m_again.setFillColor(sf::Color::Transparent);

    m_button1.setPosition(340.0f, 350.0f);
    m_button1.setSize(sf::Vector2f{240.0f, 80.0f});
    m_button1.setFillColor(sf::Color::White);
    m_button1.setOutlineColor(sf::Color::Black);
    m_button1.setOutlineThickness(1.2f);

    m_button1Text.setCharacterSize(30);
    m_button1Text.setString("2 Players");
    m_button1Text.setPosition(378.0f, 370.0f);
    m_button1Text.setFillColor(sf::Color::Black);

    m_button2.setPosition(700.0f, 350.0f);
    m_button2.setSize(sf::Vector2f{260.0f, 80.0f});
    m_button2.setFillColor(sf::Color::White);
    m_button2.setOutlineColor(sf::Color::Black);
    m_button2.setOutlineThickness(1.2f);

    m_button2Text.setCharacterSize(30);
    m_button2Text.setString("Against Bot");
    m_button2Text.setPosition(732.0f, 370.0f);
    m_button2Text.setFillColor(sf::Color::Black);

    m_buttonMystery.setPosition(1200.0f, 600.0f);
    m_buttonMystery.setSize(sf::Vector2f{60.0f, 60.0f});
    m_buttonMystery.setFillColor(sf::Color{0xef5250ff});
    m_buttonMystery.setOutlineColor(sf::Color::Black);
    m_buttonMystery.setOutlineThickness(1.2f);

    m_buttonMysteryText.setCharacterSize(30);
    m_buttonMysteryText.setString("???");
    m_buttonMysteryText.setPosition(1203.0f, 610.0f);
    m_buttonMysteryText.setFillColor(sf::Color::Black);
}

void Menu::setFont(const sf::Font& font)
{
    m_title.setFont(font);
    m_by.setFont(font);
    m_message.setFont(font);
    m_again.setFont(font);
    m_button1Text.setFont(font);
    m_button2Text.setFont(font);
    m_buttonMysteryText.setFont(font);
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(m_title);
    window.draw(m_by);
    window.draw(m_message);
    window.draw(m_again);
    window.draw(m_button1);
    window.draw(m_button1Text);
    window.draw(m_button2);
    window.draw(m_button2Text);
    window.draw(m_buttonMystery);
    window.draw(m_buttonMysteryText);
}

bool Menu::isWithinButton1(const sf::Vector2f& mousePos)
{
    return (320.0f <= mousePos.x && mousePos.x <= 320.0f + 240.0f) && (350.0f <= mousePos.y && mousePos.y <= 350.0f + 80.0f);
}

bool Menu::isWithinButton2(const sf::Vector2f& mousePos)
{
    return (700.0f <= mousePos.x && mousePos.x <= 700.0f + 310.0f) && (350.0f <= mousePos.y && mousePos.y <= 350.0f + 80.0f);
}

bool Menu::isWithinButtonMystery(const sf::Vector2f& mousePos)
{
    return (1200.0f <= mousePos.x && mousePos.x <= 1200.0f + 60.0f) && (600.0f <= mousePos.y && mousePos.y <= 600.0f + 60.0f);
}

void Menu::setMystery(bool isMysteryEnabled)
{
    if (isMysteryEnabled)
    {
        m_buttonMystery.setFillColor(sf::Color{0x4cae50ff});
    }
    else
    {
        m_buttonMystery.setFillColor(sf::Color{0xef5250ff});
    }
}

void Menu::setMessage(const sf::String& message, const sf::Color& color)
{
    m_message.setString(message);
    m_message.setFillColor(color);
    m_message.setPosition(500.0f, 130.0f);
    m_again.setFillColor(sf::Color::Black);
}
