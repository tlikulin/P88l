#include "Trajectory.hpp"
#include "Spec.hpp"
#include <cmath>
#include <utility>

Trajectory::Trajectory(TrajectoryMode mode) :
    m_mode(mode)
{
    m_ballPrev1.setRadius(Spec::BALL_RADIUS);
    m_ballPrev1.setFillColor(sf::Color::Transparent);
    m_ballPrev1.setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
    m_ballPrev1.setOutlineColor(sf::Color::White);
    m_ballPrev1.setOutlineThickness(1.0f);
    m_ballPrev2 = m_ballPrev1;
}

// Calculates the 2 segments (and co-parts) of trajectory with reflection off the wall if needed
// Basically checks which wall the trajectory crosses, if any, and reflects in it
void Trajectory::update(const sf::Vector2f& chargeStart, const sf::Vector2f& mousePosition)
{
    if (m_mode == None)
        return;

    m_segment1[0].position = chargeStart;
    m_segment1[1].position = m_segment1[0].position + 2.5f * (chargeStart - mousePosition);

    updateReflection();

    if (m_mode == Normal || m_mode == Detailed || m_mode == All)
    {   
        m_ballPrev1.setPosition(m_segment1[1].position);
        m_ballPrev2.setPosition(m_segment2[1].position);
    }

    if (m_mode == Detailed || m_mode == All)
    {
        updateExtra1();
        if (m_isExtensionNeeded)
            updateExtra2();
    }

}

void Trajectory::updateReflection()
{
    m_isExtensionNeeded = true;
    float gradient = (m_segment1[0].position.y - m_segment1[1].position.y) / (m_segment1[0].position.x - m_segment1[1].position.x);

    // the end of trajectory is in the ... third and entersects the ... wall
    if (m_segment1[1].position.y < (Spec::TABLE_TOP + Spec::BALL_RADIUS)) // top
    {
        float x_intercept = m_segment1[0].position.x + ((Spec::TABLE_TOP + Spec::BALL_RADIUS) - m_segment1[0].position.y) / gradient;

        if (x_intercept < (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) // left wall
        {
            m_segment2[1].position.x = 2 * (Spec::TABLE_LEFT + Spec::BALL_RADIUS) - m_segment1[1].position.x;
            m_segment2[1].position.y = m_segment1[1].position.y;
            m_segment1[1].position.y = m_segment1[0].position.y - (m_segment1[0].position.x - (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) * gradient;
            m_segment1[1].position.x = (Spec::TABLE_LEFT + Spec::BALL_RADIUS);
        }
        else if (x_intercept > (Spec::TABLE_RIGHT- Spec::BALL_RADIUS)) // right wall
        {
            m_segment2[1].position.x = 2 * (Spec::TABLE_RIGHT- Spec::BALL_RADIUS) - m_segment1[1].position.x;
            m_segment2[1].position.y = m_segment1[1].position.y;
            m_segment1[1].position.y = m_segment1[0].position.y - (m_segment1[0].position.x - (Spec::TABLE_RIGHT- Spec::BALL_RADIUS)) * gradient;
            m_segment1[1].position.x = (Spec::TABLE_RIGHT- Spec::BALL_RADIUS);
        }
        else // top wall
        {
            m_segment2[1].position.x = m_segment1[1].position.x;
            m_segment2[1].position.y = 2 * (Spec::TABLE_TOP + Spec::BALL_RADIUS) - m_segment1[1].position.y;
            m_segment1[1].position.x = m_segment1[0].position.x - (m_segment1[0].position.y - (Spec::TABLE_TOP + Spec::BALL_RADIUS)) / gradient;
            m_segment1[1].position.y = (Spec::TABLE_TOP + Spec::BALL_RADIUS);
        }
    }
    else if (m_segment1[1].position.y > (Spec::TABLE_BOTTOM - Spec::BALL_RADIUS)) // bottom
    {
        float x_intercept = m_segment1[0].position.x + ((Spec::TABLE_BOTTOM - Spec::BALL_RADIUS) - m_segment1[0].position.y) / gradient;

        if (x_intercept < (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) // left wall
        {
            m_segment2[1].position.x = 2 * (Spec::TABLE_LEFT + Spec::BALL_RADIUS) - m_segment1[1].position.x;
            m_segment2[1].position.y = m_segment1[1].position.y;
            m_segment1[1].position.y = m_segment1[0].position.y - (m_segment1[0].position.x - (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) * gradient;
            m_segment1[1].position.x = (Spec::TABLE_LEFT + Spec::BALL_RADIUS);
        }
        else if (x_intercept > (Spec::TABLE_RIGHT- Spec::BALL_RADIUS)) // right wall
        {
            m_segment2[1].position.x = 2 * (Spec::TABLE_RIGHT- Spec::BALL_RADIUS) - m_segment1[1].position.x;
            m_segment2[1].position.y = m_segment1[1].position.y;
            m_segment1[1].position.y = m_segment1[0].position.y - (m_segment1[0].position.x - (Spec::TABLE_RIGHT- Spec::BALL_RADIUS)) * gradient;
            m_segment1[1].position.x = (Spec::TABLE_RIGHT- Spec::BALL_RADIUS);
        }
        else // bottom wall
        {
            m_segment2[1].position.x = m_segment1[1].position.x;
            m_segment2[1].position.y = 2 * (Spec::TABLE_BOTTOM - Spec::BALL_RADIUS) - m_segment1[1].position.y;
            m_segment1[1].position.x = m_segment1[0].position.x - (m_segment1[0].position.y - (Spec::TABLE_BOTTOM - Spec::BALL_RADIUS)) / gradient;
            m_segment1[1].position.y = (Spec::TABLE_BOTTOM - Spec::BALL_RADIUS);
        }
    }
    else // middle
    {
        if (m_segment1[1].position.x < (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) // left wall
        {
            m_segment2[1].position.x = 2 * (Spec::TABLE_LEFT + Spec::BALL_RADIUS) - m_segment1[1].position.x;
            m_segment2[1].position.y = m_segment1[1].position.y;
            m_segment1[1].position.y = m_segment1[0].position.y - (m_segment1[0].position.x - (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) * gradient;
            m_segment1[1].position.x = (Spec::TABLE_LEFT + Spec::BALL_RADIUS);
        }
        else if (m_segment1[1].position.x > (Spec::TABLE_RIGHT- Spec::BALL_RADIUS)) // right wall
        {
            m_segment2[1].position.x = 2 * (Spec::TABLE_RIGHT- Spec::BALL_RADIUS) - m_segment1[1].position.x;
            m_segment2[1].position.y = m_segment1[1].position.y;
            m_segment1[1].position.y = m_segment1[0].position.y - (m_segment1[0].position.x - (Spec::TABLE_RIGHT- Spec::BALL_RADIUS)) * gradient;
            m_segment1[1].position.x = (Spec::TABLE_RIGHT- Spec::BALL_RADIUS);
        }
        else // neither
        {
            m_isExtensionNeeded = false; 
        }
    }

    m_segment2[0].position = m_segment1[1].position;
}

void Trajectory::updateExtra1()
{
    sf::Vector2f shift = m_segment1[1].position - m_segment1[0].position;
    shift /= Spec::hypot(shift);
    std::swap(shift.x, shift.y);
    shift.y *= -1.0f;
    shift *= Spec::BALL_RADIUS;

    m_segment1L[0].position = m_segment1[0].position + shift;
    m_segment1L[1].position = m_segment1[1].position + shift;
    m_segment1R[0].position = m_segment1[0].position - shift;
    m_segment1R[1].position = m_segment1[1].position - shift;
}

void Trajectory::updateExtra2()
{
    sf::Vector2f shift = m_segment2[1].position - m_segment2[0].position;
    shift /= Spec::hypot(shift);
    std::swap(shift.x, shift.y);
    shift.y *= -1.0f;
    shift *= Spec::BALL_RADIUS;

    m_segment2L[0].position = m_segment2[0].position + shift;
    m_segment2L[1].position = m_segment2[1].position + shift;
    m_segment2R[0].position = m_segment2[0].position - shift;
    m_segment2R[1].position = m_segment2[1].position - shift;
}

void Trajectory::draw(sf::RenderWindow& window)
{
    if (m_mode == None)
        return;
    
    if (m_mode == Minimum || m_mode == Normal || m_mode == All)
        window.draw(m_segment1, 2, sf::Lines);
    if (m_mode == Detailed || m_mode == All)
    {
        window.draw(m_segment1L, 2, sf::Lines);
        window.draw(m_segment1R, 2, sf::Lines);
    }
    if (m_mode == Normal || m_mode == Detailed || m_mode == All)
        window.draw(m_ballPrev1);

    if (m_isExtensionNeeded)
    {
        if (m_mode == Minimum || m_mode == Normal || m_mode == All)
            window.draw(m_segment2, 2, sf::Lines);
        if (m_mode == Detailed || m_mode == All)
        {
            window.draw(m_segment2L, 2, sf::Lines);
            window.draw(m_segment2R, 2, sf::Lines);
        }
        if (m_mode == Normal || m_mode == Detailed || m_mode == All)
            window.draw(m_ballPrev2);
    }
}

void Trajectory::cycleMode()
{
    switch(m_mode)
    {
    case None:
        m_mode = Minimum;
        break;
    case Minimum:
        m_mode = Normal;
        break;
    case Normal:
        m_mode = Detailed;
        break;
    case Detailed:
        m_mode = All;
        break;
    default:
        m_mode = None;
        break;
    }
}
