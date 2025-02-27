#include "Menu.hpp"

namespace
{
    // Strings
    const sf::String TITLE_STRING           {"P88l"};
    const sf::String BY_STRING              {"by tlikulin"};
    const sf::String MESSAGE_INITIAL_STRING {"Welcome to the game!"};
    const sf::String AGAIN_STRING           {"Play again?"};
    const sf::String BUTTON_MODE1_STRING    {"2 Players"};
    const sf::String BUTTON_MODE2_STRING    {"Against Bot"};
    const sf::String MYSTERY_STRING         {"???"};
    // Colors
    const sf::Color MAIN_TEXT_COLOR         = sf::Color::Black;
    const sf::Color BY_COLOR                {0x121e47ff};
    const sf::Color BUTTONS_FILL_COLOR      = sf::Color::White;
    const sf::Color MYSTERY_ENABLED_COLOR   {0x4cae50ff};
    const sf::Color MYSTERY_DISABLED_COLOR  {0xef5250ff};
    // Font sizes
    constexpr unsigned int MAIN_FONT_SIZE    = 30U;
    constexpr unsigned int TITLE_FONT_SIZE   = 80U;
    constexpr unsigned int MESSAGE_FONT_SIZE = 40U;
    // Positions
    const sf::Vector2f TITLE_POS                {550.0f, 25.0f};
    const sf::Vector2f BY_POS                   {755.0f, 75.0f};
    const sf::Vector2f MESSAGE_POS              {420.0f, 130.0f};
    const sf::Vector2f AGAIN_POS                {540.0f, 290.0f};
    const sf::Vector2f BUTTON_MODE1_RECT_POS    {340.0f, 350.0f};
    const sf::Vector2f BUTTON_MODE1_TEXT_POS    {378.0f, 370.0f};
    const sf::Vector2f BUTTON_MODE2_RECT_POS    {700.0f, 350.0f};
    const sf::Vector2f BUTTON_MODE2_TEXT_POS    {732.0f, 370.0f};
    const sf::Vector2f BUTTON_MYSTERY_RECT_POS  {1200.0f, 600.0f};
    const sf::Vector2f BUTTON_MYSTERY_TEXT_POS  {1203.0f, 610.0f};
    const sf::Vector2f INFO_POS                 {10.0f, 465.0f};
    // Button sizes
    const sf::Vector2f BUTTON_MODE1_SIZE        {240.0f, 80.0f};
    const sf::Vector2f BUTTON_MODE2_SIZE        {260.0f, 80.0f};
    const sf::Vector2f BUTTON_MYSTERY_SIZE      {60.0f, 60.0f};
    constexpr float BUTTON_OUTLINE_THICKNESS    = 1.2f;
}

// Initializing all the members' color, position, size, and string.
Menu::Menu()
{
    m_title.setCharacterSize(TITLE_FONT_SIZE);
    m_title.setString(TITLE_STRING);
    m_title.setPosition(TITLE_POS);
    m_title.setFillColor(MAIN_TEXT_COLOR);

    m_by.setCharacterSize(MAIN_FONT_SIZE);
    m_by.setString(BY_STRING);
    m_by.setPosition(BY_POS);
    m_by.setFillColor(BY_COLOR);

    m_message.setCharacterSize(MESSAGE_FONT_SIZE);
    m_message.setString(MESSAGE_INITIAL_STRING);
    m_message.setPosition(MESSAGE_POS);
    m_message.setFillColor(MAIN_TEXT_COLOR);

    // Transparent when first time in the menu
    m_again.setCharacterSize(MAIN_FONT_SIZE);
    m_again.setString(AGAIN_STRING);
    m_again.setPosition(AGAIN_POS);
    m_again.setFillColor(sf::Color::Transparent);

    m_buttonMode1Rect.setPosition(BUTTON_MODE1_RECT_POS);
    m_buttonMode1Rect.setSize(BUTTON_MODE1_SIZE);
    m_buttonMode1Rect.setFillColor(BUTTONS_FILL_COLOR);
    m_buttonMode1Rect.setOutlineColor(MAIN_TEXT_COLOR);
    m_buttonMode1Rect.setOutlineThickness(BUTTON_OUTLINE_THICKNESS);
    m_buttonMode1Text.setCharacterSize(MAIN_FONT_SIZE);
    m_buttonMode1Text.setString(BUTTON_MODE1_STRING);
    m_buttonMode1Text.setPosition(BUTTON_MODE1_TEXT_POS);
    m_buttonMode1Text.setFillColor(MAIN_TEXT_COLOR);

    m_buttonMode2Rect.setPosition(BUTTON_MODE2_RECT_POS);
    m_buttonMode2Rect.setSize(BUTTON_MODE2_SIZE);
    m_buttonMode2Rect.setFillColor(BUTTONS_FILL_COLOR);
    m_buttonMode2Rect.setOutlineColor(MAIN_TEXT_COLOR);
    m_buttonMode2Rect.setOutlineThickness(BUTTON_OUTLINE_THICKNESS);
    m_buttonMode2Text.setCharacterSize(MAIN_FONT_SIZE);
    m_buttonMode2Text.setString(BUTTON_MODE2_STRING);
    m_buttonMode2Text.setPosition(BUTTON_MODE2_TEXT_POS);
    m_buttonMode2Text.setFillColor(MAIN_TEXT_COLOR);

    m_buttonMysteryRect.setPosition(BUTTON_MYSTERY_RECT_POS);
    m_buttonMysteryRect.setSize(BUTTON_MYSTERY_SIZE);
    m_buttonMysteryRect.setFillColor(MYSTERY_DISABLED_COLOR);
    m_buttonMysteryRect.setOutlineColor(MAIN_TEXT_COLOR);
    m_buttonMysteryRect.setOutlineThickness(BUTTON_OUTLINE_THICKNESS);
    m_buttonMysteryText.setCharacterSize(MAIN_FONT_SIZE);
    m_buttonMysteryText.setString(MYSTERY_STRING);
    m_buttonMysteryText.setPosition(BUTTON_MYSTERY_TEXT_POS);
    m_buttonMysteryText.setFillColor(MAIN_TEXT_COLOR);

    m_info.setPosition(INFO_POS);
}

void Menu::setFontAndTexture(const sf::Font& font, const sf::Texture& texture)
{
    m_title.setFont(font);
    m_by.setFont(font);
    m_message.setFont(font);
    m_again.setFont(font);
    m_buttonMode1Text.setFont(font);
    m_buttonMode2Text.setFont(font);
    m_buttonMysteryText.setFont(font);
    m_info.setTexture(texture);
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(m_title);
    window.draw(m_by);
    window.draw(m_message);
    window.draw(m_again);
    window.draw(m_buttonMode1Rect);
    window.draw(m_buttonMode1Text);
    window.draw(m_buttonMode2Rect);
    window.draw(m_buttonMode2Text);
    window.draw(m_buttonMysteryRect);
    window.draw(m_buttonMysteryText);
    window.draw(m_info);
}

// Checks whether the mouse position is within one of the followind button rectangles.

bool Menu::isWithinButtonMode1(const sf::Vector2f& mousePos)
{
    return (BUTTON_MODE1_RECT_POS.x <= mousePos.x && mousePos.x <= BUTTON_MODE1_RECT_POS.x + BUTTON_MODE1_SIZE.x) 
        && (BUTTON_MODE1_RECT_POS.y <= mousePos.y && mousePos.y <= BUTTON_MODE1_RECT_POS.y + BUTTON_MODE1_SIZE.y);
}

bool Menu::isWithinButtonMode2(const sf::Vector2f& mousePos)
{
    return (BUTTON_MODE2_RECT_POS.x <= mousePos.x && mousePos.x <= BUTTON_MODE2_RECT_POS.x + BUTTON_MODE2_SIZE.x) 
        && (BUTTON_MODE2_RECT_POS.y <= mousePos.y && mousePos.y <= BUTTON_MODE2_RECT_POS.y + BUTTON_MODE2_SIZE.y);
}

bool Menu::isWithinButtonMystery(const sf::Vector2f& mousePos)
{
    return (BUTTON_MYSTERY_RECT_POS.x <= mousePos.x && mousePos.x <= BUTTON_MYSTERY_RECT_POS.x + BUTTON_MYSTERY_SIZE.x) 
        && (BUTTON_MYSTERY_RECT_POS.y <= mousePos.y && mousePos.y <= BUTTON_MYSTERY_RECT_POS.y + BUTTON_MYSTERY_SIZE.y);
}

// Sets the enabled/disabled color of the mystery button.
void Menu::setMystery(bool isMysteryEnabled)
{
    m_buttonMysteryRect.setFillColor(isMysteryEnabled ? MYSTERY_ENABLED_COLOR : MYSTERY_DISABLED_COLOR);
}

// Sets the string and color of the message, also makes the 'play again' visible.
void Menu::setMessage(const sf::String& message, const sf::Color& color)
{
    m_message.setString(message);
    m_message.setFillColor(color);
    m_again.setFillColor(MAIN_TEXT_COLOR);
}
