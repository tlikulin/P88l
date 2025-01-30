#include "Trajectory.hpp"

Trajectory::Trajectory()
{
    m_ballPrev.setRadius(Specs::BALL_RADIUS);
    m_ballPrev.setFillColor(sf::Color::Transparent);
    m_ballPrev.setOrigin(Specs::BALL_RADIUS, Specs::BALL_RADIUS);
    m_ballPrev.setOutlineColor(sf::Color::White);
    m_ballPrev.setOutlineThickness(1.0f);
}

// Calculates the 2 segments of trajectory with reflection off the wall if needed
// Basically checks which wall the trajectory crosses, if any, and reflects in it
void Trajectory::update(const sf::Vector2f& chargeStart, const sf::Vector2f& mousePosition)
{
    m_segment1[0].position = chargeStart;
    m_segment1[1].position = m_segment1[0].position + 2.5f * (chargeStart - mousePosition);

    m_isExtensionNeeded = true;
    float gradient = (m_segment1[0].position.y - m_segment1[1].position.y) / (m_segment1[0].position.x - m_segment1[1].position.x);

    // the end of trajectory is in the ... third and entersects the ... wall
    if (m_segment1[1].position.y < (Specs::TABLE_TOP + Specs::BALL_RADIUS)) // top
    {
        float x_intercept = m_segment1[0].position.x + ((Specs::TABLE_TOP + Specs::BALL_RADIUS) - m_segment1[0].position.y) / gradient;

        if (x_intercept < (Specs::TABLE_LEFT + Specs::BALL_RADIUS)) // left wall
        {
            m_segment2[1].position.x = 2 * (Specs::TABLE_LEFT + Specs::BALL_RADIUS) - m_segment1[1].position.x;
            m_segment2[1].position.y = m_segment1[1].position.y;
            m_segment1[1].position.y = m_segment1[0].position.y - (m_segment1[0].position.x - (Specs::TABLE_LEFT + Specs::BALL_RADIUS)) * gradient;
            m_segment1[1].position.x = (Specs::TABLE_LEFT + Specs::BALL_RADIUS);
        }
        else if (x_intercept > (Specs::TABLE_RIGHT- Specs::BALL_RADIUS)) // right wall
        {
            m_segment2[1].position.x = 2 * (Specs::TABLE_RIGHT- Specs::BALL_RADIUS) - m_segment1[1].position.x;
            m_segment2[1].position.y = m_segment1[1].position.y;
            m_segment1[1].position.y = m_segment1[0].position.y - (m_segment1[0].position.x - (Specs::TABLE_RIGHT- Specs::BALL_RADIUS)) * gradient;
            m_segment1[1].position.x = (Specs::TABLE_RIGHT- Specs::BALL_RADIUS);
        }
        else // top wall
        {
            m_segment2[1].position.x = m_segment1[1].position.x;
            m_segment2[1].position.y = 2 * (Specs::TABLE_TOP + Specs::BALL_RADIUS) - m_segment1[1].position.y;
            m_segment1[1].position.x = m_segment1[0].position.x - (m_segment1[0].position.y - (Specs::TABLE_TOP + Specs::BALL_RADIUS)) / gradient;
            m_segment1[1].position.y = (Specs::TABLE_TOP + Specs::BALL_RADIUS);
        }
    }
    else if (m_segment1[1].position.y > (Specs::TABLE_BOTTOM - Specs::BALL_RADIUS)) // bottom
    {
        float x_intercept = m_segment1[0].position.x + ((Specs::TABLE_BOTTOM - Specs::BALL_RADIUS) - m_segment1[0].position.y) / gradient;

        if (x_intercept < (Specs::TABLE_LEFT + Specs::BALL_RADIUS)) // left wall
        {
            m_segment2[1].position.x = 2 * (Specs::TABLE_LEFT + Specs::BALL_RADIUS) - m_segment1[1].position.x;
            m_segment2[1].position.y = m_segment1[1].position.y;
            m_segment1[1].position.y = m_segment1[0].position.y - (m_segment1[0].position.x - (Specs::TABLE_LEFT + Specs::BALL_RADIUS)) * gradient;
            m_segment1[1].position.x = (Specs::TABLE_LEFT + Specs::BALL_RADIUS);
        }
        else if (x_intercept > (Specs::TABLE_RIGHT- Specs::BALL_RADIUS)) // right wall
        {
            m_segment2[1].position.x = 2 * (Specs::TABLE_RIGHT- Specs::BALL_RADIUS) - m_segment1[1].position.x;
            m_segment2[1].position.y = m_segment1[1].position.y;
            m_segment1[1].position.y = m_segment1[0].position.y - (m_segment1[0].position.x - (Specs::TABLE_RIGHT- Specs::BALL_RADIUS)) * gradient;
            m_segment1[1].position.x = (Specs::TABLE_RIGHT- Specs::BALL_RADIUS);
        }
        else // bottom wall
        {
            m_segment2[1].position.x = m_segment1[1].position.x;
            m_segment2[1].position.y = 2 * (Specs::TABLE_BOTTOM - Specs::BALL_RADIUS) - m_segment1[1].position.y;
            m_segment1[1].position.x = m_segment1[0].position.x - (m_segment1[0].position.y - (Specs::TABLE_BOTTOM - Specs::BALL_RADIUS)) / gradient;
            m_segment1[1].position.y = (Specs::TABLE_BOTTOM - Specs::BALL_RADIUS);
        }
    }
    else // middle
    {
        if (m_segment1[1].position.x < (Specs::TABLE_LEFT + Specs::BALL_RADIUS)) // left wall
        {
            m_segment2[1].position.x = 2 * (Specs::TABLE_LEFT + Specs::BALL_RADIUS) - m_segment1[1].position.x;
            m_segment2[1].position.y = m_segment1[1].position.y;
            m_segment1[1].position.y = m_segment1[0].position.y - (m_segment1[0].position.x - (Specs::TABLE_LEFT + Specs::BALL_RADIUS)) * gradient;
            m_segment1[1].position.x = (Specs::TABLE_LEFT + Specs::BALL_RADIUS);
        }
        else if (m_segment1[1].position.x > (Specs::TABLE_RIGHT- Specs::BALL_RADIUS)) // right wall
        {
            m_segment2[1].position.x = 2 * (Specs::TABLE_RIGHT- Specs::BALL_RADIUS) - m_segment1[1].position.x;
            m_segment2[1].position.y = m_segment1[1].position.y;
            m_segment1[1].position.y = m_segment1[0].position.y - (m_segment1[0].position.x - (Specs::TABLE_RIGHT- Specs::BALL_RADIUS)) * gradient;
            m_segment1[1].position.x = (Specs::TABLE_RIGHT- Specs::BALL_RADIUS);
        }
        else // neither
        {
            m_isExtensionNeeded = false; 
        }
    }

    m_segment2[0].position = m_segment1[1].position;
    m_ballPrev.setPosition(m_segment1[1].position.x, m_segment1[1].position.y);
}

// Displays the trajectory, the second segment not always needed
void Trajectory::draw(sf::RenderWindow& window)
{
    window.draw(m_segment1, 2, sf::Lines);

    if (m_isExtensionNeeded)
    {
        window.draw(m_segment2, 2, sf::Lines);
        window.draw(m_ballPrev);
    }
}