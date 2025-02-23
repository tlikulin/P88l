#include "Pockets.hpp"
#include <cmath>

Pockets::Pockets()
{
    for (size_t i = 0; i < Spec::NUM_POCKETS; i++)
    {
        m_pockets[i].setPosition(Spec::POCKETS_POS[i]);
        m_pockets[i].setOrigin(Spec::POCKET_RADIUS, Spec::POCKET_RADIUS);
        m_pockets[i].setRadius(Spec::POCKET_RADIUS);
        m_pockets[i].setFillColor(sf::Color::Black);
    }
    m_soundPotting.setAttenuation(0.0f);
    m_soundPotting.setVolume(40.0f);
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

bool Pockets::checkBallPotted(Ball& ball)
{
    for (size_t i = 0; i < Spec::NUM_POCKETS; i++)
    {
        sf::Vector2f displacement = m_pockets[i].getPosition() - ball.getPosition();
        if (Spec::hypot(displacement) < Spec::POCKET_THRESHOLD)
        {
            ball.pot(m_pockets[i].getPosition());
            m_soundPotting.setPosition(m_pockets[i].getPosition().x, 0.0f, m_pockets[i].getPosition().y);
            m_soundPotting.play();
            return true;
        }
    }

    return false;
}
