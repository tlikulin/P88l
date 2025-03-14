#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include <vector>

// Displays and updates the scores and current state.
class UI
{
public:
    UI();
    void setFont(const sf::Font& font);

    [[nodiscard]] bool update(Ball& ball);
    void draw(sf::RenderWindow& window);

    void setString(unsigned char activePlayer, const sf::String& state);
    void reset();
private:
    //number of scored balls and active player
    unsigned char m_player1 = 0;
    unsigned char m_player2 = 0;
    unsigned char m_activePlayer = 1;
    //current state and scores
    sf::Text m_textPlayer1Score;
    sf::Text m_textPlayer2Score;
    sf::Text m_textSeparator;
    sf::Text m_textPlayer1State;
    sf::Text m_textPlayer2State;
    //ball slots
    std::vector<sf::CircleShape> m_ballSlots;
    sf::RectangleShape m_eightballReadyPlayer1;
    sf::RectangleShape m_eightballReadyPlayer2;
};
