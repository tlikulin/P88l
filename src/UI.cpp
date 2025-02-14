#include "UI.hpp"
#include "Spec.hpp"
#include <string>

UI::UI() :
    m_ballSlots{2 * Spec::BALLS_PER_PLAYER + 2, sf::CircleShape{Spec::BALL_RADIUS}}
{
    m_textPlayer1State.setCharacterSize(26);
    m_textPlayer1State.setFillColor(Spec::PLAYER1_COLOR); 
    m_textPlayer1State.setPosition(70.0f, 20.0f);
    m_textPlayer1State.setOutlineThickness(1.5f);
    m_textPlayer1State.setOutlineColor(sf::Color{0xfcd70088});

    m_textPlayer1Score.setCharacterSize(Spec::SCORE_CHAR_SIZE);
    m_textPlayer1Score.setString(std::to_string(m_player1));
    m_textPlayer1Score.setFillColor(Spec::PLAYER1_COLOR);
    m_textPlayer1Score.setPosition(Spec::SCORE1_POS);
    m_textPlayer1Score.setOutlineThickness(1.5f);
    m_textPlayer1Score.setOutlineColor(sf::Color{0xfcd70088});

    m_textSeparator.setCharacterSize(Spec::SCORE_CHAR_SIZE);
    m_textSeparator.setString(':');
    m_textSeparator.setFillColor(sf::Color::Black);
    m_textSeparator.setPosition(Spec::SCORE_SEP_POS);

    m_textPlayer2Score.setCharacterSize(Spec::SCORE_CHAR_SIZE);
    m_textPlayer2Score.setString(std::to_string(m_player2));
    m_textPlayer2Score.setFillColor(Spec::PLAYER2_COLOR);
    m_textPlayer2Score.setPosition(Spec::SCORE2_POS);
    m_textPlayer2Score.setOutlineThickness(1.5f);
    m_textPlayer2Score.setOutlineColor(sf::Color{0x72000488});

    m_textPlayer2State.setCharacterSize(26);
    m_textPlayer2State.setFillColor(Spec::PLAYER2_COLOR); 
    m_textPlayer2State.setPosition(1130.0f, 20.0f);
    m_textPlayer2State.setOutlineThickness(2.0f);
    m_textPlayer2State.setOutlineColor(sf::Color{0x72000488});

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
        m_ballSlots[i].move(i * -3.2f * Spec::BALL_RADIUS, 0.0f);
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
    m_ballSlots[i].setOutlineColor(Spec::EIGHTBALL_COLOR);
    m_ballSlots[i].setOutlineThickness(1.2f);
    m_ballSlots[i].setPosition(630.0f, 80.0f);
    i++;
    m_ballSlots[i].setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
    m_ballSlots[i].setFillColor(sf::Color::Transparent);
    m_ballSlots[i].setOutlineColor(sf::Color::White);
    m_ballSlots[i].setOutlineThickness(1.2f);
    m_ballSlots[i].setPosition(673.0f, 80.0f);

    m_eightballReadyPlayer1.setPosition(612.0f, 62.0f);
    m_eightballReadyPlayer1.setSize(sf::Vector2f{18.0f, 36.0f});
    m_eightballReadyPlayer1.setFillColor(sf::Color{0xfcd70088});

    m_eightballReadyPlayer2.setPosition(630.0f, 62.0f);
    m_eightballReadyPlayer2.setSize(sf::Vector2f{18.0f, 36.0f});
    m_eightballReadyPlayer2.setFillColor(sf::Color{0x72000488});
}

void UI::setFont(const sf::Font& font)
{
    m_textPlayer1State.setFont(font);
    m_textPlayer1Score.setFont(font);
    m_textSeparator.setFont(font);
    m_textPlayer2Score.setFont(font);
    m_textPlayer2State.setFont(font);
}

void UI::setString(unsigned char activePlayer, const sf::String& state)
{
    m_activePlayer = activePlayer;
    switch (m_activePlayer)
    {
    case 1:
        m_textPlayer1State.setString(state);
        break;
    case 2:
        m_textPlayer2State.setString(state);
        break;
    default:
        break;
    }
}

bool UI::update(Ball& ball)
{
    switch (ball.getType())
    {
    case Ball::Player1:
        ball.setScoredPosition(m_ballSlots[m_player1].getPosition());
        m_player1++;
        m_textPlayer1Score.setString(std::to_string(m_player1));
        return false;
    case Ball::Player2:
        ball.setScoredPosition(m_ballSlots[Spec::BALLS_PER_PLAYER + m_player2].getPosition());
        m_player2++;
        m_textPlayer2Score.setString(std::to_string(m_player2));
        return false;
    case Ball::Eightball:
        ball.setScoredPosition(m_ballSlots[2 * Spec::BALLS_PER_PLAYER].getPosition());
        if ((m_activePlayer == 1 && m_player1 == Spec::BALLS_PER_PLAYER)
         || (m_activePlayer == 2 && m_player2 == Spec::BALLS_PER_PLAYER))
        {
            return true;
        }
        else
        {
            return false;
        }
    case Ball::Cue:
        ball.setScoredPosition(m_ballSlots[2 * Spec::BALLS_PER_PLAYER + 1].getPosition());
        return false;
    default:
        return false;
    }
}

void UI::draw(sf::RenderWindow& window)
{
    if (m_activePlayer == 1)
        window.draw(m_textPlayer1State);
    window.draw(m_textPlayer1Score);
    window.draw(m_textSeparator);
    window.draw(m_textPlayer2Score);
    if (m_activePlayer == 2)
        window.draw(m_textPlayer2State);
    if (m_player1 == Spec::BALLS_PER_PLAYER)
        window.draw(m_eightballReadyPlayer1);
    if (m_player2 == Spec::BALLS_PER_PLAYER)
        window.draw(m_eightballReadyPlayer2);
    for (const auto& slot : m_ballSlots)
        window.draw(slot);
}

void UI::reset()
{
    m_player1 = 0;
    m_textPlayer1Score.setString(std::to_string(m_player1));
    m_player2 = 0;
    m_textPlayer2Score.setString(std::to_string(m_player2));
    m_activePlayer = 1;
}
