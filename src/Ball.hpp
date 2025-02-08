#pragma once

#include <SFML/Graphics.hpp>

class Ball
{
public:
    enum BallType : std::uint8_t
    {
        None = 0,
        Cue,
        Eightball,
        Player1,
        Player2
    };
public:
    Ball(sf::Vector2f position, BallType type);

    static sf::Color colorFromType(BallType type);

    void draw(sf::RenderWindow& window) const;
    void update(float deltaTime);

    bool checkCollisionWithBall(Ball& other);
    bool checkCollisionWithBorder();
    bool isWithinBall(float x, float y);
    bool isWithinBall(const sf::Vector2f& pos);
    void pot(const sf::Vector2f& pocket);
    void setScoredPosition(const sf::Vector2f& pos) { m_scoredPosition = pos; }

    void scaleVelocity(float xScale, float yScale);
    void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }

    sf::Vector2f getVelocity()  const { return m_velocity; }
    sf::Vector2f getPosition()  const { return m_body.getPosition(); }
    BallType getType()          const { return m_type; }
    bool isPotted()             const { return m_isPotted; }
    bool isAnimationPlaying()   const { return m_animationDuration != 0.0f; }
private:
    float calculateAnimationRadius();
private:
    sf::CircleShape m_body;
    sf::Vector2f m_velocity;
    BallType m_type;
    bool m_isPotted = false;
    float m_animationDuration = 0.0f;
    sf::Vector2f m_animationShift{0.0f, 0.0f};
    sf::Vector2f m_scoredPosition{0.0f, 0.0f};
};
