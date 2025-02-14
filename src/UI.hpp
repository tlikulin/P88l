#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include <vector>

class UI
{
public:
    UI();
    void setFont(const sf::Font& font);
    void setString(unsigned char activePlayer, const sf::String& state);
    [[nodiscard]] bool update(Ball& ball);
    void draw(sf::RenderWindow& window);
    void reset();
private:
    unsigned char m_player1 = 0;
    unsigned char m_player2 = 0;
    unsigned char m_activePlayer = 1;
    sf::Text m_textPlayer1State;
    sf::Text m_textPlayer1Score;
    sf::Text m_textSeparator;
    sf::Text m_textPlayer2Score;
    sf::Text m_textPlayer2State;
    sf::RectangleShape m_eightballReadyPlayer1;
    sf::RectangleShape m_eightballReadyPlayer2;
    std::vector<sf::CircleShape> m_ballSlots;
};
