#include "Ball.hpp"
#include "Spec.hpp"
#include <cmath>
#include <utility>

Ball::Ball(sf::Vector2f position, BallType type) : 
    m_type{type}
{
    m_body.setRadius(Spec::BALL_RADIUS);
    m_body.setFillColor(colorFromType(type));
    m_body.setPosition(position);
    m_body.setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
}

sf::Color Ball::colorFromType(BallType type)
{
    switch(type)
    {
    case Cue:
        return sf::Color::White;
    case Player1:
        return sf::Color::Red;
    case Player2:
        return sf::Color::Blue;
    case Eightball:
        return sf::Color::Black;
    default:
        return sf::Color::Magenta;
    }
}

void Ball::draw(sf::RenderWindow& window) const
{
    window.draw(m_body);
}

// Only moves the ball without checking collisions
// Friction is applied
void Ball::update(float deltaTime)
{
    float magnitude = std::hypot(m_velocity.x, m_velocity.y);
    float coef = Spec::FRICTION_COEF + Spec::SPEED_FRICTION_COEF * magnitude * magnitude;

    if (magnitude < coef * deltaTime)
    {
        m_velocity.x = 0;
        m_velocity.y = 0;
    }
    else
    {
        float angle = std::abs(std::atan(m_velocity.y / m_velocity.x));

        if (m_velocity.x > 0)
            m_velocity.x -=  coef * std::cos(angle) * deltaTime;
        else
            m_velocity.x +=  coef * std::cos(angle) * deltaTime;
        
        if (m_velocity.y > 0)
            m_velocity.y -=  coef * std::sin(angle) * deltaTime;
        else
            m_velocity.y +=  coef * std::sin(angle) * deltaTime;
    }

    m_body.move(m_velocity * deltaTime);
}

void Ball::scaleVelocity(float xScale, float yScale)
{
    m_velocity.x *= xScale;
    m_velocity.y *= yScale;
}

// Checks collision with another ball
// Also handles velocity changes due to the collision
// (oblique collision of 2 smooth balls)
bool Ball::checkCollisionWithBall(Ball& other)
{
    if (m_type == Potted || other.getType() == Potted)
        return false;

    sf::Vector2f vec1to2 = other.getPosition() - getPosition();

    if (std::hypot(vec1to2.x, vec1to2.y) >= 2 * Spec::BALL_RADIUS)
    {
        return false;
    }

    sf::Vector2f otherVelocity = other.getVelocity();

    vec1to2 /= std::hypot(vec1to2.x, vec1to2.y); //now unit vector

    float angle = vec1to2.y > 0 ? std::acos(vec1to2.x) : -std::acos(vec1to2.x);

    // finds projections of the velocities onto the the line connecting the centres (rotates by 'angle')
    sf::Vector2f u1_proj = sf::Vector2f{m_velocity.x*std::cos(-angle) - m_velocity.y*std::sin(-angle), m_velocity.x*std::sin(-angle) + m_velocity.y*std::cos(-angle)};
    sf::Vector2f u2_proj = sf::Vector2f{otherVelocity.x*std::cos(-angle) - otherVelocity.y*std::sin(-angle), otherVelocity.x*std::sin(-angle) + otherVelocity.y*std::cos(-angle)};

    //only changes if the 2 balls are moving towards or one catches up with the other
    if ((u1_proj.x > 0.0f && u2_proj.x < 0.0f)
        || (u1_proj.x > 0.0f && u2_proj.x >= 0.0f && std::abs(u2_proj.x) < std::abs(u1_proj.x))
        || (u1_proj.x <= 0.0f && u2_proj.x < 0.0f && std::abs(u1_proj.x) < std::abs(u2_proj.x)))
    {
        std::swap(u1_proj.x, u2_proj.x);
        u1_proj.x *= Spec::REBOUND_COEF;
        u2_proj.x *= Spec::REBOUND_COEF;

        // from projections back to normal velocities (rotates back)
        m_velocity = sf::Vector2f{u1_proj.x*std::cos(angle) - u1_proj.y*std::sin(angle), u1_proj.x*std::sin(angle) + u1_proj.y*std::cos(angle)};
        other.setVelocity(sf::Vector2f{u2_proj.x*std::cos(angle) - u2_proj.y*std::sin(angle), u2_proj.x*std::sin(angle) + u2_proj.y*std::cos(angle)});

        return true;
    }
    return false;    
}

// checks and handles collision of the ball with the walls
bool Ball::checkCollisionWithBorder()
{
    //collides with the bottom or top border
    if ((getPosition().y + Spec::BALL_RADIUS > Spec::TABLE_BOTTOM && getVelocity().y > 0)
        || (getPosition().y - Spec::BALL_RADIUS < Spec::TABLE_TOP && getVelocity().y < 0))
    {
        scaleVelocity(Spec::REBOUND_COEF, -Spec::REBOUND_COEF);
        return true;
    }
    //collides with the right or left border
    if ((getPosition().x + Spec::BALL_RADIUS > Spec::TABLE_RIGHT && getVelocity().x > 0)
        || (getPosition().x - Spec::BALL_RADIUS < Spec::TABLE_LEFT && getVelocity().x < 0))
    {
        scaleVelocity(-Spec::REBOUND_COEF, Spec::REBOUND_COEF);
        return true;
    }

    return false;
}

// is the point with given coordinates within the ball
bool Ball::isWithinBall(float x, float y)
{
    return std::hypot(x - getPosition().x, y - getPosition().y) <= Spec::BALL_RADIUS;
}
bool Ball::isWithinBall(const sf::Vector2f& pos)
{
    return std::hypot(pos.x - getPosition().x, pos.y - getPosition().y) <= Spec::BALL_RADIUS;
}

void Ball::pot()
{
    m_type = Potted;
}