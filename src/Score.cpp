#include "Score.hpp"
#include "Spec.hpp"
#include <string>

Score::Score() :
    m_ballSlots{2 * Spec::BALLS_PER_PLAYER + 2, sf::CircleShape{Spec::BALL_RADIUS}}
{
    m_textPlayer1.setCharacterSize(Spec::SCORE_CHAR_SIZE);
    m_textPlayer1.setString(std::to_string(m_player1));
    m_textPlayer1.setFillColor(Spec::PLAYER1_COLOR);
    m_textPlayer1.setPosition(Spec::SCORE1_POS);
    m_textPlayer1.setOutlineThickness(1.2f);
    m_textPlayer1.setOutlineColor(sf::Color{0xfcd70088});

    m_textSeparator.setCharacterSize(Spec::SCORE_CHAR_SIZE);
    m_textSeparator.setString(':');
    m_textSeparator.setFillColor(sf::Color::Black);
    m_textSeparator.setPosition(Spec::SCORE_SEP_POS);

    m_textPlayer2.setCharacterSize(Spec::SCORE_CHAR_SIZE);
    m_textPlayer2.setString(std::to_string(m_player2));
    m_textPlayer2.setFillColor(Spec::PLAYER2_COLOR);
    m_textPlayer2.setPosition(Spec::SCORE2_POS);
    m_textPlayer2.setOutlineThickness(1.2f);
    m_textPlayer2.setOutlineColor(sf::Color{0x72000488});

    const sf::Vector2f P1_START{525.0f ,50.0f};
    const sf::Vector2f P2_START{775.0f ,50.0f};

    size_t i = 0;
    for (; i < Spec::BALLS_PER_PLAYER; i++)
    {
        m_ballSlots[i].setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
        m_ballSlots[i].setFillColor(sf::Color::Transparent);
        m_ballSlots[i].setOutlineColor(sf::Color{0xfcd70088});
        m_ballSlots[i].setOutlineThickness(1.8f);
        m_ballSlots[i].setPosition(P1_START);
        m_ballSlots[i].move(-1.0f * i * 3.2f * Spec::BALL_RADIUS, 0.0f);
    }
    for (; i < 2 * Spec::BALLS_PER_PLAYER; i++)
    {
        m_ballSlots[i].setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
        m_ballSlots[i].setFillColor(sf::Color::Transparent);
        m_ballSlots[i].setOutlineColor(sf::Color{0x72000488});
        m_ballSlots[i].setOutlineThickness(1.8f);
        m_ballSlots[i].setPosition(P2_START);
        m_ballSlots[i].move((i - Spec::BALLS_PER_PLAYER) * 3.2f * Spec::BALL_RADIUS, 0.0f);
    }

    m_ballSlots[i].setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
    m_ballSlots[i].setFillColor(sf::Color::Transparent);
    m_ballSlots[i].setOutlineColor(sf::Color::Black);
    m_ballSlots[i].setOutlineThickness(1.2f);
    m_ballSlots[i].setPosition(630.0f, 80.0f);

    i++;
    m_ballSlots[i].setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
    m_ballSlots[i].setFillColor(sf::Color::Transparent);
    m_ballSlots[i].setOutlineColor(sf::Color::White);
    m_ballSlots[i].setOutlineThickness(1.2f);
    m_ballSlots[i].setPosition(673.0f, 80.0f);
}

void Score::setFont(const sf::Font& font)
{
    m_textPlayer1.setFont(font);
    m_textSeparator.setFont(font);
    m_textPlayer2.setFont(font);
}

void Score::update(Ball& ball)
{
    switch (ball.getType())
    {
    case Ball::Player1:
        ball.setScoredPosition(m_ballSlots[m_player1].getPosition());
        m_player1++;
        m_textPlayer1.setString(std::to_string(m_player1));
        break;
    case Ball::Player2:
        ball.setScoredPosition(m_ballSlots[Spec::BALLS_PER_PLAYER + m_player2].getPosition());
        m_player2++;
        m_textPlayer2.setString(std::to_string(m_player2));
        break;
    case Ball::Eightball:
        ball.setScoredPosition(m_ballSlots[2 * Spec::BALLS_PER_PLAYER].getPosition());
        break;
    case Ball::Cue:
        ball.setScoredPosition(m_ballSlots[2 * Spec::BALLS_PER_PLAYER + 1].getPosition());
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
    for (const auto& slot : m_ballSlots)
        window.draw(slot);
}
