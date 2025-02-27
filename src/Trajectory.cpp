#include "Trajectory.hpp"
#include "Spec.hpp"
#include <cmath>
#include <utility>

namespace
{
    constexpr float BALL_PREV_OUTLINE_THICKNESS = 1.0f;
}

// All circular shapes are initialized.
Trajectory::Trajectory(TrajectoryMode mode) :
    m_mode{mode}
{
    m_ballPreviews[0].setRadius(Spec::BALL_RADIUS);
    m_ballPreviews[0].setFillColor(sf::Color::Transparent);
    m_ballPreviews[0].setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
    m_ballPreviews[0].setOutlineColor(sf::Color::White);
    m_ballPreviews[0].setOutlineThickness(BALL_PREV_OUTLINE_THICKNESS);
    for (size_t i = 1; i < SEGMENTS_MAX; i++)
    {
        m_ballPreviews[i] = m_ballPreviews[0];
    }
}

// Update different segments based on the mode.
void Trajectory::update(const sf::Vector2f& chargeStart, const sf::Vector2f& mousePos)
{
    if (m_mode == None)
    {
        return;
    }

    updateMiddle(chargeStart, mousePos);

    if (m_mode == Normal || m_mode == Detailed || m_mode == All)
    {   
        for (size_t i = 0; i < m_numSegmentsNeeded; i++)
        {
            m_ballPreviews[i].setPosition(m_segmentsMiddle[2*i+1].position);
        }
    }

    if (m_mode == Detailed || m_mode == All)
    {
        updateLateral();
    }

    // If the maximum speed is going to happen, turn red.
    if (Spec::CHARGE_VELOCITY_COEF * Spec::hypot(chargeStart - mousePos) >= Spec::MAX_CHARGE_SPEED)
    {
        setColor(sf::Color::Red);
    }
    else
    {
        setColor(sf::Color::White);
    }
}

// Updates middle segments by repeatedly calculating reflections at each step until the max number of segments is reached or it doesn't cross either rail.
void Trajectory::updateMiddle(const sf::Vector2f& chargeStart, const sf::Vector2f& mousePos)
{
    m_segmentsMiddle[0].position = chargeStart;
    m_segmentsMiddle[1].position = m_segmentsMiddle[0].position + Spec::CHARGE_VELOCITY_COEF * (chargeStart - mousePos);
    m_numSegmentsNeeded = 1;

    for (size_t& i = m_numSegmentsNeeded; i < SEGMENTS_MAX; i++)
    {
        float gradient = (m_segmentsMiddle[2*(i-1)].position.y - m_segmentsMiddle[2*(i-1)+1].position.y) / (m_segmentsMiddle[2*(i-1)].position.x - m_segmentsMiddle[2*(i-1)+1].position.x);

        // the end of trajectory is in the ... third and intersects the ... rail
        if (m_segmentsMiddle[2*(i-1)+1].position.y < (Spec::TABLE_TOP + Spec::BALL_RADIUS)) // top
        {
            float x_intercept = m_segmentsMiddle[2*(i-1)].position.x + ((Spec::TABLE_TOP + Spec::BALL_RADIUS) - m_segmentsMiddle[2*(i-1)].position.y) / gradient;

            if (x_intercept < (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) // left rail
            {
                m_segmentsMiddle[2*i+1].position.x = 2 * (Spec::TABLE_LEFT + Spec::BALL_RADIUS) - m_segmentsMiddle[2*(i-1)+1].position.x;
                m_segmentsMiddle[2*i+1].position.y = m_segmentsMiddle[2*(i-1)+1].position.y;
                m_segmentsMiddle[2*(i-1)+1].position.y = m_segmentsMiddle[2*(i-1)].position.y - (m_segmentsMiddle[2*(i-1)].position.x - (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) * gradient;
                m_segmentsMiddle[2*(i-1)+1].position.x = Spec::TABLE_LEFT + Spec::BALL_RADIUS;
            }
            else if (x_intercept > (Spec::TABLE_RIGHT- Spec::BALL_RADIUS)) // right rail
            {
                m_segmentsMiddle[2*i+1].position.x = 2 * (Spec::TABLE_RIGHT - Spec::BALL_RADIUS) - m_segmentsMiddle[2*(i-1)+1].position.x;
                m_segmentsMiddle[2*i+1].position.y = m_segmentsMiddle[2*(i-1)+1].position.y;
                m_segmentsMiddle[2*(i-1)+1].position.y = m_segmentsMiddle[2*(i-1)].position.y - (m_segmentsMiddle[2*(i-1)].position.x - (Spec::TABLE_RIGHT - Spec::BALL_RADIUS)) * gradient;
                m_segmentsMiddle[2*(i-1)+1].position.x = Spec::TABLE_RIGHT - Spec::BALL_RADIUS;
            }
            else // top rail
            {
                m_segmentsMiddle[2*i+1].position.x = m_segmentsMiddle[2*(i-1)+1].position.x;
                m_segmentsMiddle[2*i+1].position.y = 2 * (Spec::TABLE_TOP + Spec::BALL_RADIUS) - m_segmentsMiddle[2*(i-1)+1].position.y;
                m_segmentsMiddle[2*(i-1)+1].position.x = m_segmentsMiddle[2*(i-1)].position.x - (m_segmentsMiddle[2*(i-1)].position.y - (Spec::TABLE_TOP + Spec::BALL_RADIUS)) / gradient;
                m_segmentsMiddle[2*(i-1)+1].position.y = Spec::TABLE_TOP + Spec::BALL_RADIUS;
            }
        }
        else if (m_segmentsMiddle[2*(i-1)+1].position.y > (Spec::TABLE_BOTTOM - Spec::BALL_RADIUS)) // bottom
        {
            float x_intercept = m_segmentsMiddle[2*(i-1)].position.x + ((Spec::TABLE_BOTTOM - Spec::BALL_RADIUS) - m_segmentsMiddle[2*(i-1)].position.y) / gradient;

            if (x_intercept < (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) // left rail
            {
                m_segmentsMiddle[2*i+1].position.x = 2 * (Spec::TABLE_LEFT + Spec::BALL_RADIUS) - m_segmentsMiddle[2*(i-1)+1].position.x;
                m_segmentsMiddle[2*i+1].position.y = m_segmentsMiddle[2*(i-1)+1].position.y;
                m_segmentsMiddle[2*(i-1)+1].position.y = m_segmentsMiddle[2*(i-1)].position.y - (m_segmentsMiddle[2*(i-1)].position.x - (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) * gradient;
                m_segmentsMiddle[2*(i-1)+1].position.x = Spec::TABLE_LEFT + Spec::BALL_RADIUS;
            }
            else if (x_intercept > (Spec::TABLE_RIGHT- Spec::BALL_RADIUS)) // right rail
            {
                m_segmentsMiddle[2*i+1].position.x = 2 * (Spec::TABLE_RIGHT - Spec::BALL_RADIUS) - m_segmentsMiddle[2*(i-1)+1].position.x;
                m_segmentsMiddle[2*i+1].position.y = m_segmentsMiddle[2*(i-1)+1].position.y;
                m_segmentsMiddle[2*(i-1)+1].position.y = m_segmentsMiddle[2*(i-1)].position.y - (m_segmentsMiddle[2*(i-1)].position.x - (Spec::TABLE_RIGHT - Spec::BALL_RADIUS)) * gradient;
                m_segmentsMiddle[2*(i-1)+1].position.x = Spec::TABLE_RIGHT - Spec::BALL_RADIUS;
            }
            else // bottom rail
            {
                m_segmentsMiddle[2*i+1].position.x = m_segmentsMiddle[2*(i-1)+1].position.x;
                m_segmentsMiddle[2*i+1].position.y = 2 * (Spec::TABLE_BOTTOM - Spec::BALL_RADIUS) - m_segmentsMiddle[2*(i-1)+1].position.y;
                m_segmentsMiddle[2*(i-1)+1].position.x = m_segmentsMiddle[2*(i-1)].position.x - (m_segmentsMiddle[2*(i-1)].position.y - (Spec::TABLE_BOTTOM - Spec::BALL_RADIUS)) / gradient;
                m_segmentsMiddle[2*(i-1)+1].position.y = Spec::TABLE_BOTTOM - Spec::BALL_RADIUS;
            }
        }
        else // middle
        {
            if (m_segmentsMiddle[2*(i-1)+1].position.x < (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) // left rail
            {
                m_segmentsMiddle[2*i+1].position.x = 2 * (Spec::TABLE_LEFT + Spec::BALL_RADIUS) - m_segmentsMiddle[2*(i-1)+1].position.x;
                m_segmentsMiddle[2*i+1].position.y = m_segmentsMiddle[2*(i-1)+1].position.y;
                m_segmentsMiddle[2*(i-1)+1].position.y = m_segmentsMiddle[2*(i-1)].position.y - (m_segmentsMiddle[2*(i-1)].position.x - (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) * gradient;
                m_segmentsMiddle[2*(i-1)+1].position.x = Spec::TABLE_LEFT + Spec::BALL_RADIUS;
            }
            else if (m_segmentsMiddle[2*(i-1)+1].position.x > (Spec::TABLE_RIGHT- Spec::BALL_RADIUS)) // right rail
            {
                m_segmentsMiddle[2*i+1].position.x = 2 * (Spec::TABLE_RIGHT - Spec::BALL_RADIUS) - m_segmentsMiddle[2*(i-1)+1].position.x;
                m_segmentsMiddle[2*i+1].position.y = m_segmentsMiddle[2*(i-1)+1].position.y;
                m_segmentsMiddle[2*(i-1)+1].position.y = m_segmentsMiddle[2*(i-1)].position.y - (m_segmentsMiddle[2*(i-1)].position.x - (Spec::TABLE_RIGHT - Spec::BALL_RADIUS)) * gradient;
                m_segmentsMiddle[2*(i-1)+1].position.x = Spec::TABLE_RIGHT - Spec::BALL_RADIUS;
            }
            else // neither
            {
                return;
            }
        }

        m_segmentsMiddle[2*i].position = m_segmentsMiddle[2*(i-1)+1].position;
    }
    
    // Doesn't let the last segment go out the table; same as above, but there is only the previous segment.
    size_t i = SEGMENTS_MAX;
    float gradient = (m_segmentsMiddle[2*(i-1)].position.y - m_segmentsMiddle[2*(i-1)+1].position.y) / (m_segmentsMiddle[2*(i-1)].position.x - m_segmentsMiddle[2*(i-1)+1].position.x);
    // the end of trajectory is in the ... third and intersects the ... rail
    if (m_segmentsMiddle[2*(i-1)+1].position.y < (Spec::TABLE_TOP + Spec::BALL_RADIUS)) // top
    {
        float x_intercept = m_segmentsMiddle[2*(i-1)].position.x + ((Spec::TABLE_TOP + Spec::BALL_RADIUS) - m_segmentsMiddle[2*(i-1)].position.y) / gradient;

        if (x_intercept < (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) // left rail
        {
            m_segmentsMiddle[2*(i-1)+1].position.y = m_segmentsMiddle[2*(i-1)].position.y - (m_segmentsMiddle[2*(i-1)].position.x - (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) * gradient;
            m_segmentsMiddle[2*(i-1)+1].position.x = Spec::TABLE_LEFT + Spec::BALL_RADIUS;
        }
        else if (x_intercept > (Spec::TABLE_RIGHT- Spec::BALL_RADIUS)) // right rail
        {
            m_segmentsMiddle[2*(i-1)+1].position.y = m_segmentsMiddle[2*(i-1)].position.y - (m_segmentsMiddle[2*(i-1)].position.x - (Spec::TABLE_RIGHT - Spec::BALL_RADIUS)) * gradient;
            m_segmentsMiddle[2*(i-1)+1].position.x = Spec::TABLE_RIGHT - Spec::BALL_RADIUS;
        }
        else // top rail
        {
            m_segmentsMiddle[2*(i-1)+1].position.x = m_segmentsMiddle[2*(i-1)].position.x - (m_segmentsMiddle[2*(i-1)].position.y - (Spec::TABLE_TOP + Spec::BALL_RADIUS)) / gradient;
            m_segmentsMiddle[2*(i-1)+1].position.y = Spec::TABLE_TOP + Spec::BALL_RADIUS;
        }
    }
    else if (m_segmentsMiddle[2*(i-1)+1].position.y > (Spec::TABLE_BOTTOM - Spec::BALL_RADIUS)) // bottom
    {
        float x_intercept = m_segmentsMiddle[2*(i-1)].position.x + ((Spec::TABLE_BOTTOM - Spec::BALL_RADIUS) - m_segmentsMiddle[2*(i-1)].position.y) / gradient;

        if (x_intercept < (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) // left rail
        {
            m_segmentsMiddle[2*(i-1)+1].position.y = m_segmentsMiddle[2*(i-1)].position.y - (m_segmentsMiddle[2*(i-1)].position.x - (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) * gradient;
            m_segmentsMiddle[2*(i-1)+1].position.x = Spec::TABLE_LEFT + Spec::BALL_RADIUS;
        }
        else if (x_intercept > (Spec::TABLE_RIGHT- Spec::BALL_RADIUS)) // right rail
        {
            m_segmentsMiddle[2*(i-1)+1].position.y = m_segmentsMiddle[2*(i-1)].position.y - (m_segmentsMiddle[2*(i-1)].position.x - (Spec::TABLE_RIGHT - Spec::BALL_RADIUS)) * gradient;
            m_segmentsMiddle[2*(i-1)+1].position.x = Spec::TABLE_RIGHT - Spec::BALL_RADIUS;
        }
        else // bottom rail
        {
            m_segmentsMiddle[2*(i-1)+1].position.x = m_segmentsMiddle[2*(i-1)].position.x - (m_segmentsMiddle[2*(i-1)].position.y - (Spec::TABLE_BOTTOM - Spec::BALL_RADIUS)) / gradient;
            m_segmentsMiddle[2*(i-1)+1].position.y = Spec::TABLE_BOTTOM - Spec::BALL_RADIUS;
        }
    }
    else // middle
    {
        if (m_segmentsMiddle[2*(i-1)+1].position.x < (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) // left rail
        {
            m_segmentsMiddle[2*(i-1)+1].position.y = m_segmentsMiddle[2*(i-1)].position.y - (m_segmentsMiddle[2*(i-1)].position.x - (Spec::TABLE_LEFT + Spec::BALL_RADIUS)) * gradient;
            m_segmentsMiddle[2*(i-1)+1].position.x = Spec::TABLE_LEFT + Spec::BALL_RADIUS;
        }
        else if (m_segmentsMiddle[2*(i-1)+1].position.x > (Spec::TABLE_RIGHT- Spec::BALL_RADIUS)) // right rail
        {
            m_segmentsMiddle[2*(i-1)+1].position.y = m_segmentsMiddle[2*(i-1)].position.y - (m_segmentsMiddle[2*(i-1)].position.x - (Spec::TABLE_RIGHT - Spec::BALL_RADIUS)) * gradient;
            m_segmentsMiddle[2*(i-1)+1].position.x = Spec::TABLE_RIGHT - Spec::BALL_RADIUS;
        }
        else // neither
        {
            return;
        }
    }
}

// Based on the middle segment, updates the left and right segments by shifting the middle by the ball radius.
void Trajectory::updateLateral()
{
    for (size_t i = 0; i < m_numSegmentsNeeded; i++)
    {
        sf::Vector2f shift = m_segmentsMiddle[2*i+1].position - m_segmentsMiddle[2*i].position;
        shift /= Spec::hypot(shift);
        std::swap(shift.x, shift.y);
        shift.y *= -1.0f;
        shift *= Spec::BALL_RADIUS;

        m_segmentsLeft[2*i].position = m_segmentsMiddle[2*i].position + shift;
        m_segmentsLeft[2*i+1].position = m_segmentsMiddle[2*i+1].position + shift;
        m_segmentsRight[2*i].position = m_segmentsMiddle[2*i].position - shift;
        m_segmentsRight[2*i+1].position = m_segmentsMiddle[2*i+1].position - shift;
    }
}

// Draws different segments based on the mode.
void Trajectory::draw(sf::RenderWindow& window)
{
    if (m_mode == None)
    {
        return;
    }
    
    // middle
    if (m_mode == Minimum || m_mode == Normal || m_mode == All)
    {
        for (size_t i = 0; i < m_numSegmentsNeeded; i++)
        {
            window.draw(m_segmentsMiddle.data() + 2*i, 2, sf::Lines);
        }
    }

    // lateral
    if (m_mode == Detailed || m_mode == All)
    {
        for (size_t i = 0; i < m_numSegmentsNeeded; i++)
        {
            window.draw(m_segmentsLeft.data() + 2*i, 2, sf::Lines);
            window.draw(m_segmentsRight.data() + 2*i, 2, sf::Lines);
        }
    }

    // circles
    if (m_mode == Normal || m_mode == Detailed || m_mode == All)
    {
        for (size_t i = 0; i < m_numSegmentsNeeded; i++)
        {
            window.draw(m_ballPreviews[i]);
        }
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

// Sets the color of all elements, invoked when comparing with max charge speed.
void Trajectory::setColor(const sf::Color& color)
{
    for (size_t i = 0; i < m_numSegmentsNeeded; i++)
    {
        m_segmentsMiddle[2*i].color = color;
        m_segmentsMiddle[2*i+1].color = color;
        m_segmentsLeft[2*i].color = color;
        m_segmentsLeft[2*i+1].color = color;
        m_segmentsRight[2*i].color = color;
        m_segmentsRight[2*i+1].color = color;
        m_ballPreviews[i].setOutlineColor(color);
    }
}

