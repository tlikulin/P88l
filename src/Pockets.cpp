#include "Pockets.hpp"
#include "Spec.hpp"

namespace
{
    constexpr float POCKET_RADIUS                = 20.0f;
    constexpr float POCKET_THRESHOLD             = 0.9f * (Spec::BALL_RADIUS + POCKET_RADIUS);
    constexpr float POCKETS_OFFSET               = 5.0f;
    const std::array<sf::Vector2f, Pockets::NUM_POCKETS> POCKETS_POS{{
        {Spec::TABLE_LEFT + POCKETS_OFFSET, Spec::TABLE_TOP + POCKETS_OFFSET}, 
        {Spec::TABLE_LEFT + POCKETS_OFFSET, Spec::TABLE_BOTTOM - POCKETS_OFFSET},
        {(Spec::TABLE_LEFT + Spec::TABLE_RIGHT) / 2.0f, Spec::TABLE_TOP - POCKETS_OFFSET},
        {(Spec::TABLE_LEFT + Spec::TABLE_RIGHT) / 2.0f, Spec::TABLE_BOTTOM + POCKETS_OFFSET},
        {Spec::TABLE_RIGHT - POCKETS_OFFSET, Spec::TABLE_TOP + POCKETS_OFFSET},
        {Spec::TABLE_RIGHT - POCKETS_OFFSET, Spec::TABLE_BOTTOM - POCKETS_OFFSET} 
    }};
    constexpr float POTTING_SOUND_VOLUME = 40.0f;
}

Pockets::Pockets()
{
    for (size_t i = 0; i < NUM_POCKETS; i++)
    {
        m_pockets[i].setPosition(POCKETS_POS[i]);
        m_pockets[i].setOrigin(POCKET_RADIUS, POCKET_RADIUS);
        m_pockets[i].setRadius(POCKET_RADIUS);
        m_pockets[i].setFillColor(sf::Color::Black);
    }
    m_soundPotting.setAttenuation(0.0f);
    m_soundPotting.setVolume(POTTING_SOUND_VOLUME);
}

void Pockets::setBuffer(const sf::SoundBuffer& buffer)
{
    m_soundPotting.setBuffer(buffer);
}

void Pockets::draw(sf::RenderWindow& window)
{
    for (const auto& pocket : m_pockets)
    {
        window.draw(pocket);
    }
}

// Checks if the ball is potted.
// If so, makes it potted, plays the sound of potting at the right pocket, and returns true.
bool Pockets::checkBallPotted(Ball& ball)
{
    for (const auto& pocket : m_pockets)
    {
        sf::Vector2f displacement = pocket.getPosition() - ball.getPosition();
        if (Spec::hypot(displacement) < POCKET_THRESHOLD)
        {
            ball.pot(pocket.getPosition());
            m_soundPotting.setPosition(pocket.getPosition().x, 0.0f, pocket.getPosition().y);
            m_soundPotting.play();
            return true;
        }
    }

    return false;
}
