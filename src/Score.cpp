#include "Score.hpp"
#include "Spec.hpp"
#include <string>

Score::Score()
{
    m_textPlayer1.setCharacterSize(Spec::SCORE_CHAR_SIZE);
    m_textPlayer1.setString(std::to_string(m_player1));
    m_textPlayer1.setFillColor(Spec::PLAYER1_COLOR);
    m_textPlayer1.setPosition(Spec::SCORE1_POS);
    m_textPlayer1.setOutlineThickness(0.8f);
    m_textPlayer1.setOutlineColor(sf::Color::Black);

    m_textSeparator.setCharacterSize(Spec::SCORE_CHAR_SIZE);
    m_textSeparator.setString(':');
    m_textSeparator.setFillColor(sf::Color::Black);
    m_textSeparator.setPosition(Spec::SCORE_SEP_POS);

    m_textPlayer2.setCharacterSize(Spec::SCORE_CHAR_SIZE);
    m_textPlayer2.setString(std::to_string(m_player2));
    m_textPlayer2.setFillColor(Spec::PLAYER2_COLOR);
    m_textPlayer2.setPosition(Spec::SCORE2_POS);
    m_textPlayer2.setOutlineThickness(0.8f);
    m_textPlayer2.setOutlineColor(sf::Color::Black);
}

void Score::setFont(const sf::Font& font)
{
    m_textPlayer1.setFont(font);
    m_textSeparator.setFont(font);
    m_textPlayer2.setFont(font);
}

void Score::update(Ball::BallType type)
{
    switch (type)
    {
    case Ball::Player1:
        m_player1++;
        m_textPlayer1.setString(std::to_string(m_player1));
        break;
    case Ball::Player2:
        m_player2++;
        m_textPlayer2.setString(std::to_string(m_player2));
        break;
    default:
        break;
    }
}

void Score::draw(sf::RenderWindow& window)
{
    window.draw(m_textPlayer1);
    window.draw(m_textSeparator);
    window.draw(m_textPlayer2);
}