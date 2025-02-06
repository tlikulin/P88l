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

        m_effects[i].first.setPosition(Spec::POCKETS_POS[i]);
        m_effects[i].first.setFillColor(sf::Color::Transparent);
        m_effects[i].second = 0.0f;
    }
}

void Pockets::update(float deltaTime)
{
    for (size_t i = 0; i < Spec::NUM_POCKETS; i++)
    {
        if (m_effects[i].second != 0.0f)
        {
            m_effects[i].second -= deltaTime;
            if (m_effects[i].second <= 0.0f)
                m_effects[i].second = 0.0f;
            else
            {
                const float radius = Spec::POCKET_ANIM_RADIUS * m_effects[i].second / Spec::POCKET_ANIM_DURATION;
                m_effects[i].first.setRadius(radius);
                m_effects[i].first.setOrigin(radius, radius);
                m_effects[i].first.setOutlineThickness(Spec::POCKET_ANIM_THICKNESS * m_effects[i].second / Spec::POCKET_ANIM_DURATION);
            }
        }
    }
}

void Pockets::draw(sf::RenderWindow& window)
{
    for (const auto& pocket : m_pockets)
        window.draw(pocket);
    for (size_t i = 0; i < Spec::NUM_POCKETS; i++)
        if (m_effects[i].second > 0.0f)
            window.draw(m_effects[i].first);
}

bool Pockets::isBallPotted(Ball& ball)
{
    for (size_t i = 0; i < Spec::NUM_POCKETS; i++)
    {
        sf::Vector2f displacement = m_pockets[i].getPosition() - ball.getPosition();
        if (std::hypot(displacement.x, displacement.y) < Spec::POCKET_THRESHOLD)
        {
            m_effects[i].first.setOutlineColor(Ball::colorFromType(ball.getType()));
            m_effects[i].second = Spec::POCKET_ANIM_DURATION;
            ball.pot();
            return true;
        }
    }

    return false;
}