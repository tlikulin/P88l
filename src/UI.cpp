#include "UI.hpp"
#include "Spec.hpp"
#include <string>

namespace
{
    //text
    const sf::String SEPARATOR_TEXT         {":"};
    constexpr unsigned int STATE_FONT_SIZE  = 26u;
    constexpr float TEXT_OUTLINE_THICKNESS  = 1.5f;
    constexpr float SLOTS_OUTLINE_THICKNESS = 1.8f;
    //positions
    const sf::Vector2f STATE_PLAYER1_POS            {70.0f, 20.0f};
    const sf::Vector2f STATE_PLAYER2_POS            {1130.0f, 20.0f};
    const sf::Vector2f SLOTS_PLAYER1_START          {525.0f ,50.0f};
    const sf::Vector2f SLOTS_PLAYER2_START          {775.0f ,50.0f};
    constexpr float SLOTS_SEPARATION                = 3.2f * Spec::BALL_RADIUS;
    const sf::Vector2f SLOTS_EIGHTBALL_POS          {630.0f, 80.0f};
    const sf::Vector2f SLOTS_CUEBALL_POS            {673.0f, 80.0f};
    const sf::Vector2f EIGHTBALL_READY_PLAYER1_POS  {612.0f, 62.0f};
    const sf::Vector2f EIGHTBALL_READY_PLAYER2_POS  {630.0f, 62.0f};
    const sf::Vector2f EIGHTBALL_READY_SIZE         {18.0f, 36.0f};
    //colors (alpha reduced to half)
    const sf::Color PLAYER1_COLOR_CONTOUR   {Spec::PLAYER1_COLOR.toInteger() & 0xffffff88};
    const sf::Color PLAYER2_COLOR_CONTOUR   {Spec::PLAYER2_COLOR.toInteger() & 0xffffff88};
}

//first 7 balls - player1, next 7 balls - player2, then eight-ball, then cue ball; 16 in total
UI::UI() :
    m_ballSlots{2 * Spec::BALLS_PER_PLAYER + 2, sf::CircleShape{Spec::BALL_RADIUS}}
{
    m_textPlayer1Score.setCharacterSize(Spec::SCORE_CHAR_SIZE);
    m_textPlayer1Score.setString(std::to_string(m_player1));
    m_textPlayer1Score.setFillColor(Spec::PLAYER1_COLOR);
    m_textPlayer1Score.setPosition(Spec::SCORE1_POS);
    m_textPlayer1Score.setOutlineThickness(TEXT_OUTLINE_THICKNESS);
    m_textPlayer1Score.setOutlineColor(PLAYER1_COLOR_CONTOUR);

    m_textPlayer2Score.setCharacterSize(Spec::SCORE_CHAR_SIZE);
    m_textPlayer2Score.setString(std::to_string(m_player2));
    m_textPlayer2Score.setFillColor(Spec::PLAYER2_COLOR);
    m_textPlayer2Score.setPosition(Spec::SCORE2_POS);
    m_textPlayer2Score.setOutlineThickness(TEXT_OUTLINE_THICKNESS);
    m_textPlayer2Score.setOutlineColor(PLAYER2_COLOR_CONTOUR);

    m_textSeparator.setCharacterSize(Spec::SCORE_CHAR_SIZE);
    m_textSeparator.setString(SEPARATOR_TEXT);
    m_textSeparator.setFillColor(sf::Color::Black);
    m_textSeparator.setPosition(Spec::SCORE_SEP_POS);

    m_textPlayer1State.setCharacterSize(STATE_FONT_SIZE);
    m_textPlayer1State.setFillColor(Spec::PLAYER1_COLOR); 
    m_textPlayer1State.setPosition(STATE_PLAYER1_POS);
    m_textPlayer1State.setOutlineThickness(TEXT_OUTLINE_THICKNESS);
    m_textPlayer1State.setOutlineColor(PLAYER1_COLOR_CONTOUR);

    m_textPlayer2State.setCharacterSize(STATE_FONT_SIZE);
    m_textPlayer2State.setFillColor(Spec::PLAYER2_COLOR); 
    m_textPlayer2State.setPosition(STATE_PLAYER2_POS);
    m_textPlayer2State.setOutlineThickness(TEXT_OUTLINE_THICKNESS);
    m_textPlayer2State.setOutlineColor(PLAYER2_COLOR_CONTOUR);

    size_t i = 0;
    // player1's
    for (; i < Spec::BALLS_PER_PLAYER; i++)
    {
        m_ballSlots[i].setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
        m_ballSlots[i].setFillColor(sf::Color::Transparent);
        m_ballSlots[i].setOutlineColor(PLAYER1_COLOR_CONTOUR);
        m_ballSlots[i].setOutlineThickness(SLOTS_OUTLINE_THICKNESS);
        m_ballSlots[i].setPosition(SLOTS_PLAYER1_START);
        m_ballSlots[i].move(static_cast<float>(i) * -SLOTS_SEPARATION, 0.0f);
    }
    // player2's
    for (; i < 2 * Spec::BALLS_PER_PLAYER; i++)
    {
        m_ballSlots[i].setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
        m_ballSlots[i].setFillColor(sf::Color::Transparent);
        m_ballSlots[i].setOutlineColor(PLAYER2_COLOR_CONTOUR);
        m_ballSlots[i].setOutlineThickness(SLOTS_OUTLINE_THICKNESS);
        m_ballSlots[i].setPosition(SLOTS_PLAYER2_START);
        m_ballSlots[i].move(static_cast<float>(i - Spec::BALLS_PER_PLAYER) * SLOTS_SEPARATION, 0.0f);
    }
    // eight-ball
    m_ballSlots[i].setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
    m_ballSlots[i].setFillColor(sf::Color::Transparent);
    m_ballSlots[i].setOutlineColor(Spec::EIGHTBALL_COLOR);
    m_ballSlots[i].setOutlineThickness(SLOTS_OUTLINE_THICKNESS);
    m_ballSlots[i].setPosition(SLOTS_EIGHTBALL_POS);
    i++;
    // cue ball
    m_ballSlots[i].setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
    m_ballSlots[i].setFillColor(sf::Color::Transparent);
    m_ballSlots[i].setOutlineColor(sf::Color::White);
    m_ballSlots[i].setOutlineThickness(SLOTS_OUTLINE_THICKNESS);
    m_ballSlots[i].setPosition(SLOTS_CUEBALL_POS);

    m_eightballReadyPlayer1.setPosition(EIGHTBALL_READY_PLAYER1_POS);
    m_eightballReadyPlayer1.setSize(EIGHTBALL_READY_SIZE);
    m_eightballReadyPlayer1.setFillColor(PLAYER1_COLOR_CONTOUR);
    m_eightballReadyPlayer2.setPosition(EIGHTBALL_READY_PLAYER2_POS);
    m_eightballReadyPlayer2.setSize(EIGHTBALL_READY_SIZE);
    m_eightballReadyPlayer2.setFillColor(PLAYER2_COLOR_CONTOUR);
}

void UI::setFont(const sf::Font& font)
{
    m_textPlayer1State.setFont(font);
    m_textPlayer1Score.setFont(font);
    m_textSeparator.setFont(font);
    m_textPlayer2Score.setFont(font);
    m_textPlayer2State.setFont(font);
}

// Updates the score with the new potted ball.
// Return true if the potted eight-ball was final.
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

//colored indications under the eight-ball slot are drawn if the player has potted all their balls
void UI::draw(sf::RenderWindow& window)
{    
    //scores
    window.draw(m_textPlayer1Score);
    window.draw(m_textPlayer2Score);
    window.draw(m_textSeparator);
    //state
    if (m_activePlayer == 1)
    {
        window.draw(m_textPlayer1State);
    }
    if (m_activePlayer == 2)
    {
        window.draw(m_textPlayer2State);
    }
    //ball slots
    if (m_player1 == Spec::BALLS_PER_PLAYER)
    {
        window.draw(m_eightballReadyPlayer1);
    }
    if (m_player2 == Spec::BALLS_PER_PLAYER)
    {
        window.draw(m_eightballReadyPlayer2);
    }
    for (const auto& slot : m_ballSlots)
    {
        window.draw(slot);
    }
}

// Sets the string for the active player.
void UI::setString(unsigned char activePlayer, const sf::String& state)
{
    switch (m_activePlayer = activePlayer)
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

// Resets the scores
void UI::reset()
{
    m_player1 = 0;
    m_textPlayer1Score.setString(std::to_string(m_player1));
    m_player2 = 0;
    m_textPlayer2Score.setString(std::to_string(m_player2));
    m_activePlayer = 1;
}
