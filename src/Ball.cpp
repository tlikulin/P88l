#include "Ball.hpp"
#include "Spec.hpp"
#include <cmath>
#include <utility>

namespace
{
    // acoustics
    constexpr float MINDISTANCE                 = 360.0f;
    constexpr float ATTENUATION                 = 0.3f;
    // graphics
    constexpr float POTTING_ANIM_DURATION       = 1.2f;
    constexpr float ROTATION_COEF               = 0.3f;
    // physics
    constexpr float FRICTION_COEF               = 60.0f;
    constexpr float SPEED_FRICTION_COEF         = 0.00065f;
    constexpr float REBOUND_COEF                = 0.95f;
}

// Complete initialization of a ball.
Ball::Ball(sf::Vector2f position, BallType type, const sf::Texture* texture, const sf::SoundBuffer& buffer) : 
    m_type{type}
{
    m_body.setRadius(Spec::BALL_RADIUS);
    m_body.setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
    m_body.setPosition(position);
    // set a texture if it's not null and not empty (default-constructed)
    if (texture && texture->getSize() != sf::Vector2u{0u, 0u})
    {
        m_body.setTexture(texture);
    }
    else
    {
        m_body.setFillColor(colorFromType(type));
    }
    m_soundCollision.setBuffer(buffer);
    m_soundCollision.setMinDistance(MINDISTANCE);
    m_soundCollision.setAttenuation(ATTENUATION);
}

// Ball type mapped to color, magenta if invalid type.
sf::Color Ball::colorFromType(BallType type)
{
    switch(type)
    {
    case Cue:
        return sf::Color::White;
    case Eightball:
        return sf::Color::Black;
    case Player1:
        return Spec::PLAYER1_COLOR;
    case Player2:
        return Spec::PLAYER2_COLOR;
    default:
        return sf::Color::Magenta;
    }
}

// Only moves the ball without checking collisions.
// Friction is applied.
// If the animation should be played, does that instead.
void Ball::update(float deltaTime)
{
    //if potted, only animation can be played
    if (m_isPotted)
    {
        if (m_animationDuration > 0.0f)
        {
            m_animationDuration -= deltaTime;

            //animation finishes, ball size is restored, the ball is moved to the score
            if (m_animationDuration <= 0.0f)
            {
                m_animationDuration = 0.0f;
                m_body.setPosition(m_scoredPosition);
                m_body.setRadius(Spec::BALL_RADIUS);
                m_body.setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
            }
            //animation in progress, change the radius and move towards the pocket
            else
            {
                const float radius = Spec::BALL_RADIUS * calculateAnimationRadiusFactor();
                m_body.setRadius(radius);
                m_body.setOrigin(radius, radius);
                m_body.move(m_animationShift * deltaTime / POTTING_ANIM_DURATION);
            }
        }

        return;
    }

    //friction a = -(A + Bv^2) is applied
    const float magnitude = Spec::hypot(m_velocity);
    const float coef = FRICTION_COEF + SPEED_FRICTION_COEF * magnitude * magnitude;

    if (magnitude < coef * deltaTime)
    {
        m_velocity *= 0.0f;
    }
    else
    {
        const float angle = std::abs(std::atan(m_velocity.y / m_velocity.x));
        // x component
        if (m_velocity.x > 0.0f)
        {
            m_velocity.x -=  coef * std::cos(angle) * deltaTime;
        }
        else
        {
            m_velocity.x +=  coef * std::cos(angle) * deltaTime;
        }
        // y component
        if (m_velocity.y > 0.0f)
        {
            m_velocity.y -=  coef * std::sin(angle) * deltaTime;
        }
        else
        {
            m_velocity.y +=  coef * std::sin(angle) * deltaTime;
        }
    }
    // the ball is moved and the sound is updated
    m_body.move(m_velocity * deltaTime);
    m_body.rotate(ROTATION_COEF * Spec::hypot(m_velocity) * deltaTime);
    m_soundCollision.setPosition(getPosition().x, 0.0f, getPosition().y);
    m_soundCollision.setVolume(std::min(std::sqrt(20.0f * Spec::hypot(m_velocity)), 100.0f)); //scales with speed, 100% at v >= 500
}

void Ball::draw(sf::RenderWindow& window) const
{
    window.draw(m_body);
}

// Checks collision with another ball, plays sound if they collide.
// Handles velocity changes due to the collision.
// (oblique collision of 2 smooth balls)
void Ball::checkCollisionWithBall(Ball& other)
{
    if (isPotted() || other.isPotted()) 
    {
        return;
    }

    sf::Vector2f vec1to2 = other.getPosition() - getPosition();
    const float intersection = 2.0f * Spec::BALL_RADIUS - Spec::hypot(vec1to2);
    if (intersection <= 0.0f) 
    {
        return;
    }

    sf::Vector2f otherVelocity = other.getVelocity();
    vec1to2 /= Spec::hypot(vec1to2); //now unit vector
    const float angle = vec1to2.y > 0.0f ? std::acos(vec1to2.x) : -std::acos(vec1to2.x);

    // finds projections of the velocities onto the the line connecting the centres (rotates by 'angle')
    sf::Vector2f u1_proj = sf::Vector2f{m_velocity.x*std::cos(-angle) - m_velocity.y*std::sin(-angle), m_velocity.x*std::sin(-angle) + m_velocity.y*std::cos(-angle)};
    sf::Vector2f u2_proj = sf::Vector2f{otherVelocity.x*std::cos(-angle) - otherVelocity.y*std::sin(-angle), otherVelocity.x*std::sin(-angle) + otherVelocity.y*std::cos(-angle)};

    //only changes if the 2 balls are moving towards or one catches up with the other
    if ((u1_proj.x > 0.0f && u2_proj.x < 0.0f)
        || (u1_proj.x > 0.0f && u2_proj.x >= 0.0f && std::abs(u2_proj.x) < std::abs(u1_proj.x))
        || (u1_proj.x <= 0.0f && u2_proj.x < 0.0f && std::abs(u1_proj.x) < std::abs(u2_proj.x)))
    {
        std::swap(u1_proj.x, u2_proj.x);
        u1_proj.x *= REBOUND_COEF;
        u2_proj.x *= REBOUND_COEF;

        //from projections back to normal velocities (rotates back)
        m_velocity = sf::Vector2f{u1_proj.x*std::cos(angle) - u1_proj.y*std::sin(angle), u1_proj.x*std::sin(angle) + u1_proj.y*std::cos(angle)};
        other.setVelocity(sf::Vector2f{u2_proj.x*std::cos(angle) - u2_proj.y*std::sin(angle), u2_proj.x*std::sin(angle) + u2_proj.y*std::cos(angle)});

        //the louder sound is played
        if (m_soundCollision.getVolume() > other.getVolume())
        {
            m_soundCollision.play();
        }
        else
        {
            other.playSound();
        }
    }  
}

// Checks and handles collision of the ball with the rails, plays sounds if collides.
void Ball::checkCollisionWithBorder()
{
    //collides with the bottom or top border
    if ((getPosition().y + Spec::BALL_RADIUS > Spec::TABLE_BOTTOM && getVelocity().y > 0.0f)
        || (getPosition().y - Spec::BALL_RADIUS < Spec::TABLE_TOP && getVelocity().y < 0.0f))
    {
        m_velocity.y *= -REBOUND_COEF;
        m_soundCollision.play();
    }
    //collides with the right or left border
    else if ((getPosition().x + Spec::BALL_RADIUS > Spec::TABLE_RIGHT && getVelocity().x > 0.0f)
        || (getPosition().x - Spec::BALL_RADIUS < Spec::TABLE_LEFT && getVelocity().x < 0.0f))
    {
        m_velocity.x *= -REBOUND_COEF;
        m_soundCollision.play();
    }
}

// Stops the ball and starts the animation.
void Ball::pot(const sf::Vector2f& pocket)
{
    m_isPotted = true;
    m_velocity *= 0.0f;
    m_animationDuration = POTTING_ANIM_DURATION;
    m_animationShift = pocket - m_body.getPosition();
}

// The ball is moved to the given positin and restores the state to active.
void Ball::replace(const sf::Vector2f& pos)
{
    m_animationDuration = 0.0f;
    m_scoredPosition *= 0.0f;
    m_isPotted = false;
    m_body.setRadius(Spec::BALL_RADIUS);
    m_body.setOrigin(Spec::BALL_RADIUS, Spec::BALL_RADIUS);
    m_body.setPosition(pos);
}

void Ball::playSound()
{
    m_soundCollision.play();
}

// Is the point with given coordinates within the ball
bool Ball::isWithinBall(const sf::Vector2f& pos) const
{
    return Spec::hypot(pos - getPosition()) <= Spec::BALL_RADIUS;
}

// a parabola such that r=R at t=0, r=1.1R at t=0.5T and r=0 at t=T
float Ball::calculateAnimationRadiusFactor()
{
    static constexpr float a = -2.4f / (POTTING_ANIM_DURATION * POTTING_ANIM_DURATION);
    static constexpr float b = 1.4f / POTTING_ANIM_DURATION;
    static constexpr float c = 1.0f; 
    const float time = POTTING_ANIM_DURATION - m_animationDuration;
    return a * time * time + b * time + c;
}
